

/*
 ==============================================================================
 
 PluginEditor.h
 Created: 01 June 2018 10:24:47am
 Author:  Dimitris Koutsaidis
 
 ==============================================================================
 */


#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "AboutBox.h"


#define BUILD_VER_SUFFIX " beta" // String to be added before the version name on the GUI (e.g. beta, alpha etc..)


// ========== Declare the Plug-In's editor class ==========
class UpmixerAudioProcessorEditor  : public AudioProcessorEditor,
                                     public Slider::Listener,
                                     public Button::Listener
{
public:
    // declare constructor and deconstructor
    UpmixerAudioProcessorEditor(UpmixerAudioProcessor &p);
    ~UpmixerAudioProcessorEditor();

    // declare default methods
    void paint(Graphics &) override;
    void resized() override;
    
    // declare custom methods
    void sliderValueChanged(Slider *) override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void mouseUp (const juce::MouseEvent &e) override;

private:
    // audio processor's object
    UpmixerAudioProcessor &processor;
    
    ScopedPointer<AboutBox> aboutBox;
    
    // sliders
    Slider gainSlider_FS;
    Slider gainSlider_FA;
    Slider gainSlider_RA;
    
    // buttons
    TextButton AboutBoxToggle;
    
    // UI size
    const int totalWidth;
    const int totalHeight;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UpmixerAudioProcessorEditor)
};


// <----- EOF PluginEditor.h

