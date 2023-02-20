/*
  ==============================================================================

    WavetableSettings.h
    Created: 3 Feb 2023 12:46:01pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../Constants.h"
#include "../../CustomSetting/RadioBox.h"
#include "../../CustomSetting/Knob.h"
#include "../../CustomSetting/Separator.h"

class WavetableSettings : public Component
{
public:
 
    static enum InterpolationType
    {
        LINEAR,
        CUBIC,
        HERMITE
    };

    // Class
	WavetableSettings();
	~WavetableSettings();

    // GUI
    void paint(Graphics& graphics) override;
    void resized() override;

    // Tools
    // Getters
    float getRate();
    float getDepth();
    float getWaveCount();
    bool isCurrentInterpolationType(WavetableSettings::InterpolationType);

    // Settings
    // (String nameIn, Colour guiColorIn, float startRangIn, float endRangeIn, float stepIn, float defaultValue)
    Knob rateKnob{ "RATE", C_SUNFLOWER, 100, 1000, 1, 400 }; // %
    Knob depthKnob{ "DEPTH", C_SUNFLOWER, 0, 100, 1, 50 }; // %
    Knob waveCountKnob{ "WAVE COUNT", C_SUNFLOWER, 2, 10, 2, 6 }; // %
    RadioBox interpolationRadioBox{ "ITERPOLATION", C_SUNFLOWER, INTERPOLATION_TYPE };

private:
    // GUI
    Colour guiColour;
    OwnedArray<Separator> separators;


};
