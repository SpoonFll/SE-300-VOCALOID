#include "TTSComponent.h"

// Buttons etc go here
TTSComponent::TTSComponent() : testButton("TEST")
{
    setSize (600, 400);

    /*testButton.onClick = [this] {
        if(MainWindow)
            MainWindow->broughtToFront();
        else
        {

        }
    };*/

    addAndMakeVisible(&testButton);
}
//==============================================================================
void TTSComponent::testButtonOnClick()
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
    //this will be continued when buttons and other items are implemented

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

