

#include "PluginProcessor.h"
#include "PluginEditor.h"


// ========== Define Constractor ==========
UpmixerAudioProcessorEditor::UpmixerAudioProcessorEditor(UpmixerAudioProcessor &p)
    : AudioProcessorEditor( &p), processor(p)
{
    // slider for mixing the Front Side Channels
    gainSlider_FS.setSliderStyle(Slider::SliderStyle::LinearVertical);
    gainSlider_FS.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 25);
    gainSlider_FS.setRange(-48, 6, 1);
    gainSlider_FS.setValue(0);
    gainSlider_FS.addListener(this);
    gainSlider_FS.setBounds(60, 150, 80, 200);
    addAndMakeVisible (gainSlider_FS);
    
    // slider for mixing the Abience to the Front Side Channels
    gainSlider_FA.setSliderStyle(Slider::SliderStyle::LinearVertical);
    gainSlider_FA.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 25);
    gainSlider_FA.setRange(-48, 6, 1);
    gainSlider_FA.setValue(-12);
    gainSlider_FA.addListener(this);
    gainSlider_FA.setBounds(160, 150, 80, 200);
    addAndMakeVisible (gainSlider_FA);
    
    // slider for mixing the Abience to the REAR Side Channels
    gainSlider_RA.setSliderStyle(Slider::SliderStyle::LinearVertical);
    gainSlider_RA.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 25);
    gainSlider_RA.setRange(-48, 6, 1);
    gainSlider_RA.setValue(-12);
    gainSlider_RA.addListener(this);
    gainSlider_RA.setBounds(260, 150, 80, 200);
    addAndMakeVisible (gainSlider_RA);
    
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
        int x = 109, y = 20, width = 184, height = 32;
        String text (TRANS("Upmixer"));
        Colour fillColour = Colour(71, 163, 198);
        g.setColour (fillColour);
        g.setFont (Font (18.80f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height, Justification::centred, true);
    }
    
    // add description
    {
        int x = 56, y = 45, width = 288, height = 32;
        String text (TRANS("Stereo (L+R)  to 5.x (L+R+C+Ls+Rs)"));
        Colour fillColour = Colour(71, 163, 198);
        g.setColour (fillColour);
        g.setFont (Font (14.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height, Justification::centred, true);
    }
    
    // add labels for the 3 sliders
    {
        int x = 50, width = 100, height = 32;
        String text1 (TRANS("Gain"));
        String text2 (TRANS("of"));
        String text3 (TRANS("Front Side"));
        Colour fillColour = Colour(24, 31, 34);
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text1, x, 100, width, height, Justification::centred, true);
        g.drawText (text2, x, 112, width, height, Justification::centred, true);
        g.drawText (text3, x, 124, width, height, Justification::centred, true);
    }
    
    {
        int x = 150, width = 100, height = 32;
        String text1 (TRANS("Ambience"));
        String text2 (TRANS("to"));
        String text3 (TRANS("Front Side"));
        Colour fillColour = Colour(24, 31, 34);
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text1, x, 100, width, height, Justification::centred, true);
        g.drawText (text2, x, 112, width, height, Justification::centred, true);
        g.drawText (text3, x, 124, width, height, Justification::centred, true);
    }
    
    {
        int x = 250, width = 100, height = 32;
        String text1 (TRANS("Ambience"));
        String text2 (TRANS("to"));
        String text3 (TRANS("Rear Side"));
        Colour fillColour = Colour(24, 31, 34);
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text1, x, 100, width, height, Justification::centred, true);
        g.drawText (text2, x, 112, width, height, Justification::centred, true);
        g.drawText (text3, x, 124, width, height, Justification::centred, true);
    }
    
    // add info for the Plug-In
    {
        int x = 200, y = 380, width = 530, height = 11;
        String text (TRANS("Ver: ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date: ") + __DATE__ + TRANS(" "));
        Colour fillColour = Colours::white;
        g.setColour (fillColour);
        g.setFont(Font(11.00f, Font::plain));
        g.drawText(text, x, y, width, height, Justification::centredLeft, true);
    }
}


// ========== Define resized Method ==========
void UpmixerAudioProcessorEditor::resized()
{
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


// <----- EOF PluginEditor.cpp

