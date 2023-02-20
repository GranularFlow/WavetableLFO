/*
  ==============================================================================

    Visualiser.cpp
    Created: 5 Feb 2023 2:53:14pm
    Author:  honza

  ==============================================================================
*/

#include "Visualiser.h"

Visualiser::Visualiser()
{
}

Visualiser::~Visualiser()
{
}

void Visualiser::paint(Graphics& g)
{
    g.fillAll(C_ANDROID);

    g.setColour(C_WHITE);
    
    int sampleCount = waveForm.size();
    float yOffset = (float)getHeight() / (float)2;
    float step = (float)getWidth() / (float)sampleCount;
    int index = 0;

    for (int sampleIndex = 0; sampleIndex < sampleCount; sampleIndex++)
    {
        int y = yOffset + (yOffset * (-waveForm[sampleIndex]));

        if (y < 0 || y > getHeight())
        {
            y = yOffset;
        }

        g.fillRect((float)step * sampleIndex, (float)y, (float)2, (float)2);
    }
}

void Visualiser::setWaveForm(Array<float> inputArray)
{
    waveForm.clear();
    waveForm = inputArray;
    repaint();
}
