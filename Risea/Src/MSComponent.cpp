#include "MSComponent.h"

MSComponent::MSComponent() : PPButton("Play/Pause"), audioSource(keyboardState), keyboardComponent(keyboardState, juce::MidiKeyboardComponent::verticalKeyboardFacingRight)
{
    addAndMakeVisible(&PPButton);
    addAndMakeVisible(insMenu);
   

//==============================================================================
    //setting up dropdown for instruments
    insMenu.setTextWhenNothingSelected("Choices");
    insMenu.addItem("Instrument 1", 1);
    insMenu.addItem("Instrument 2", 2);
    insMenu.addItem("Instrument 3", 3);

    insMenu.onChange = [this]
    {
        insMenuChanged();
    };
//==============================================================================
    //Dropdown for instrument choices
    inst1Choice.setTextWhenNothingSelected("Choices");
    inst1Choice.addItem("Drums", 1);
    inst1Choice.addItem("Guitar", 2);
    inst1Choice.addItem("Synth", 3);

    inst1Choice.onChange = [this]
    {
        inst1ChoiceChanged();
    };

    inst2Choice.setTextWhenNothingSelected("Choices");
    inst2Choice.addItem("Drums", 1);
    inst2Choice.addItem("Guitar", 2);
    inst2Choice.addItem("Synth", 3);

    inst2Choice.onChange = [this]
    {
        inst2ChoiceChanged();
    };

    inst3Choice.setTextWhenNothingSelected("Choices");
    inst3Choice.addItem("Drums", 1);
    inst3Choice.addItem("Guitar", 2);
    inst3Choice.addItem("Synth", 3);

    inst3Choice.onChange = [this]
    {
        inst3ChoiceChanged();
    };
//==============================================================================
    //setting PP Button Actions
    PPButton.onClick = [this]
    {
        PPButtonOnClick();
    };
//==============================================================================
    //setting up piano
    setMidiInput(0);
    addAndMakeVisible(keyboardComponent);
    setAudioChannels(0,2);
    setSize (600, 400);
    startTimer(400);
    audioSource.loadFile();
//==============================================================================
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

    // addAndMakeVisible(vmChoice);
    addAndMakeVisible(inst1Choice);
    addAndMakeVisible(inst2Choice);
    addAndMakeVisible(inst3Choice);
//==============================================================================
    for(int i =0;i<25;i++)
    {
        for(int j=0;j<50;j++)
        {
            addAndMakeVisible(notes[i][j]);
            addAndMakeVisible(syllable[j]);
            notes[i][j].onStateChange = [this]{
                onToggleButtonStateChange();
            };

        }
    }
    addAndMakeVisible(tempo);
    tempo.onReturnKey =[this]{
        tempoNumber=tempo.getText().getIntValue();
    };

}
//==============================================================================
/**
* paints the basic elements with g graphics object
* @param g
*/
void MSComponent::paint (juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId)); g.setFont(juce::Font (16.0f));
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
    area.setX(area.getX()+area.getWidth());
    tempo.setBounds(area);
    keyboardComponent.setBounds(pArea);

    pVolumeSlider.setBounds(pSliderArea);
    mVolumeSlider.setBounds(mSliderArea);

    voiceModule.setBounds(vModArea1);
    instModule1.setBounds(iModArea1);
    instModule2.setBounds(iModArea2);
    instModule3.setBounds(iModArea3);

    insMenu.setBounds(newArea);
    inst1Choice.setBounds(7, 142, (getWidth()/6) - 4, getHeight()/16);
    inst2Choice.setBounds(7, 232, (getWidth()/6) - 4, getHeight()/16);
    inst3Choice.setBounds(7, 322, (getWidth()/6) - 4, getHeight()/16);

   auto buttonArea = getLocalBounds();
   buttonArea.setBounds(getWidth()/3,440,30,30);
    for(int i =0;i<25;i++)
    {
        for(int j=0;j<50;j++)
        {
            notes[i][j].setBounds(buttonArea);
            buttonArea.setBounds(buttonArea.getX()+buttonArea.getWidth(),buttonArea.getY(),buttonArea.getWidth(),buttonArea.getHeight());
        }
        buttonArea.setBounds(getWidth()/3,buttonArea.getY()+buttonArea.getHeight(),buttonArea.getWidth(),buttonArea.getHeight());
    }
    for(int i =0;i<50;i++)
    {
        syllable[i].setBounds(buttonArea);
        buttonArea.setX(buttonArea.getX()+buttonArea.getWidth());
    }


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
    for(int j = 0; j < endBeat+1; j++) {
        int channel =1;
        for(int i =0;i<25;i++) {
            if(notes[i][j].getToggleState()&&channel<16) {
                DBG(channel);
                keyboardState.noteOn(channel, 80- i, 1);
                channel++;

            }
        }
        //jassert(true);
        juce::Time::waitForMillisecondCounter((60*1000)/(tempoNumber*1000));
        //DBG("BUG");
        keyboardState.allNotesOff(0);
    }

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
void MSComponent::inst1ChoiceChanged()
{
    switch (inst1Choice.getSelectedId())
    {
        case 1:
            break;
        case 2:
            break;
        case 3:
             break;
        default: break;
    }
}
//================================================================
void MSComponent::inst2ChoiceChanged()
{
    switch (inst2Choice.getSelectedId())
    {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        default: break;
    }
}
//================================================================
void MSComponent::inst3ChoiceChanged()
{
    switch (inst3Choice.getSelectedId())
    {
        case 1:
            break;
        case 2:
            break;
        case 3:
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
void MSComponent::onToggleButtonStateChange() {
    for(int j = 0; j < 50; j++) {
        for(int i =0;i<25;i++) {
            if(notes[i][j].getToggleState()) {
                endBeat = j;
                break;
            }
        }
    }
}
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