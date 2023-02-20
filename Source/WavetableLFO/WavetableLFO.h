/*
  ==============================================================================

    WavetableLFO.h
    Created: 3 Feb 2023 12:45:49pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Constants.h"
#include "../Utils/Utils.h"
#include "WavetableSettings/WavetableSettings.h"
#include "Canvas/Canvas.h"
#include "Visualiser/Visualiser.h"

class WavetableLFO : public Component, public Button::Listener, public Slider::Listener
{
public:
    // Class
	WavetableLFO();
	~WavetableLFO();


    // Listeners
    void addListeners();
    void removeListeners();
    void sliderValueChanged(Slider*) override;
    void buttonClicked(Button*) override;

    // GUI
    void paint(Graphics&) override;
    void paintLogoOnce(Graphics&);
    void resized()override;
    
    // Tools
    void initSamples();
    float interpolate(float x, float x1, float x2, float y1, float y2);

    float getNext();
private:
    TextButton combineButton{ "COMBINE" };
    Canvas canvas1;
    Canvas canvas2;
    Canvas canvas3;
    Visualiser canvas4;
    WavetableSettings wavetableSettings;
    Array<float> sampleY;
    Array<float> sampleX;

    float frequency = 440;
    float sampleRate = 48000;

    int currentPosition = 0;
    float increment = 1.0;
};
