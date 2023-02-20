/*
  ==============================================================================

    Canvas.h
    Created: 17 Oct 2022 4:54:03pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../Constants.h"
class Canvas : public Component
{
public:  
    // Class
    Canvas();
    ~Canvas();

    // GUI
    void paintPath(Graphics& g);
    void paint(Graphics& g) override;
    // Listeners
    void mouseDown(const MouseEvent& e) override;
    void mouseDrag(const MouseEvent& e) override;
    void mouseUp(const MouseEvent&) override;

    // Points
    float snapToClosestXPoint(float xValue);
    void addPoint(float newX, float newY);
    float interpolateY(float x, float x1, float y1, float x2, float y2);

    // Conversion
    void convertPointsToAmplitude();
    float yValueToAmplitude(float);

    Array<float> xPos;
    Array<float> yPos;

    Array<float> waveTableSamples;

    int waveTableIndex = 0;
    const int waveTableSampleCount = 100;
    float sampleDistance = 2.5; // 250 / 100 samples
private:

};