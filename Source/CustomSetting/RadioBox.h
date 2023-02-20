/*
  ==============================================================================

    RadioBox.h
    Created: 15 Nov 2022 1:29:12am
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Constants.h"
#include "CustomLook.h"

class RadioBox : public Component, public ToggleButton::Listener
{
public:
    // Class
	RadioBox(String, Colour, Array<String>);
    ~RadioBox();
    // GUI
    void paint(Graphics&) override;
    void resized();
    // Listeners
    void buttonStateChanged(Button*) override;
    void buttonClicked(Button*) override;
    // Getters
    int8 getValue();

private:
    CustomLook customLook;
    String name;
    Colour guiColor;
    OwnedArray<ToggleButton> toggleButtons;
    int8 value = 0;
};
