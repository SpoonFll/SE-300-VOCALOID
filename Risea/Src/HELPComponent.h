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

class HelpComponent : public juce::Component
        {
public:
    HelpComponent();
    ~HelpComponent();//this is needed
    /**
     * decrunched the code need to impletment these to see functions
     * windows will still be black without this
     */
    //void paint(juce::Graphics &) override;

    //void resized() override;

    //void drawButtonBackground(juce::Graphics &, juce::Button &, const juce::Colour &, bool);


private:
    juce::TextButton testButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HelpComponent)
};//forgor semicolon