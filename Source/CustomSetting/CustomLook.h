/*
  ==============================================================================

    KnobDraw.h
    Created: 22 Nov 2022 10:25:16pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Constants.h"

class CustomLook : public LookAndFeel_V4
{
public:
    CustomLook();
	~CustomLook();
    void drawRotarySlider(juce::Graphics&, int, int, int, int, float, const float, const float, juce::Slider&) override;
    void drawLinearSlider(Graphics& , int, int, int, int, float, float, float, const Slider::SliderStyle, Slider&) override;
    void drawTickBox(Graphics&, Component&, float, float, float, float, bool, bool, bool, bool) override;
};
