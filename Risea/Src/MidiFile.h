#include "juce_analytics/juce_analytics.h"
#include "juce_audio_basics/juce_audio_basics.h"
#include "juce_audio_devices/juce_audio_devices.h"
#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_audio_utils/juce_audio_utils.h"


class MidiFilePlayer : public juce::Thread//, public HighResolutionTimer
{
public:
    MidiFilePlayer(juce::MidiKeyboardState);
    ~MidiFilePlayer();
    bool loadMidiFile(const juce::String);

    // methods controlled by buttons
    void play();
    void stop();
    bool useSustainPedalMessages = false;


private:
    void run() override;

    void playFile();
    void playFile_IgnoreSustainPedal();

    void setTracks();
    void printAllTracks();

    juce::MidiKeyboardState& keyboardState;
    juce::MidiFile theMidiFile;
    juce::MidiMessageSequence * tracks;

    int numTracks;
    bool canPlay = false;
};