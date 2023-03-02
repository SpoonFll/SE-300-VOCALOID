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
#include "HELPComponent.h"
#include "MSComponent.h"
#include "TTSComponent.h"

//==============================================================================

//==============================================================================
// window for TTS Class
/**
 * implements a new window for TTS
 */
class TTSwindow : public juce::DocumentWindow {
public:
    explicit TTSwindow(juce::String name)
            : DocumentWindow(
            name,
            juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(
                    ResizableWindow::backgroundColourId),
            DocumentWindow::allButtons) {
        setUsingNativeTitleBar(true);
        setContentOwned(new TTSComponent(), true); //error

#if JUCE_IOS || JUCE_ANDROID
        setFullScreen(true);
#else
        setResizable(true, true);
        centreWithSize(getWidth(), getHeight());
#endif
        setVisible(true);
    }
    void closeButtonPressed() override {
        juce::JUCEApplication::getInstance()->systemRequestedQuit();
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TTSwindow)
};

//==============================================================================
// window for MS class
class MSwindow : public juce::DocumentWindow {
public:
    explicit MSwindow(juce::String name)
            : DocumentWindow(
            name,
            juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(
                    ResizableWindow::backgroundColourId),
            DocumentWindow::allButtons) {
        setUsingNativeTitleBar(true);
        setContentOwned(new MSComponent(), true);

#if JUCE_IOS || JUCE_ANDROID
        setFullScreen(true);
#else
        setResizable(true, true);
        centreWithSize(getWidth(), getHeight());
#endif
        setVisible(true);
    }
    void closeButtonPressed() override {
        juce::JUCEApplication::getInstance()->systemRequestedQuit();
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MSwindow)
};

//==============================================================================
class HELPwindow : public juce::DocumentWindow {
public:
    explicit HELPwindow(juce::String name)
            : DocumentWindow(
            name,
            juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(
                    ResizableWindow::backgroundColourId),
            DocumentWindow::allButtons) {
        setUsingNativeTitleBar(true);
        setContentOwned(new HelpComponent(), true);

#if JUCE_IOS || JUCE_ANDROID
        setFullScreen(true);
#else
        setResizable(true, true);
        centreWithSize(getWidth(), getHeight());
#endif
        setVisible(true);
    }
    void closeButtonPressed() override {
        juce::JUCEApplication::getInstance()->systemRequestedQuit();
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HELPwindow)
};

/*
    This component lives inside our window, and this is where you should put all
    your controls and content.


    controls main component
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
    std::unique_ptr<TTSwindow> TtsWindow;//adds class
    void button1OnClick();//for button1 lambda function

    juce::TextButton button2;
    std::unique_ptr<MSwindow> Mswindow;//adds class
    void button2OnClick();//for button2 Lambda function

    juce::TextButton button3;
    std::unique_ptr<HELPwindow> Helpwindow;//adds class
    void button3OnClick();//for button3 Lambda function


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};