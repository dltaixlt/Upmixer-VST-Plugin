

/*
 ==============================================================================
 
 PluginProcessor.cpp
 Created: 01 June 2018 10:24:47am
 Author:  Dimitris Koutsaidis
 
 ==============================================================================
 */


#include "PluginProcessor.h"
#include "PluginEditor.h"


// ========== Define Constructor ==========
UpmixerAudioProcessor::UpmixerAudioProcessor()
{
    updateFFTsize (2048);
}


// ========== Define Deconstructor ==========
UpmixerAudioProcessor::~UpmixerAudioProcessor() {}


// ========== Define default JUCE methods ==========
const String UpmixerAudioProcessor::getName() const { return JucePlugin_Name; }
bool UpmixerAudioProcessor::acceptsMidi() const { return false; }
bool UpmixerAudioProcessor::producesMidi() const { return false; }
bool UpmixerAudioProcessor::isMidiEffect() const { return false; }
double UpmixerAudioProcessor::getTailLengthSeconds() const { return 0.0; }
int UpmixerAudioProcessor::getNumPrograms() { return 1; }
int UpmixerAudioProcessor::getCurrentProgram() { return 0; }
void UpmixerAudioProcessor::setCurrentProgram (int index) {}
const String UpmixerAudioProcessor::getProgramName (int index) { return {}; }
void UpmixerAudioProcessor::changeProgramName (int index, const String& newName) {}
void UpmixerAudioProcessor::releaseResources() {}
bool UpmixerAudioProcessor::hasEditor() const { return true; }
AudioProcessorEditor* UpmixerAudioProcessor::createEditor() { return new UpmixerAudioProcessorEditor (*this); }
void UpmixerAudioProcessor::getStateInformation (MemoryBlock& destData) {}
void UpmixerAudioProcessor::setStateInformation (const void* data, int sizeInBytes) {}


// ========== Define prepareToPlay Method ==========
void UpmixerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    updateFFTsize (2048);
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
    
    // declare const var for Direct Component calculation
    std::complex<float> tmpExp(-0.30901699437, -0.30901699437); // exp(i*0.6*pi) = cos(0.6*pi) + i*sin(0.6*pi) = tmpExp
    
    // Main Upmixing Processing Loop
    for (int sample = 0; sample < numSamples; ++sample) {
        
        // calculation of Panning Coefficients
        float aL =  abs(frequencyDomainBuffer_left[sample]) / sqrt( abs(frequencyDomainBuffer_left[sample])*abs(frequencyDomainBuffer_left[sample]) + abs(frequencyDomainBuffer_right[sample])*abs(frequencyDomainBuffer_right[sample]) );
        float aR =  abs(frequencyDomainBuffer_right[sample]) / sqrt( abs(frequencyDomainBuffer_left[sample])*abs(frequencyDomainBuffer_left[sample]) + abs(frequencyDomainBuffer_right[sample])*abs(frequencyDomainBuffer_right[sample]) );
        
        
        // calculation of Direct Component
        Direct[sample] = (frequencyDomainBuffer_left[sample] * tmpExp - frequencyDomainBuffer_right[sample]) / (aL * tmpExp - aR);
        
        // calculation of Ambient(L&R) Components
        DL[sample] = Direct[sample] * aL;
        DR[sample] = Direct[sample] * aR;
        NL[sample] = frequencyDomainBuffer_left[sample] - DL[sample];
        NR[sample] = frequencyDomainBuffer_right[sample] - DR[sample];
        
        // up-mixing Direct Component
        // sqrt(0.5) = 0.70710678118
        DC_mag[sample] = (float)0.70710678118 * (abs(DL[sample]+DR[sample])-abs(DL[sample]-DR[sample])); // Center Channel Magnitude
        float nl_dbl_min = std::numeric_limits<float>::min();
        DC[sample] = ((DL[sample]+DR[sample]) * DC_mag[sample]) / (abs(DL[sample]+DR[sample])+nl_dbl_min); // Calculation of Center Channel
        CL[sample] = DL[sample] - DC[sample]*(float)0.70710678118; // Calculation of Left & Right Channels
        CR[sample] = DR[sample] - DC[sample]*(float)0.70710678118; // Calculation of Left & Right Channels
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


// ========== Define updateFFTsize Method ==========
void UpmixerAudioProcessor::updateFFTsize (const int newFFTsize)
{
    fft = new dsp::FFT (log2 (newFFTsize));
    
    timeDomainBuffer_left.realloc (newFFTsize);
    timeDomainBuffer_left.clear (newFFTsize);
    timeDomainBuffer_right.realloc (newFFTsize);
    timeDomainBuffer_right.clear (newFFTsize);
    
    frequencyDomainBuffer_left.realloc (newFFTsize);
    frequencyDomainBuffer_left.clear (newFFTsize);
    frequencyDomainBuffer_right.realloc (newFFTsize);
    frequencyDomainBuffer_right.clear (newFFTsize);
    
    NL.realloc (newFFTsize);
    NL.clear (newFFTsize);
    NR.realloc (newFFTsize);
    NR.clear (newFFTsize);
    Direct.realloc (newFFTsize);
    Direct.clear (newFFTsize);
    DL.realloc (newFFTsize);
    DL.clear (newFFTsize);
    DR.realloc (newFFTsize);
    DR.clear (newFFTsize);
    DC_mag.realloc (newFFTsize);
    DC_mag.clear (newFFTsize);
    DC.realloc (newFFTsize);
    DC.clear (newFFTsize);
    CL.realloc (newFFTsize);
    CL.clear (newFFTsize);
    CR.realloc (newFFTsize);
    CR.clear (newFFTsize);
    
    timeDomain_DL.realloc (newFFTsize);
    timeDomain_DL.clear (newFFTsize);
    timeDomain_DR.realloc (newFFTsize);
    timeDomain_DR.clear (newFFTsize);
    timeDomain_DC.realloc (newFFTsize);
    timeDomain_DC.clear (newFFTsize);
    timeDomain_NL.realloc (newFFTsize);
    timeDomain_NL.clear (newFFTsize);
    timeDomain_NR.realloc (newFFTsize);
    timeDomain_NR.clear (newFFTsize);
}


// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter() { return new UpmixerAudioProcessor(); }


// <----- EOF PluginProcessor.cpp

