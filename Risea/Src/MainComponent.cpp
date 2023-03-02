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
        button1OnClick();
    };

    //creating the second button
    //button2.setButtonText("Mode: Music Synthesis");
    button2.onClick = [this] {
        button2OnClick();
    };

    //creating the third button
    //button3.setButtonText("Help");
    button3.onClick = [this] {
        button3OnClick();
    };

    addAndMakeVisible (&button1);
    addAndMakeVisible (&button2);
    addAndMakeVisible (&button3);


}

//==============================================================================
/**
 * function for button click on button 1
 * opens new window and makes it visible
 */
void MainComponent::button1OnClick()
{
    if(TtsWindow)
        TtsWindow->broughtToFront();
    else
    {
        TtsWindow.reset(new TTSwindow("Text to speech"));//declares class this way with the pointer as described by JUCE
        TtsWindow->centreWithSize(600,400);
        TtsWindow->setVisible(true);
    }
}
/**
 * function of button 2
 * opens music window and brings to front
 */
void MainComponent::button2OnClick()
{
    if(Mswindow)
        Mswindow->broughtToFront();
    else
    {
        Mswindow.reset(new MSwindow("Music"));//declares class this way with the pointer as described by JUCE
        Mswindow->centreWithSize(600, 400);
        Mswindow->setVisible(true);
    }
}
/**
 * function for button 3
 * creates new window for help and brings it to the front
 */
void MainComponent::button3OnClick()
{
    if(Helpwindow)
        Helpwindow->broughtToFront();
    else
    {
        Helpwindow.reset(new HELPwindow("Help"));//declares class this way with the pointer as described by JUCE
        Helpwindow->centreWithSize(600, 400);
        Helpwindow->setVisible(true);
    }
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
