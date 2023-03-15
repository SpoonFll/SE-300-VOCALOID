#include "juce_analytics/juce_analytics.h"
#include "juce_audio_basics/juce_audio_basics.h"
#include "juce_audio_devices/juce_audio_devices.h"
#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_audio_utils/juce_audio_utils.h"

class SynthAudioSource: public juce::AudioSource
{
public:
    SynthAudioSource(juce::MidiKeyboardState &keyState): keyboardState(keyState)
    {
        Manager.registerBasicFormats();
        for(int i =0;i<4;i++)
            Voice.addVoice(new juce::SamplerVoice());
        //loadFile();
    }
    void prepareToPlay(int, double sampleRate) override
    {
        Voice.setCurrentPlaybackSampleRate(sampleRate);
        midiCollector.reset(sampleRate);
    }
    void loadFile()
    {
        juce::File file = juce::File("../../VoiceBanks/RISEA_TEST_VOICE_BANK/B4_Power/061.wav");
        DBG("File loaded");
        Reader = Manager.createReaderFor(file);
        juce::BigInteger range;
        range.setRange(0,128,true);
        Voice.addSound(new juce::SamplerSound("Sample", *Reader,range,71,0.1,0.1,5));


    }
    void releaseResources() override{}
    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override
    {
        DBG("new block");
        bufferToFill.clearActiveBufferRegion();

        juce::MidiBuffer incomingMidi;
        keyboardState.processNextMidiBuffer(incomingMidi,bufferToFill.startSample,bufferToFill.numSamples,true);
        Voice.renderNextBlock(*bufferToFill.buffer,incomingMidi,bufferToFill.startSample,bufferToFill.numSamples);
    }
    juce::MidiMessageCollector* getMidiCollector()
    {
        return &midiCollector;
    }

private:
    juce::MidiKeyboardState &keyboardState;
    juce::Synthesiser Voice;
    juce::AudioFormatManager Manager;
    juce::AudioFormatReader* Reader{nullptr};
    juce::MidiMessageCollector midiCollector;

};