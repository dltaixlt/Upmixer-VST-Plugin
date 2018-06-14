

#include "PluginProcessor.h"
#include "PluginEditor.h"


// ========== Define Constractor ==========
UpmixerAudioProcessor::UpmixerAudioProcessor()
{
    updateFFTsize (2048);
}


// ========== Define Deconstractor ==========
UpmixerAudioProcessor::~UpmixerAudioProcessor()
{
}


// ========== Define getName Method ==========
const String UpmixerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

// ========== Define acceptsMidi Method ==========
bool UpmixerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

// ========== Define producesMidi Method ==========
bool UpmixerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

// ========== Define isMidiEffect Method ==========
bool UpmixerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

// ========== Define getTailLengthSeconds Method ==========
double UpmixerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

// ========== Define getNumPrograms Method ==========
int UpmixerAudioProcessor::getNumPrograms()
{
    return 1;
}

// ========== Define getCurrentProgram Method ==========
int UpmixerAudioProcessor::getCurrentProgram()
{
    return 0;
}

// ========== Define setCurrentProgram Method ==========
void UpmixerAudioProcessor::setCurrentProgram (int index)
{
}

// ========== Define getProgramName Method ==========
const String UpmixerAudioProcessor::getProgramName (int index)
{
    return {};
}

// ========== Define changeProgramName Method ==========
void UpmixerAudioProcessor::changeProgramName (int index, const String& newName)
{
}


// ========== Define prepareToPlay Method ==========
void UpmixerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    gainFA = pow(10, 0 / 20);
    gainFS = pow(10, -12 / 20);
    gainRA = pow(10, -12 / 20);
    
    updateFFTsize (2048);
}


// ========== Define releaseResources Method ==========
void UpmixerAudioProcessor::releaseResources()
{
}




// ==============================================================================
// ========================= Define processBlock Method =========================
// ==============================================================================
void UpmixerAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    
    // number of samples per buffer
    const int numSamples = buffer.getNumSamples();
    
    // input channels
    auto channelData_left = buffer.getReadPointer(0);
    auto channelData_right = buffer.getReadPointer(1);
    
    // output channels
    float* const ChannelDataOut_1 = buffer.getWritePointer(0);
    float* const ChannelDataOut_2 = buffer.getWritePointer(1);
    float* const ChannelDataOut_3 = buffer.getWritePointer(2);
    float* const ChannelDataOut_4 = buffer.getWritePointer(3);
    float* const ChannelDataOut_5 = buffer.getWritePointer(4);
    
    // main STFT analysis loop
    for (int sample = 0; sample < numSamples; ++sample) {
        // input sample per channel
        timeDomainBuffer_left[sample].real (channelData_left[sample]);
        timeDomainBuffer_left[sample].imag (0.0f);
        
        timeDomainBuffer_right[sample].real (channelData_right[sample]);
        timeDomainBuffer_right[sample].imag (0.0f);
    }
    
    // FFT - Analysis
    fft->perform (timeDomainBuffer_left, frequencyDomainBuffer_left, false);
    fft->perform (timeDomainBuffer_right, frequencyDomainBuffer_right, false);
    
    // Main Upmixing Processing Loop
    for (int sample = 0; sample < numSamples; ++sample) {
        // calculation of Panning Coefficients
        float aL =  abs(frequencyDomainBuffer_left[sample]) / pow(pow(abs(frequencyDomainBuffer_left[sample]), 2) + pow(abs(frequencyDomainBuffer_right[sample]), 2), 0.5);
        float aR =  abs(frequencyDomainBuffer_right[sample]) / pow(pow(abs(frequencyDomainBuffer_left[sample]), 2) + pow(abs(frequencyDomainBuffer_right[sample]), 2), 0.5);
        
        
        // calculation of Direct Component
        float phi = 0.6 * MathConstants<float>::pi;
        std::complex<float> j(0.0, 1.0);
        Direct[sample] = (frequencyDomainBuffer_left[sample] * exp(j*phi) - frequencyDomainBuffer_right[sample]) / (aL * exp(j*phi) - aR);
        
        // calculation of Ambient(L&R) Components
        DL[sample] = Direct[sample] * aL;
        DR[sample] = Direct[sample] * aR;
        NL[sample] = frequencyDomainBuffer_left[sample] - DL[sample];
        NR[sample] = frequencyDomainBuffer_right[sample] - DR[sample];
        
        // up-mixing Direct Component
        DC_mag[sample] = sqrt(0.5) * (abs(DL[sample]+DR[sample])-abs(DL[sample]-DR[sample])); // Center Channel Magnitude
        float nl_dbl_min = std::numeric_limits<float>::min();
        DC[sample] = ((DL[sample]+DR[sample]) * DC_mag[sample]) / (abs(DL[sample]+DR[sample])+nl_dbl_min); // Calculation of Center Channel
        float tmpVar2 = (float) sqrt(0.5);
        CL[sample] = DL[sample] - DC[sample]*tmpVar2; // Calculation of Left & Right Channels
        CR[sample] = DR[sample] - DC[sample]*tmpVar2; // Calculation of Left & Right Channels
    }
    
    // iFFT - Synthesis
    fft->perform (CL, timeDomain_DL, true);
    fft->perform (CR, timeDomain_DR, true);
    fft->perform (DC, timeDomain_DC, true);
    fft->perform (NL, timeDomain_NL, true);
    fft->perform (NR, timeDomain_NR, true);
    
    
    // main STFT synthesis loop
    for (int sample = 0; sample < numSamples; ++sample) {
        ChannelDataOut_1[sample] = (timeDomain_DL[sample].real() * gainFS) + (timeDomain_NL[sample].real() * gainFA);
        ChannelDataOut_2[sample] = (timeDomain_DR[sample].real() * gainFS) + (timeDomain_NR[sample].real() * gainFA);
        ChannelDataOut_3[sample] = timeDomain_DC[sample].real();
        ChannelDataOut_4[sample] = timeDomain_NL[sample].real() * gainRA;
        ChannelDataOut_5[sample] = timeDomain_NR[sample].real() * gainRA;
    }
}
// ==============================================================================
// ==============================================================================
// ==============================================================================




// ========== Define hasEditor Method ==========
bool UpmixerAudioProcessor::hasEditor() const
{
    return true;
}

// ========== Define createEditor Method ==========
AudioProcessorEditor* UpmixerAudioProcessor::createEditor()
{
    return new UpmixerAudioProcessorEditor (*this);
}

// ========== Define getStateInformation Method ==========
void UpmixerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
}

// ========== Define setStateInformation Method ==========
void UpmixerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}


// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new UpmixerAudioProcessor();
}


// <----- EOF PluginProcessor.cpp

