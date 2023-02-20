//
// Created by honza on 15. 11. 2022.
//
#include "RadioBox.h"

RadioBox::RadioBox(String nameIn, Colour guiColorIn, Array<String> elementsIn)
{
    setLookAndFeel(&customLook);

    name = nameIn;
    guiColor = guiColorIn;

    for (String element : elementsIn)
    {
        auto button = new ToggleButton(element);
        button->setRadioGroupId(1);
        button->setColour(ToggleButton::ColourIds::tickColourId, guiColorIn);
        button->addListener(this);
        addAndMakeVisible(button);
        toggleButtons.add(button);
    }
    toggleButtons[0]->setToggleState(true, true);
}

RadioBox::~RadioBox() {

    for (ToggleButton* button : toggleButtons)
    {
        button->removeListener(this);
    }

    setLookAndFeel(nullptr);
}

void RadioBox::paint(Graphics& g) {

    g.setColour(guiColor);
    g.fillRect((getWidth() / 2) / 2, 0, (getWidth() / 2), 5);

    g.setColour(Colours::whitesmoke);
    g.drawFittedText(name, getLocalBounds().withTrimmedTop(10).withTrimmedRight(getWidth() * 0.1).withTrimmedLeft(getWidth() * 0.1), Justification::centredTop, 1);
}

void RadioBox::buttonStateChanged(Button* button)
{
    if (button->getToggleState()) {
        for (int8 i = 0; i < toggleButtons.size(); ++i){
            if(button == toggleButtons[i]){
                value = i;
            }
        }
    }
    const MessageManagerLock mmLock;
    repaint();

}

void RadioBox::buttonClicked(Button* button){}

int8 RadioBox::getValue(){
    return value;
}

void RadioBox::resized()
{
    //DBG("RESIZED");
    juce::FlexBox fb {
        FlexBox::Direction::column,
        FlexBox::Wrap::wrap,
        FlexBox::AlignContent::center,
        FlexBox::AlignItems::center,
        FlexBox::JustifyContent::center
    };

    for (ToggleButton* toggleButton : toggleButtons)
    {
        fb.items.add(juce::FlexItem(*toggleButton).withMinWidth(getWidth()*0.8).withHeight(20).withMaxHeight((getHeight() - 30) / toggleButtons.size()));
    }
    fb.performLayout(getLocalBounds().toFloat());
}