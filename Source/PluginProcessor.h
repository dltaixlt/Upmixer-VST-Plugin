/*
 ==============================================================================
 
 PluginProcessor.h
 Created: 01 June 2018 10:24:47am
 Author:  Dimitris Koutsaidis
 
 ==============================================================================
 */


#pragma once

#define _USE_MATH_DEFINES


#include "../JuceLibraryCode/JuceHeader.h"
#include <cmath>
#include <math.h>
#include <stdlib.h>
#include <complex.h>
#include <limits>
#include "STFT.h"


// ========== Declare the Plug-In's processor class ==========
class UpmixerAudioProcessor  : public AudioProcessor
{
public:
    // declare constructor and deconstructor
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
    void updateFFTsize (const int newFFTsize);
    
    
    // declare slider parameter vars
    double gainFS;
    double gainFA;
    double gainRA;
    

private:
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
    
    std::unique_ptr<STFT> upmixerSTFT;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (UpmixerAudioProcessor)
};


// <----- EOF PluginProcessor.h

