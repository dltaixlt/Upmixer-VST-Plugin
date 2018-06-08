

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


#define BUILD_VER_SUFFIX " beta" // String to be added before the version name on the GUI (e.g. beta, alpha etc..)


// ========== Declare the Plug-In's editor class ==========
class UpmixerAudioProcessorEditor  : public AudioProcessorEditor,
                                     public Slider::Listener
{
public:
    // declare constractor and deconstractor
    UpmixerAudioProcessorEditor(UpmixerAudioProcessor &p);
    ~UpmixerAudioProcessorEditor();

    // declare default methods
    void paint(Graphics &) override;
    void resized() override;
    
    // declare custom methods
    void sliderValueChanged(Slider *) override;

private:
    // audio processor's pointer
    UpmixerAudioProcessor &processor;
    
    // sliders
    Slider gainSlider_FS;
    Slider gainSlider_FA;
    Slider gainSlider_RA;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UpmixerAudioProcessorEditor)
};


// <----- EOF PluginEditor.h

