#pragma once
#include "juce_analytics/juce_analytics.h"
#include "juce_audio_basics/juce_audio_basics.h"
#include "juce_audio_devices/juce_audio_devices.h"
#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_audio_utils/juce_audio_utils.h"
#include "Synthesizer.h"
/**
 * settings data type for the time settings for individual samples
 */
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
    /**
     * constructor for the audio source
     * takes in a midi key state to determine when a midi even happens
     * @param keyState
     */
    SynthAudioSource(juce::MidiKeyboardState &keyState): keyboardState(keyState)
    {

        Manager.registerBasicFormats();
        for(int i =0;i<4;i++) {
            Voice.addVoice(new juce::SamplerVoice());
            Voice.addVoice(new SineWaveVoice());
        }
        auto sound = new SineWaveVoice();
        Voice.addSound(new juce::SineWaveSound());
            //loadFile();

    }
    /**
     * prepares samples for play making sure the sample reate is correct
     * @param sampleRate
     */
    void prepareToPlay(int, double sampleRate) override
    {
        Voice.setCurrentPlaybackSampleRate(sampleRate);
        midiCollector.reset(sampleRate);
    }
    /**
     * loads all files for a voice into a hashtable to make converting strings to sounds easier
     */
    void loadFile()
    {
        DBG("Loading File");
        juce::File file = juce::File::getSpecialLocation(juce::File::SpecialLocationType::currentApplicationFile).getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getChildFile("VoiceBanks").getChildFile("RISEA_TEST_VOICE_BANK");
        DBG(file.getFullPathName());
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
        DBG(wordsToSounds["llth-G4"].cutoff);
        Voice.addSound(new juce::SamplerSound("Sample", *Reader,range,67,wordsToSounds["llth-G4"].consonant/1000,wordsToSounds["llth-G4"].preutterance/1000,-1*wordsToSounds["llth-G4"].cutoff/1000,wordsToSounds["llth-G4"].offset));
        juce::File drums = file.getParentDirectory().getParentDirectory().getChildFile("Instruments");

        juce::File hat = drums.getChildFile("MC_Hat (10).wav");
        juce::File kick = drums.getChildFile("MC_kick (12).wav");
        juce::File perc = drums.getChildFile("MC_Perc (7).wav");
        juce::File snare = drums.getChildFile("MC_Snare (15).wav");
        juce::File guitar = drums.getChildFile("guitar-single-falling-note.wav");
        HatReader = Manager.createReaderFor(hat);
        KickReader = Manager.createReaderFor(kick);
        PercReader = Manager.createReaderFor(perc);
        SnareReader = Manager.createReaderFor(snare);
        GuitarReader = Manager.createReaderFor(guitar);
        hatSound = new juce::SamplerSound("hat",*HatReader,range,55,0,0,0.71,0);
        hatSound->setChannel(3);
        hatSound->setApplyNote(55);
        Voice.addSound(hatSound);
        kickSound = new juce::SamplerSound("kick",*KickReader,range,56,0,0,0.50,0);
        kickSound->setChannel(3);
        kickSound->setApplyNote(56);
        Voice.addSound(kickSound);
        percSound = new juce::SamplerSound("perc",*PercReader,range,57,0,0,0.71,0);
        percSound->setChannel(3);
        percSound->setApplyNote(57);
        Voice.addSound(percSound);
        snareSound = new juce::SamplerSound("snare",*SnareReader,range,58,0,0,0.71,0);
        snareSound->setChannel(3);
        snareSound->setApplyNote(58);
        Voice.addSound(snareSound);
        guitarSound = new juce::SamplerSound("guitar",*GuitarReader,range,64,0,0,0.71,0);
        guitarSound->setChannel(4);
        Voice.addSound(guitarSound);
    }
    int loadSound(juce::String soundIndex)
    {
        DBG("1");
        auto result = wordsToSounds.find(soundIndex);
        if(result != wordsToSounds.end()) {
            DBG("2");
            Reader = Manager.createReaderFor(wordsToSounds[soundIndex].soundFile);
            juce::BigInteger range;
            range.setRange(0, 128, true);
            Voice.addSound(
                    new juce::SamplerSound("Sample", *Reader, range, 67, wordsToSounds[soundIndex].consonant / 1000,
                                           wordsToSounds[soundIndex].preutterance / 1000,
                                           -1 * wordsToSounds[soundIndex].cutoff / 1000,
                                           wordsToSounds[soundIndex].offset));
            return 0;
        }
        else
        {
            DBG("word not found");
            return 1;
        }
    }
    std::vector<juce::String> getSounds()
    {
        std::vector<juce::String> keys;
        for(auto keypair:wordsToSounds)
        {
            keys.push_back(keypair.first);
        }
        return keys;
    }
    void releaseResources() override{}
    /**
     * processes the sampler and midi events to convert to audio
     * @param bufferToFill
     */
    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override
    {
        bufferToFill.clearActiveBufferRegion();

        juce::MidiBuffer incomingMidi;
        keyboardState.processNextMidiBuffer(incomingMidi,bufferToFill.startSample,bufferToFill.numSamples,true);

        Voice.renderNextBlock(*bufferToFill.buffer,incomingMidi,bufferToFill.startSample,bufferToFill.numSamples);
    }
    /**
     * midi collector
     * @return
     */
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
    juce::AudioFormatReader* HatReader{nullptr};
    juce::SamplerSound* hatSound;
    juce::AudioFormatReader* KickReader{nullptr};
    juce::SamplerSound* kickSound;
    juce::AudioFormatReader* PercReader{nullptr};
    juce::SamplerSound* percSound;
    juce::AudioFormatReader* SnareReader{nullptr};
    juce::SamplerSound* snareSound;
    juce::MidiMessageCollector midiCollector;
    juce::AudioFormatReader* GuitarReader{nullptr};
    juce::SamplerSound* guitarSound;

};
/**
 * variant of the sampler sound
 * @TODO implement functions for proper cutting of values
 */
class VoiceClip: public juce::SynthesiserSound
{
    VoiceClip(){

    }
};