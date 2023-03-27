#include "MSComponent.h"

MSComponent::MSComponent() : PPButton("Play/Pause")
{
    addAndMakeVisible(&PPButton);
    addAndMakeVisible(insMenu);

    insMenu.setTextWhenNothingSelected("Choices");
    insMenu.addItem("Instrument 1", 1);
    insMenu.addItem("Instrument 2", 2);
    insMenu.addItem("Instrument 3", 3);

    insMenu.onChange = [this]
    {
        insMenuChanged();
    };

    setSize (600, 400);
}
//==============================================================================
/**
* paints the basic elements with g graphics object
* @param g
*/
void MSComponent::paint (juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setFont(juce::Font (16.0f));
    g.setColour(juce::Colours::white);
    g.drawText("Music Synthesis", getLocalBounds(), juce::Justification::centredTop, true);
}
//================================================================
void MSComponent::resized()
{
    auto area = getLocalBounds();
    auto newArea = getLocalBounds();

    area.setBounds(10, 10, 100, 40);
    newArea.setBounds(490, 10, 100, 40);

    PPButton.setBounds(area);
    insMenu.setBounds(newArea);
}
//================================================================
/**
* for drawing buttons and creating style
*    @param g
*    @param button
*    @param backgroundColour
*    @param isButtonDown
*/
void MSComponent::drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour, bool isButtonDown)
{
    auto buttonArea = button.getLocalBounds();
    auto edge = 4;

    buttonArea.removeFromLeft(edge);
    buttonArea.removeFromTop(edge);
    
    //creating the shadows
    g.setColour (juce::Colours::darkgrey.withAlpha (0.5f));
    g.fillRect(buttonArea);

    //shadow offsets
    auto offset = isButtonDown ? -edge /2: -edge;
    buttonArea.translate (offset, offset);

    //setting button colour
    g.setColour(backgroundColour);
    g.fillRect(buttonArea);

}    
//================================================================
void MSComponent::PPButtonOnClick()
{
}
//================================================================
void MSComponent::insMenuChanged()
{
    switch (insMenu.getSelectedId())
    {
    case 1: //holder
        break;
    case 2: //holder
        break;
    case 3: //holder
        break;
    default: break;
    }
}