/*
  ==============================================================================

    NumberSelect.h
    Created: 18 Nov 2022 2:11:13pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Constants.h"
#include "CustomLook.h"

class NumberSelect : public Component
{
public:
    // Class
	NumberSelect(String, Colour, int, int, int, int);
	~NumberSelect();
    // GUI
    void paint(Graphics&) override;
    void resized() override;
    void clearTop();
    // Public vars
    Slider slider{ Slider::SliderStyle::LinearHorizontal, Slider::TextEntryBoxPosition::TextBoxAbove};
private:
    CustomLook customLook;
    String name;
    Colour guiColor;
};
