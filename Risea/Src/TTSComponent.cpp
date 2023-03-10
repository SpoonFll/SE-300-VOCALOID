#include "TTSComponent.h"

// Buttons etc go here
TTSComponent::TTSComponent() : PPButton("Play/Pause")
{

    addAndMakeVisible(&PPButton);
    addAndMakeVisible(voiceMenu);
    
    voiceMenu.setTextWhenNothingSelected("Choices");
    voiceMenu.addItem("Voice 1", 1);
    voiceMenu.addItem("Voice 2", 2);
    voiceMenu.addItem("Voice 3", 3);

     setSize (600, 400);
}
//==============================================================================
void TTSComponent::PPButtonOnClick()
{
}

//==============================================================================
/**
* paints the basic elements with g graphics object
* @param g
*/
void TTSComponent::paint (juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::Font (16.0f));
    g.setColour (juce::Colours::white);
    g.drawText ("Text to Speech", getLocalBounds(), juce::Justification::centredTop, true);
}
/**
 * adds visibility of buttons
 * @TODO implement buttons
 */
void TTSComponent::resized()
{
    auto area = getLocalBounds();
    auto newArea = getLocalBounds();
    auto newArea2 = getLocalBounds();

    area.setBounds(10, 10, 80, 40);
    //itty bitty tiny pp button
    newArea.setBounds(150, 10, 80, 40);
    newArea2.setBounds(200, 5, 80, 40);
    //this will be continued when buttons and other items are implemented
    PPButton.setBounds(area);
    voiceMenu.setBounds(newArea);
    
}

/**
* for drawing buttons and creating style
*    @param g
*    @param button
*    @param backgroundColour
*    @param isButtonDown
*/
void TTSComponent::drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour, bool isButtonDown)
{
    auto buttonArea = button.getLocalBounds();
    auto edge = 4;

    buttonArea.removeFromLeft(edge);
    buttonArea.removeFromTop(edge);

    //creating the shadows
    g.setColour (juce::Colours::darkgrey.withAlpha (0.5f));
    g.fillRect (buttonArea);

    //shadow offsets
    auto offset = isButtonDown ? -edge /2 : -edge;
    buttonArea.translate (offset, offset);

    //setting the button color
    g.setColour (backgroundColour);
    g.fillRect (buttonArea);
}

void TTSComponent::voiceMenuChanged()
{
    switch (voiceMenu.getSelectedId())
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