/*
  ==============================================================================

    WavetableSettings.cpp
    Created: 3 Feb 2023 12:46:01pm
    Author:  honza

  ==============================================================================
*/

#include "WavetableSettings.h"


WavetableSettings::WavetableSettings()
{
    addAndMakeVisible(depthKnob);
    addAndMakeVisible(rateKnob);
    addAndMakeVisible(waveCountKnob);
    addAndMakeVisible(interpolationRadioBox);
}

WavetableSettings::~WavetableSettings()
{
}

void WavetableSettings::paint(Graphics& g)
{
    g.setColour(L_GRAY);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 30);
}

void WavetableSettings::resized()
{
    int sectionWidth = (getWidth() * 0.9) / 6;
    int sectionHeight = getHeight();

    FlexBox fb{
            FlexBox::Direction::row,
            FlexBox::Wrap::noWrap,
            FlexBox::AlignContent::center,
            FlexBox::AlignItems::flexStart,
            FlexBox::JustifyContent::spaceAround
    };

    // Second column
    int tmp_height = sectionHeight;
    int tmp_width = 100;
    fb.items.add(FlexItem(rateKnob).withOrder(1).withMinWidth(tmp_width).withMinHeight(tmp_height));
    fb.items.add(FlexItem(depthKnob).withOrder(3).withMinWidth(tmp_width).withMinHeight(tmp_height));
    fb.items.add(FlexItem(waveCountKnob).withOrder(5).withMinWidth(tmp_width).withMinHeight(tmp_height));
    fb.items.add(FlexItem(interpolationRadioBox).withOrder(5).withMinWidth(tmp_width).withMinHeight(tmp_height));


    // White lines
    for (int8 i = 0; i < 3; i++)
    {
        fb.items.add(FlexItem(*separators[i]).withMinWidth(1).withHeight(sectionHeight).withOrder((i + 1) * 2));
    }

    fb.performLayout(getLocalBounds());

}


float WavetableSettings::getRate()
{
    return rateKnob.getValue();
}

float WavetableSettings::getDepth()
{
    return depthKnob.getValue();
}

float WavetableSettings::getWaveCount()
{
    return waveCountKnob.getValue();
}


bool WavetableSettings::isCurrentInterpolationType(WavetableSettings::InterpolationType type)
{
    return ((WavetableSettings::InterpolationType)interpolationRadioBox.getValue() == type);
}
