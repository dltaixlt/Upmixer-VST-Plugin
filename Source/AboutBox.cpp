/*
 ==============================================================================
 
 AboutBox.cpp
 Created: 14 October 2018 4:56:34pm
 Author:  Dimitris Koutsaidis
 
 ==============================================================================
 */


#include "AboutBox.h"


AboutBox::AboutBox ()
{
    setName ("AboutBox");
    
    hyperlinkButton.reset (new HyperlinkButton (TRANS("http://www.juce.com"), URL ("http://www.juce.com")));
    addAndMakeVisible (hyperlinkButton.get());
    hyperlinkButton->setTooltip (TRANS("http://www.juce.com"));
    hyperlinkButton->setButtonText (TRANS("http://www.juce.com"));

    okButton.reset(new TextButton ("okButton"));
    addAndMakeVisible (okButton.get());
    okButton->setButtonText (TRANS("OK"));
    okButton->addListener (this);
    okButton->setColour (TextButton::buttonColourId, Colours::black);

    setSize (400, 400);
}


AboutBox::~AboutBox()
{
    hyperlinkButton = nullptr;
    okButton = nullptr;
}


void AboutBox::paint (Graphics& g)
{
    //g.fillAll (Colour (0xd047a3c6));
    g.fillAll (Colour (0x5e47a3c6));
    g.setColour (Colours::black);
    
    int x = proportionOfWidth (0.0f);
    int width = proportionOfWidth (1.0f);
    int height = proportionOfHeight (0.04f);
    
    // Draw box Background
    {
        g.setColour (Colours::white);
        g.fillRoundedRectangle (proportionOfWidth (0.2f), proportionOfWidth (0.1f), proportionOfWidth (0.6f), proportionOfWidth (0.8f), 10.000f);
    }

    // Description
    {
        int yTop = proportionOfHeight (0.15f);
        int yMiddle = proportionOfHeight (0.19f);
        int yBottom = proportionOfHeight (0.23f);
        
        String textTop (TRANS("Developed by Dimitris Koutsaidis in the"));
        String textMiddle (TRANS("context of his Master\'s Thesis."));
        String textBottom (TRANS("Supervission by Professor John Mourjopoulos."));
        
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Regular"));
        
        g.drawText (textTop, x, yTop, width, height, Justification::centred, true);
        g.drawText (textMiddle, x, yMiddle, width, height, Justification::centred, true);
        g.drawText (textBottom, x, yBottom, width, height, Justification::centred, true);
    }

    // Github Info
    {
        int yTop = proportionOfHeight (0.33f);
        int yBottom = proportionOfHeight (0.37f);
        
        String textTop (TRANS("Open-source code available here:"));
        String textBottom (TRANS("github.com/dkoutsaidis/Upmixer-VST-Plugin"));
        
        g.setFont (Font (10.00f, Font::plain).withTypefaceStyle ("Regular"));
        
        g.drawText (textTop, x, yTop, width, height, Justification::centred, true);
        g.drawText (textBottom, x, yBottom, width, height, Justification::centred, true);
    }

    // Legal
    {
        int y1 = proportionOfHeight (0.47f);
        int y4 = proportionOfHeight (0.51f);
        int y2 = proportionOfHeight (0.55f);
        int y3 = proportionOfHeight (0.59f);
        
        String text1 (CharPointer_UTF8 ("All Rights Reserved by Audio Group \xc2\xa9."));
        String text2 (TRANS("Department of Electrical & Computer Engineering,"));
        String text3 (TRANS("University of Patras, Greece."));
        String text4 (TRANS("Wire Communications Laboratory,"));
        
        g.setFont (Font (10.00f, Font::plain).withTypefaceStyle ("Regular"));
        
        g.drawText (text1, x, y1, width, height, Justification::centred, true);
        g.drawText (text2, x, y2, width, height, Justification::centred, true);
        g.drawText (text3, x, y3, width, height, Justification::centred, true);
        g.drawText (text4, x, y4, width, height, Justification::centred, true);
    }
}


void AboutBox::resized()
{
    okButton->setBoundsRelative(0.4f, 0.69f, 0.2f, 0.06f);
    hyperlinkButton->setBounds (128, 184, 150, 24);
}


void AboutBox::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == okButton.get())
        setVisible(false);
}


// <----- EOF AboutBox.cpp

