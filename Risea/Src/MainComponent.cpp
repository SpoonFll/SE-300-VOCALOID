#include "MainComponent.h"
//namespace juce
//==============================================================================
/**
 * constructs buttons and sets size for main component object
 * also applies lambda function for button1
 */
MainComponent::MainComponent() : button1("Mode: Speech Synthesis"), button2("Mode: Music Synthesis"), button3("Help")
{
    setSize (600, 400);

    //creating the first button
    //button1.setButtonText("Mode: Speech Synthesis");
    button1.onClick = [this] {
        if(TTSwindow)
            TTSwindow->broughtToFront();
        else
        {
            TTSwindow = new juce::TopLevelWindow( "Text to Speech", true);
            TTSwindow->centreWithSize(600,400);
            TTSwindow->setVisible(true);
        }
    };

    //creating the second button
    //button2.setButtonText("Mode: Music Synthesis");
    button2.onClick = [this] {
        if(MSwindow)
            MSwindow->broughtToFront();
        else
        {
            MSwindow = new juce::TopLevelWindow("Music Synthesis", true);
            MSwindow->centreWithSize(600, 400);
            MSwindow->setVisible(true);
        }
    };

    //creating the third button
    //button3.setButtonText("Help");
    button3.onClick = [this] {
        if(HELPwindow)
            HELPwindow->broughtToFront();
        else
        {
            HELPwindow = new juce::TopLevelWindow("Help", true);
            HELPwindow->centreWithSize(600, 400);
            HELPwindow->setVisible(true);
        }
    };

    addAndMakeVisible (&button1);
    addAndMakeVisible (&button2);

    //creating the third button
    //button3.setButtonText("Help");
    addAndMakeVisible (&button3);

}

//==============================================================================
/**
 * function for button click on button 1
 * @TODO add functionality open a new window or have it play back music in earlier sprints
 */
void MainComponent::button1OnClick()
{
}

void MainComponent::button2OnClick()
{
}

void MainComponent::button3OnClick()
{
}

/**
 * paints the basic elements with the g Graphics object only prints welcome for now
 * @param g
 */
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont (juce::Font (16.0f));
    g.setColour (juce::Colours::white);
    g.drawText ("Welcome to Risea!", getLocalBounds(), juce::Justification::centredTop, true);
}
/**
 * sets bounds for buttons and other elements after resize
 * bounds are determined by a rectangle type which can be set by points or coordinates
 * get Local Bounds gets the max size of the window use that to set new bounds
 */
void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    //auto border = 4;
    auto area = getLocalBounds();
    auto area2 = getLocalBounds();
    auto area3 = getLocalBounds();
    //auto areaTwo = getLocalBounds();
    //What if we use multiple area variables so that multiple buttons can be made

    //auto buttonHeight = 30;
    area.setBounds(130,170,160,80);//function is coordinates and size in order of numbers is x,y,width,height
    area2.setBounds(310, 170, 160, 80);
    area3.setBounds(260, 110, 80, 40);
    // You can change button size and location here. Still need to find how to modify width to put buttons side by side
        button1.setBounds(area);//sets size
        button2.setBounds(area2);
        button3.setBounds(area3);

        //button2.setBounds (area.removeFromBottom (buttonHeight).reduced (2 /border));
        //button3.setBounds (area.removeFromBottom (buttonHeight).reduced (2 / border));
        //button1.setTopLeftPosition(150,400);//set position of buttons


}
/**
 * draws button and creates style for buttons
 * @param g
 * @param button
 * @param backgroundColour
 * @param isButtonDown
 */
void MainComponent::drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour,bool isButtonDown)
{
    auto buttonArea = button.getLocalBounds();
    auto edge = 4;

    buttonArea.removeFromLeft (edge);
    buttonArea.removeFromTop (edge);

    //creating the shadows
    g.setColour(juce::Colours::darkgrey.withAlpha (0.5F));
    g.fillRect(buttonArea);

    //shadow offsets
    auto offset = isButtonDown ? -edge /2 : -edge;
    buttonArea.translate (offset, offset);

    //Setting button color
    g.setColour (backgroundColour);
    g.fillRect (buttonArea);
}
