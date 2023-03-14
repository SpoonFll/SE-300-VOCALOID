#include "juce_analytics/juce_analytics.h"
#include "juce_audio_basics/juce_audio_basics.h"
#include "juce_audio_devices/juce_audio_devices.h"
#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_audio_utils/juce_audio_utils.h"

class WavPlayer: public juce::AudioProcessor
{
public:
    WavPlayer();
    ~WavPlayer();
    void loadFile();
    void processBlock(juce::AudioBuffer<float> &,juce::MidiBuffer &) override;
    void prepareToPlay(double, int);
private:
    juce::Synthesiser Voice;
    const int maxVoices {3};
    juce::AudioFormatManager Manager;
    juce::AudioFormatReader* ReaderPtr {nullptr};//change pointer when changing files

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WavPlayer)
};
