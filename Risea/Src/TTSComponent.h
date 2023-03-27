#pragma once

#include "juce_gui_extra/juce_gui_extra.h"
#include "juce_analytics/juce_analytics.h"
#include "juce_audio_basics/juce_audio_basics.h"
#include "juce_audio_devices/juce_audio_devices.h"
#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_audio_utils/juce_audio_utils.h"
#include "WavPlayer.h"
//================================================================
class TTSComponent : public juce::AudioAppComponent,
private juce::Timer
{
public:
    TTSComponent();
    void paint (juce::Graphics&) override;
    void resized() override;
    void drawButtonBackground(juce::Graphics&, juce::Button&, const juce::Colour&, bool);
//Testing Drop Down 
    void voiceMenuChanged();
    void releaseResources() override;
    void prepareToPlay(int, double) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo&) override;


private:
    juce::TextButton PPButton;
    void PPButtonOnClick(); //for the Play/Pause button Lambda function
    
    juce::TextEditor textEditor;
    void EnterText();

//Testing dropdown
    juce::ComboBox voiceMenu;
    void testButtonOnClick(); //for the test button Lambda function

    void timerCallback() override;
    void setMidiInput(int index);

    SynthAudioSource audioSource;
    juce::MidiKeyboardState keyboardState;
    juce::MidiKeyboardComponent keyboardComponent;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TTSComponent)
};