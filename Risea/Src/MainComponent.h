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

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public juce::Component
{
public:
    //==============================================================================
    MainComponent();//constructor for component

    //==============================================================================
    void paint (juce::Graphics&) override;//paint text and other elements
    void resized() override;//what to do on resize
    void drawButtonBackground(juce::Graphics&, juce::Button&, const juce::Colour&, bool);//create buttons

private:
    //==============================================================================
    // Your private member variables go here..
    juce::TextButton button1;
    Component::SafePointer<juce::TopLevelWindow> window;
    void button1OnClick();//for button1 lambda function


    juce::TextButton button2;
    juce::TextButton button3;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};