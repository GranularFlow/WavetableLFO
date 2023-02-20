/*
  ==============================================================================

    RadioBox.h
    Created: 15 Nov 2022 1:29:12am
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Constants.h"
#include "CustomLook.h"

class Knob : public Component, public Slider::Listener
{
public:
    // Class
    Knob(String, Colour, float, float, float, float);
    ~Knob();
    // GUI
    void paint(Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider*) override;
    // Getters
    float getValue();
    // Public vars
    Slider slider { Slider::SliderStyle::RotaryHorizontalDrag, Slider::TextEntryBoxPosition::NoTextBox };
private:
    CustomLook customLook;
    String name;
    Colour guiColor;
    float value = 0;
};