/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Created with Projucer version: 5.3.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

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

    // Binary resources:
    static const char* audiogrouplogo_png;
    static const int audiogrouplogo_pngSize;
    static const char* upatraslogo_jpg;
    static const int upatraslogo_jpgSize;


private:

    ScopedPointer<TextButton> okButton;
    Image cachedImage_audiogrouplogo_png_1;
    Image cachedImage_upatraslogo_jpg_2;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AboutBox)
};

//[/EndFile]
