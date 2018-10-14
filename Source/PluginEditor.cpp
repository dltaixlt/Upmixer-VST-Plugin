

/*
 ==============================================================================
 
 PluginEditor.cpp
 Created: 01 June 2018 10:24:47am
 Author:  Dimitris Koutsaidis
 
 ==============================================================================
 */


#include "PluginEditor.h"


// ========== Define Constructor ==========
UpmixerAudioProcessorEditor::UpmixerAudioProcessorEditor(UpmixerAudioProcessor &p)
    : AudioProcessorEditor(&p), processor(p)
{
    // slider for mixing the Front Side Channels
    gainSlider_FS.setSliderStyle(Slider::SliderStyle::LinearVertical);
    gainSlider_FS.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 25);
    gainSlider_FS.setRange(-48, 6, 1);
    gainSlider_FS.setValue(0);
    gainSlider_FS.addListener(this);
    gainSlider_FS.addMouseListener(this, false);
    addAndMakeVisible (gainSlider_FS);
    
    // slider for mixing the Abience to the Front Side Channels
    gainSlider_FA.setSliderStyle(Slider::SliderStyle::LinearVertical);
    gainSlider_FA.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 25);
    gainSlider_FA.setRange(-48, 6, 1);
    gainSlider_FA.setValue(-12);
    gainSlider_FA.addListener(this);
    gainSlider_FA.addMouseListener(this, false);
    addAndMakeVisible (gainSlider_FA);
    
    // slider for mixing the Abience to the REAR Side Channels
    gainSlider_RA.setSliderStyle(Slider::SliderStyle::LinearVertical);
    gainSlider_RA.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 25);
    gainSlider_RA.setRange(-48, 6, 1);
    gainSlider_RA.setValue(-12);
    gainSlider_RA.addListener(this);
    gainSlider_RA.addMouseListener(this, false);
    addAndMakeVisible (gainSlider_RA);
    
    // toggle TextButton for AboutBox
    AboutBoxToggle.setButtonText("About");
    AboutBoxToggle.addListener(this);
    addAndMakeVisible (AboutBoxToggle);
    // set plugin's UI window size
    setSize (400, 400);
}


// ========== Define Deconstractor ==========
UpmixerAudioProcessorEditor::~UpmixerAudioProcessorEditor()
{
}


// ========== Define paint Method ==========
void UpmixerAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    
    // add title
    {
        g.setColour (Colour(71, 163, 198));
        g.setFont (Font (18.80f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (TRANS("Upmixer"), 109, 20, 184, 32, Justification::centred, true);
    }
    
    // add description
    {
        g.setColour (Colour(71, 163, 198));
        g.setFont (Font (14.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (TRANS("Stereo (L+R)  to 5.x (L+R+C+Ls+Rs)"), 56, 45, 288, 32, Justification::centred, true);
    }
    
    // add labels for the 3 sliders
    {
        int x = 50, width = 100, height = 32;
        g.setColour (Colour(24, 31, 34));
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (TRANS("Gain"), x, 100, width, height, Justification::centred, true);
        g.drawText (TRANS("of"), x, 112, width, height, Justification::centred, true);
        g.drawText (TRANS("Front Side"), x, 124, width, height, Justification::centred, true);
    }
    
    {
        int x = 150, width = 100, height = 32;
        g.setColour (Colour(24, 31, 34));
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (TRANS("Ambience"), x, 100, width, height, Justification::centred, true);
        g.drawText (TRANS("to"), x, 112, width, height, Justification::centred, true);
        g.drawText (TRANS("Front Side"), x, 124, width, height, Justification::centred, true);
    }
    
    {
        int x = 250, width = 100, height = 32;
        g.setColour (Colour(24, 31, 34));
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (TRANS("Ambience"), x, 100, width, height, Justification::centred, true);
        g.drawText (TRANS("to"), x, 112, width, height, Justification::centred, true);
        g.drawText (TRANS("Rear Side"), x, 124, width, height, Justification::centred, true);
    }
    
    // add info for the Plug-In
    {
        String text (TRANS("Ver: ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date: ") + __DATE__ + TRANS(" "));
        g.setColour (Colours::white);
        g.setFont(Font(11.00f, Font::plain));
        g.drawText(text, 200, 380, 530, 11, Justification::centredLeft, true);
    }
}


// ========== Define resized Method ==========
void UpmixerAudioProcessorEditor::resized()
{
    gainSlider_FS.setBounds(60, 150, 80, 200);
    gainSlider_FA.setBounds(160, 150, 80, 200);
    gainSlider_RA.setBounds(260, 150, 80, 200);
    
    AboutBoxToggle.setBounds(18, 370, 50, 20);
}


// ========== Define sliderValueChanged Method ==========
void UpmixerAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
    if (slider == &gainSlider_FS)
    {
        processor.gainFS = pow(10, (gainSlider_FS.getValue() / 20));
    }
    if (slider == &gainSlider_FA)
    {
        processor.gainFA = pow(10, (gainSlider_FA.getValue() / 20));;
    }
    if (slider == &gainSlider_RA)
    {
        processor.gainRA = pow(10, (gainSlider_RA.getValue() / 20));;
    }
}


// ========== Define buttonClicked Method ==========
void UpmixerAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == &AboutBoxToggle)
    {
        // set visible the AboutBox
    }
}


// ========== Define mouseUp Method ==========
void UpmixerAudioProcessorEditor::mouseUp(const juce::MouseEvent &e)
{
    Component* componentThatWasClicked = e.eventComponent;
    int shiftClick = (ModifierKeys::leftButtonModifier | ModifierKeys::shiftModifier);
    bool isShiftClickDown = e.mods.getRawFlags() == shiftClick;
    
    if (componentThatWasClicked == &gainSlider_FS)
    {
        if (isShiftClickDown)
            gainSlider_FS.setValue(0);
    }
    else if (componentThatWasClicked == &gainSlider_FA)
    {
        if (isShiftClickDown)
            gainSlider_FA.setValue(-12);
    }
    else if (componentThatWasClicked == &gainSlider_RA)
    {
        if (isShiftClickDown)
            gainSlider_RA.setValue(-12);
    }
}


// <----- EOF PluginEditor.cpp

