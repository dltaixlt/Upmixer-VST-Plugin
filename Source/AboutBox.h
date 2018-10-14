/*
 ==============================================================================
 
 AboutBox.h
 Created: 14 October 2018 4:56:34pm
 Author:  Dimitris Koutsaidis
 
 ==============================================================================
 */


#pragma once
#include "JuceHeader.h"


class AboutBox  : public Component,
                  public Button::Listener
{
public:
    AboutBox ();
    ~AboutBox();

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;

private:
    std::unique_ptr<HyperlinkButton> hyperlinkButton;
    std::unique_ptr<TextButton> okButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AboutBox)
};


// <----- EOF AboutBox.h

