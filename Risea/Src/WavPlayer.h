#include "juce_analytics/juce_analytics.h"
#include "juce_audio_basics/juce_audio_basics.h"
#include "juce_audio_devices/juce_audio_devices.h"
#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_audio_utils/juce_audio_utils.h"

struct settings {
    float offset;
    float consonant;
    float cutoff;
    float preutterance;
    float overlap;
    juce::File soundFile;
};
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
        DBG("Loading File");
        juce::File file = juce::File("/home/jacksonb/Work/Classes/SE300/SE-300-VOCALOID/VoiceBanks/RISEA_TEST_VOICE_BANK");
        DBG("File loaded");
        //juce::File speakPower =file.getChildFile("B4_Power");
        //juce::File speakPowerConfig = speakPower.getChildFile("oto.ini");
        //DBG(speakPowerConfig.loadFileAsString());
        juce::File speakNatural=file.getChildFile("G4_Natural");
        juce::File speakNaturalConfig = speakNatural.getChildFile("oto.ini");

        juce::String words = speakNaturalConfig.loadFileAsString();
        juce::StringArray lines = juce::StringArray::fromLines(words);
        for(int i =0;i<lines.size();i++)
        {
            juce::StringArray equalsDivide = juce::StringArray::fromTokens(lines.getReference(i),"=,","'");
            if(equalsDivide.size()==7)
            {
                settings set;
                set.soundFile = speakNatural.getChildFile(equalsDivide.getReference(0));
                set.offset = equalsDivide.getReference(2).getFloatValue();
                set.consonant = equalsDivide.getReference(3).getFloatValue();
                set.cutoff = equalsDivide.getReference(4).getFloatValue();
                set.preutterance = equalsDivide.getReference(5).getFloatValue();
                set.overlap = equalsDivide.getReference(6).getFloatValue();
                wordsToSounds[equalsDivide.getReference(1)] = set;
            }
            //DBG(equalsDivide.getReference(0));
            //DBG(equalsDivide.getReference(1));
        }
/*
        set.fileName=words.upToFirstOccurrenceOf("=",false,true);
        juce::String key = words.substring(words.indexOfChar('=')+1,words.indexOfChar(','));

        DBG(set.fileName);
        DBG(key);
*/
        //wordsToSounds["llth-G4"].fileName;
        Reader = Manager.createReaderFor(wordsToSounds["llth-G4"].soundFile);
        juce::BigInteger range;
        range.setRange(0,128,true);
        Voice.addSound(new juce::SamplerSound("Sample", *Reader,range,67,wordsToSounds["llth-G4"].consonant/1000,wordsToSounds["llth-G4"].preutterance/1000,wordsToSounds["llth-G4"].overlap));


    }
    void releaseResources() override{}
    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override
    {
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
    std::unordered_map<juce::String,settings> wordsToSounds;//makes the pronunciation to the sounds string one will be the phonetic and string 2 will be the config settings
    juce::MidiKeyboardState &keyboardState;
    juce::Synthesiser Voice;
    juce::AudioFormatManager Manager;
    juce::AudioFormatReader* Reader{nullptr};
    juce::MidiMessageCollector midiCollector;

};