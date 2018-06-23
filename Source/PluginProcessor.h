

#pragma once

#define _USE_MATH_DEFINES

#include <cmath>
#include <math.h>
#include <stdlib.h>
#include <complex.h>
#include <limits>

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
        
        NL.realloc (fftSize);
        NL.clear (fftSize);
        NR.realloc (fftSize);
        NR.clear (fftSize);
        Direct.realloc (fftSize);
        Direct.clear (fftSize);
        DL.realloc (fftSize);
        DL.clear (fftSize);
        DR.realloc (fftSize);
        DR.clear (fftSize);
        DC_mag.realloc (fftSize);
        DC_mag.clear (fftSize);
        DC.realloc (fftSize);
        DC.clear (fftSize);
        CL.realloc (fftSize);
        CL.clear (fftSize);
        CR.realloc (fftSize);
        CR.clear (fftSize);
        
        timeDomain_DL.realloc (fftSize);
        timeDomain_DL.clear (fftSize);
        timeDomain_DR.realloc (fftSize);
        timeDomain_DR.clear (fftSize);
        timeDomain_DC.realloc (fftSize);
        timeDomain_DC.clear (fftSize);
        timeDomain_NL.realloc (fftSize);
        timeDomain_NL.clear (fftSize);
        timeDomain_NR.realloc (fftSize);
        timeDomain_NR.clear (fftSize);
    }
    
    
    // declare slider parameter vars
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
    
    HeapBlock<dsp::Complex<float>> Direct;
    HeapBlock<dsp::Complex<float>> NL;
    HeapBlock<dsp::Complex<float>> NR;
    HeapBlock<dsp::Complex<float>> DL;
    HeapBlock<dsp::Complex<float>> DR;
    HeapBlock<dsp::Complex<float>> DC_mag;
    HeapBlock<dsp::Complex<float>> DC;
    HeapBlock<dsp::Complex<float>> CL;
    HeapBlock<dsp::Complex<float>> CR;
    
    HeapBlock<dsp::Complex<float>> timeDomain_DL;
    HeapBlock<dsp::Complex<float>> timeDomain_DR;
    HeapBlock<dsp::Complex<float>> timeDomain_DC;
    HeapBlock<dsp::Complex<float>> timeDomain_NL;
    HeapBlock<dsp::Complex<float>> timeDomain_NR;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (UpmixerAudioProcessor)
};


// <----- EOF PluginProcessor.h

