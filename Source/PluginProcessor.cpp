

#include "PluginProcessor.h"
#include "PluginEditor.h"


// ========== Define Constractor ==========
UpmixerAudioProcessor::UpmixerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
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
}


// ========== Define releaseResources Method ==========
void UpmixerAudioProcessor::releaseResources()
{
}

// ========== Define isBusesLayoutSupported Method ==========
#ifndef JucePlugin_PreferredChannelConfigurations
bool UpmixerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    return true;
}
#endif




// ==============================================================================
// ========================= Define processBlock Method =========================
// ==============================================================================
void UpmixerAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    //auto totalNumInputChannels  = getTotalNumInputChannels();
    //auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    const float numSamples = buffer.getNumSamples();
    float* const ChannelDataOut_1 = buffer.getWritePointer(0);
    float* const ChannelDataOut_2 = buffer.getWritePointer(1);
    float* const ChannelDataOut_3 = buffer.getWritePointer(2);
    float* const ChannelDataOut_4 = buffer.getWritePointer(3);
    float* const ChannelDataOut_5 = buffer.getWritePointer(4);
    
    for (int i = 0; i < numSamples; ++i)
    {
        float leftChannelDataIn = buffer.getReadPointer(0)[i];
        float rightChannelDataIn = buffer.getReadPointer(1)[i];
        float monoDataIn = (leftChannelDataIn + rightChannelDataIn) / 2;
        
        ChannelDataOut_1[i] = (leftChannelDataIn * gainFS) + (monoDataIn * gainFA);
        ChannelDataOut_2[i] = rightChannelDataIn * gainFS + (monoDataIn * gainFA);
        ChannelDataOut_3[i] = monoDataIn;
        ChannelDataOut_4[i] = rightChannelDataIn * gainRA;
        ChannelDataOut_5[i] = leftChannelDataIn * gainRA;
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


AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new UpmixerAudioProcessor();
}


// <----- EOF PluginProcessor.cpp


