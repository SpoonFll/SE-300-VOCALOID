#include "MSComponent.h"

MSComponent::MSComponent() : PPButton("Play/Pause"), audioSource(keyboardState), keyboardComponent(keyboardState, juce::MidiKeyboardComponent::verticalKeyboardFacingRight)
{
    addAndMakeVisible(&PPButton);
    addAndMakeVisible(insMenu);

    //setting up dropdown for instruments
    insMenu.setTextWhenNothingSelected("Choices");
    insMenu.addItem("Instrument 1", 1);
    insMenu.addItem("Instrument 2", 2);
    insMenu.addItem("Instrument 3", 3);

    insMenu.onChange = [this]
    {
        insMenuChanged();
    };


    //setting PP Button Actions
    PPButton.onClick = [this]
    {
        PPButtonOnClick();
    };

    //setting up piano
    setMidiInput(0);
    addAndMakeVisible(keyboardComponent);
    setAudioChannels(0,2);
    setSize (600, 400);
    startTimer(400);
    audioSource.loadFile();

    addAndMakeVisible(pVolumeSlider);
    pVolumeSlider.setRange(0, 100);
    pVolumeSlider.setTextValueSuffix(" Hz");

    addAndMakeVisible(mVolumeSlider);
    mVolumeSlider.setRange(0, 100);
    pVolumeSlider.setTextValueSuffix(" Hz");


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
    auto pArea = getLocalBounds();
    auto pSliderArea = getLocalBounds();
    auto mSliderArea = getLocalBounds();


    area.setBounds(10, 10, 100, 40);
    newArea.setBounds(1100, 10, 100, 40);
    pArea.setBounds(5, 490, getWidth()/3, getHeight()/3);
    pSliderArea.setBounds(375, 325, 700, 200);
    mSliderArea.setBounds(10, 50, getWidth()/3, getHeight()/3);

    PPButton.setBounds(area);
    insMenu.setBounds(newArea);
    keyboardComponent.setBounds(pArea);

    pVolumeSlider.setBounds(pSliderArea);
    mVolumeSlider.setBounds(mSliderArea);
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
//================================================================
void MSComponent::timerCallback() 
{
    keyboardComponent.grabKeyboardFocus();
    stopTimer();
}
//================================================================
void MSComponent::setMidiInput(int index)
{
    auto list = juce::MidiInput::getAvailableDevices();
    deviceManager.removeMidiInputDeviceCallback(list[0].identifier, audioSource.getMidiCollector());
    auto newInput = list[index];
    if (!deviceManager.isMidiInputDeviceEnabled(newInput.identifier))
        deviceManager.setMidiInputDeviceEnabled(newInput.identifier, true);
    deviceManager.addMidiInputDeviceCallback(newInput.identifier, audioSource.getMidiCollector());
}
//================================================================
void MSComponent::releaseResources()
{

}
//================================================================
void MSComponent::prepareToPlay(int sampleBlocks, double sampleRate)
{
    audioSource.prepareToPlay(sampleBlocks, sampleRate);
}
//================================================================
void MSComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& buffer)
{
    audioSource.getNextAudioBlock(buffer);
}