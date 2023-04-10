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

    addAndMakeVisible(voiceModule);
    addAndMakeVisible(instModule1);
    addAndMakeVisible(instModule2);
    addAndMakeVisible(instModule3);


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

    //Piano and Master Volume Sliders
    auto pSliderArea = getLocalBounds();
    auto mSliderArea = getLocalBounds();

    //Module Volume Sliders
    auto vmSliderArea = getLocalBounds();
    auto inst1SliderArea = getLocalBounds();
    auto inst2SliderArea = getLocalBounds();
    auto inst3SliderArea = getLocalBounds();

    //Module Areas
    auto vModArea1 = getLocalBounds();
    auto iModArea1 = getLocalBounds();
    auto iModArea2 = getLocalBounds();
    auto iModArea3 = getLocalBounds();

    //Drop Down Module Areas
    auto vModDDArea1 = getLocalBounds();
    auto iModDDArea1 = getLocalBounds();
    auto iModDDArea2 = getLocalBounds();
    auto iModDDArea3 = getLocalBounds();


    area.setBounds(5, 10, 100, 40);
    newArea.setBounds(1100, 10, 100, 40);
    pArea.setBounds(5, 440, getWidth()/3, getHeight()/2);

    pSliderArea.setBounds(5, 410, getWidth(), 30);
    mSliderArea.setBounds(130, 10, getWidth()/3, 30);

    vModArea1.setBounds(5, 50, getWidth()/6, getHeight()/8);
    iModArea1.setBounds(5, 140, getWidth()/6, getHeight()/8);
    iModArea2.setBounds(5, 230, getWidth()/6, getHeight()/8);
    iModArea3.setBounds(5, 320, getWidth()/6, getHeight()/8);


    PPButton.setBounds(area);
    insMenu.setBounds(newArea);
    keyboardComponent.setBounds(pArea);

    pVolumeSlider.setBounds(pSliderArea);
    mVolumeSlider.setBounds(mSliderArea);

    voiceModule.setBounds(vModArea1);
    instModule1.setBounds(iModArea1);
    instModule2.setBounds(iModArea2);
    instModule3.setBounds(iModArea3);


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