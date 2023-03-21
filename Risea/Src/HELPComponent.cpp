#include "HELPComponent.h"

HelpComponent::HelpComponent()  : MSButton("Music Synthesis"), TTSButtonOnClick("Text to Speech")
{
    setSize (400, 600);
    MSButton.onClick = [this] 
    {
        MSButtonOnClick();
    };

    TTSButton.onClick = [this]
    {
        TTSButtonOnClick();
    };

    addAndMakeVisible(&MSButton);
    addAndMakeVisible(&TTSButton);
}

void HelpComponent::MSButtonOnClick()
{
    if (Mswindow)
        MsWindow->broughtToFront();
    else
    {
        Mswindow.reset(new Mswindow("Music Synthesis"));
        Mswindow->centreWithSize(600,400);
        Mswindow->setVisible(true);
    }
}

void HelpComponent::TTSButtonOnClick()
{
    if (Ttswindow)
        Ttswindow->broughtToFront();
    else
    {
        Ttswindow.reset(new Ttswindow("Text to Speech"));
        Ttswindow->centreWithSize(600,400);
        Ttswindow->setVisible(true);
    }
}


/**
 * paints the basic elements with the g graphics object
 * @param g
*/
void HelpComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::Font (16.0f));
    g.setColour(juce::Colours::white);
    g.drawText("Help", juce::Justification::centredTop, true);
}

void HelpComponent::resized()
{
    auto area1 = getLocalBounds();
    auto area2 = getLocalBounds();

    area1.setBounds(130, 170, 160, 80);
    area2.setBounds(310, 170, 160, 80);

    MSButton.setBounds(area1);
    TTSButton.setBounds(area2);
}

/**
 * draws button and creates style for buttons
 * @param g
 * @param button 
 * @param backgroundColour
 * @param isButtonDown
*/

void HelpComponent::drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour, bool isButtonDown)
{
    auto buttonArea = button.getLocalBounds();
    auto edge = 4;

    g.setColour(juce::Colours::darkgrey.withAlpha (0.5f));
    g.fillRect(buttonArea);

    auto offset = isButtonDown ? -edge /2 -edge;
    buttonArea.translate(offset, offset);

    g.setColour(backgroundColour);
    g.fillRect(buttonArea);
}