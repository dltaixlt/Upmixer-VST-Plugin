

#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

#include "../JuceLibraryCode/JuceHeader.h"


// ========== Declare the Plug-In's processor class ==========
class UpmixerAudioProcessor  : public AudioProcessor
{
public:
    // declare constractor and deconstractor
    UpmixerAudioProcessor();
    ~UpmixerAudioProcessor();

    
    // declare default methods
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (AudioBuffer<float> &, MidiBuffer &) override;
    
    
    // declare extra default methods
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    const String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    
    // declare custom methods
    void updateFFTsize (const int newFftSize)
    {
        fftSize = newFftSize;
        fft = new dsp::FFT (log2 (fftSize));
        
        timeDomainBuffer_left.realloc (fftSize);
        timeDomainBuffer_left.clear (fftSize);
        timeDomainBuffer_right.realloc (fftSize);
        timeDomainBuffer_right.clear (fftSize);
        
        frequencyDomainBuffer_left.realloc (fftSize);
        frequencyDomainBuffer_left.clear (fftSize);
        frequencyDomainBuffer_right.realloc (fftSize);
        frequencyDomainBuffer_right.clear (fftSize);
    }

    
    // declare custom variables
    double gainFS;
    double gainFA;
    double gainRA;
    

private:
    int fftSize;
    ScopedPointer<dsp::FFT> fft;

    HeapBlock<dsp::Complex<float>> timeDomainBuffer_left;
    HeapBlock<dsp::Complex<float>> timeDomainBuffer_right;
    HeapBlock<dsp::Complex<float>> frequencyDomainBuffer_left;
    HeapBlock<dsp::Complex<float>> frequencyDomainBuffer_right;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (UpmixerAudioProcessor)
};


// <----- EOF PluginProcessor.h

