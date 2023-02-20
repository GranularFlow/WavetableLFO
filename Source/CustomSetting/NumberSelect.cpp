/*
  ==============================================================================

    NumberSelect.cpp
    Created: 18 Nov 2022 2:11:13pm
    Author:  honza

  ==============================================================================
*/

#include "NumberSelect.h"

NumberSelect::NumberSelect(String nameIn, Colour guiColorIn, int startRangeIn, int endRangeIn, int stepIn, int initialValue) {
    setLookAndFeel(&customLook);

    guiColor = guiColorIn;
    name = nameIn;
    // Number selector
    slider.setValue(initialValue);
    slider.setRange(startRangeIn, endRangeIn, stepIn);
    slider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    slider.setColour(Slider::ColourIds::trackColourId, guiColorIn);
    slider.setColour(Slider::ColourIds::thumbColourId, guiColorIn);
    slider.setColour(Slider::ColourIds::textBoxBackgroundColourId, guiColorIn.darker());
    slider.setColour(Slider::ColourIds::textBoxOutlineColourId, guiColorIn);


    // Visibility
    addAndMakeVisible(slider);
}

NumberSelect::~NumberSelect() {
    setLookAndFeel(nullptr);
}

void NumberSelect::clearTop() {
    guiColor = C_TRANSPARENT;
}

void NumberSelect::paint(Graphics& g) {
    // Top colour
    g.setColour(guiColor);
    g.fillRect((getWidth() / 2) / 2, 0, (getWidth() / 2), 2);

    g.setColour(C_SMOKE);
    g.drawFittedText(name, getLocalBounds().withTrimmedTop(5).withTrimmedRight(getWidth() * 0.1).withTrimmedLeft(getWidth() * 0.1), Justification::centredTop, 1);
}

void NumberSelect::resized() {
    slider.setBounds(getLocalBounds().withTrimmedBottom(getHeight()/4).withTrimmedLeft(getWidth()*0.2).withTrimmedRight(getWidth() * 0.2).withTrimmedTop(getHeight() / 2));
}