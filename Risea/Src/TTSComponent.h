#pragma once

#include "juce_gui_extra/juce_gui_extra.h"

#include "juce_analytics/juce_analytics.h"
#include "juce_audio_basics/juce_audio_basics.h"
#include "juce_audio_devices/juce_audio_devices.h"
#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_audio_utils/juce_audio_utils.h"

//================================================================
class TTSComponent : public juce::Component
{
public:
    TTSComponent();
    void paint (juce::Graphics&) override;
    void resized() override;
    void drawButtonBackground(juce::Graphics&, juce::Button&, const juce::Colour&, bool);
//Testing Drop Down 
    void voiceMenuChanged();


private:
    juce::TextButton PPButton;
    juce::TextButton choiceButton;
    Component::SafePointer<juce::TopLevelWindow> TTSwindow;
    void PPButtonOnClick(); //for the Play/Pause button Lambda function
    void choiceButtonOnClick();

//Testing dropdown
    juce::ComboBox voiceMenu;
    //SynthsizerVoice might be sampler
    juce::SynthesiserVoice voiceChoice;
   // Component::SafePointer<juce::TopLevelWindow> TTSWindow;
    //void voiceMenuOnclick
    juce::Label voiceLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TTSComponent)
};