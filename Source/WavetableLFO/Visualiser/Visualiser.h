/*
  ==============================================================================

    Visualiser.h
    Created: 5 Feb 2023 2:53:14pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../Constants.h"

class Visualiser : public Component
{
public:
    // Class
	Visualiser();
	~Visualiser();

    // GUI
    void paint(Graphics&) override;
    void setWaveForm(Array<float>);

private:
    Array<float> waveForm;
};
