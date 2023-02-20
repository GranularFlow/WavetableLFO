/*
  ==============================================================================

    Separator.h
    Created: 22 Nov 2022 11:46:37pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Constants.h"

class Separator : public Component
{
public:
    void paint(Graphics& g) override {
        g.fillAll(M_T_LIGHT);
    };
};