/*
  ==============================================================================

    Utils.cpp
    Created: 18 Nov 2022 2:08:09pm
    Author:  honza

  ==============================================================================
*/

#include "./Utils.h"


Utils::Utils()
{
}

Utils::~Utils()
{
}

int Utils::msToSamples(float timeInMs, int sampleRate) {

    return Utils::secToSamples((timeInMs /(float) 1000), sampleRate);
}

float Utils::samplesToMs(int samplesCount, int sampleRate) {

    return (samplesCount /(float)sampleRate) * 1000;
}

int Utils::secToSamples(float timeInSec, int sampleRate) {
    int samples = std::round(sampleRate * timeInSec);
    //DBG("samples" << samples);
    return samples;
}

float Utils::percentToFloat(int8 percent)
{
    return (float)percent/100;
}

float Utils::samplesToPercent(int samplePosition, int totalSamples)
{
    return (samplePosition/(float) totalSamples) * 100.0;
}

void Utils::addToFb(FlexBox* fb, Component& c, int8 order, int minWidth,int minHeight) {
    fb->items.add(FlexItem(c).withMinWidth(minWidth).withMinHeight(minHeight).withMargin(0).withOrder(order));
}