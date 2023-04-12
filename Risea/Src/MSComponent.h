#pragma once
// CMake builds don't use an AppConfig.h, so it's safe to include juce module headers
// directly. If you need to remain compatible with Projucer-generated builds, and
// have called `juce_generate_juce_header(<thisTarget>)` in your CMakeLists.txt,
// you could `#include <JuceHeader.h>` here instead, to make all your module headers visible.
#include "juce_gui_extra/juce_gui_extra.h"
/**
 * @Jackson
 * added in extra headers for music not sure which ones we need yet so I just
 * added a lot to see what we need
 */
#include "juce_analytics/juce_analytics.h"
#include "juce_audio_basics/juce_audio_basics.h"
#include "juce_audio_devices/juce_audio_devices.h"
#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_audio_utils/juce_audio_utils.h"
#include "WavPlayer.h"
//================================================================
class MSComponent : public juce::AudioAppComponent, 
private juce::Timer
{
public:
    MSComponent();
    void paint(juce::Graphics&) override;
    void resized() override;
    void drawButtonBackground(juce::Graphics&, juce::Button&, const juce::Colour&, bool);
    void insMenuChanged();
    void inst1ChoiceChanged();
    void inst2ChoiceChanged();
    void inst3ChoiceChanged();
    void releaseResources() override;
    void prepareToPlay(int, double) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo&);
    
private:
    juce::TextButton PPButton;
    juce::ComboBox insMenu;
    //Drop down for instrument menu
    juce::Synthesiser insChoice;
    //Piano functions
    void timerCallback() override;
    void setMidiInput(int index);
    //Play/Pause button Lambda function
    void PPButtonOnClick();

    SynthAudioSource audioSource;
    juce::MidiKeyboardState keyboardState;
    juce::MidiKeyboardComponent keyboardComponent;

    juce::Slider pVolumeSlider;
    juce::Slider mVolumeSlider;
    juce::Slider vmSlider;
        juce::Slider vmVolumeSlider;
    juce::Slider inst1Slider;
        juce::Slider inst1VolumeSlider;
    juce::Slider inst2Slider;
        juce::Slider inst2VolumeSlider;
    juce::Slider inst3Slider;
        juce::Slider inst3VolumeSlider;

    juce::ComboBox vmMenu;
    juce::ComboBox inst1Menu;
    juce::ComboBox inst2Menu;
    juce::ComboBox inst3Menu;
    juce::ComboBox inst1Choice;
    juce::ComboBox inst2Choice;
    juce::ComboBox inst3Choice;

    juce::TextButton voiceModule; 
    juce::TextButton instModule1;
    juce::TextButton instModule2;
    juce::TextButton instModule3;
    juce::TextButton vmChoice;

    juce::ToggleButton notes[25][50];
      

    Component::SafePointer<juce::TopLevelWindow> MSWindow;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MSComponent)
};
