#include "TTSComponent.h"

// Buttons etc go here
TTSComponent::TTSComponent() : PPButton("Play/Pause"), audioSource(keyboardState), keyboardComponent(keyboardState,juce::MidiKeyboardComponent::horizontalKeyboard)
{
    //keyboardState.noteOn(1,1,15);
    addAndMakeVisible(&PPButton);
    addAndMakeVisible(voiceMenu);
    EnterText();

    
    voiceMenu.setTextWhenNothingSelected("Choices");
    voiceMenu.addItem("Voice 1", 1);
    voiceMenu.addItem("Voice 2", 2);
    voiceMenu.addItem("Voice 3", 3);
    voiceMenu.onChange = [this]
    {
        voiceMenuChanged();
    };
    PPButton.onClick =[this]{
        PPButtonOnClick();
    };
    setMidiInput(0);
    addAndMakeVisible(keyboardComponent);
    setAudioChannels(0,2);
    setSize (600, 400);
    startTimer(400);
    audioSource.loadFile();//loads files
}
//==============================================================================
void TTSComponent::PPButtonOnClick()
{
    
}
//==============================================================================
void TTSComponent:: EnterText()
{     
    addAndMakeVisible(textEditor);   
 
    juce::Rectangle<int> textEditorBounds = getLocalBounds().reduced(20, 60);

    textEditor.setText("Enter your text here");
    textEditor.grabKeyboardFocus();


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

    area.setBounds(10, 10, 100, 40);
    //itty bitty tiny pp button
    newArea.setBounds(490, 10, 100, 40);
    //this will be continued when buttons and other items are implemented
    PPButton.setBounds(area);
    voiceMenu.setBounds(newArea);

    textEditor.setBounds(newArea2.reduced(20, 60));

    keyboardComponent.setBounds(10,40,getWidth()/2,getHeight()/4);
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

void TTSComponent::timerCallback() {
    keyboardComponent.grabKeyboardFocus();
    stopTimer();
}

void TTSComponent::setMidiInput(int index) {
    auto list = juce::MidiInput::getAvailableDevices();
    deviceManager.removeMidiInputDeviceCallback(list[0].identifier,audioSource.getMidiCollector());
    auto newInput=list[index];
    if(!deviceManager.isMidiInputDeviceEnabled(newInput.identifier))
        deviceManager.setMidiInputDeviceEnabled(newInput.identifier, true);
    deviceManager.addMidiInputDeviceCallback(newInput.identifier,audioSource.getMidiCollector());
}

void TTSComponent::releaseResources() {
}

void TTSComponent::prepareToPlay(int sampleBlocks, double sampleRate) {
    audioSource.prepareToPlay(sampleBlocks,sampleRate);
}
void TTSComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo & buffer) {
    audioSource.getNextAudioBlock(buffer);
}
