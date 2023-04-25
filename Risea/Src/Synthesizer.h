#pragma once
#include "juce_analytics/juce_analytics.h"
#include "juce_audio_basics/juce_audio_basics.h"
#include "juce_audio_devices/juce_audio_devices.h"
#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_audio_utils/juce_audio_utils.h"

namespace juce {
    class JUCE_API SineWaveSound : public SynthesiserSound {
    public:
        SineWaveSound() {}

        ~SineWaveSound() override {}

        bool appliesToNote(int midiNoteNumber) override {
            return true;
        }

        bool appliesToChannel(int midiChannel) override {
            if (midiChannel == 2)
                return true;
            return false;
        }

    private:

        JUCE_LEAK_DETECTOR(SineWaveSound);
    };
}
struct SineWaveVoice:public juce::SynthesiserVoice {
    SineWaveVoice() {}

    bool canPlaySound(juce::SynthesiserSound *sound) {
        return dynamic_cast<juce::SineWaveSound *>(sound) != nullptr;
    }

    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound*, int) {
        currentAngle = 0.0;
        level = velocity * 0.15;
        tailOff = 0.0;
        auto cyclesPerSecond = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        auto cyclesPerSample = cyclesPerSecond / getSampleRate();
        angleDelta = cyclesPerSecond * juce::MathConstants<double>::twoPi;
    }

    void stopNote(float, bool allowTailOff) {
        if (allowTailOff) {
            if (tailOff == 0.0)
                tailOff = 1.0;
        } else {
            clearCurrentNote();
            angleDelta = 0.0;
        }
    }

    void pitchWheelMoved(int) override {}

    void controllerMoved(int controllerNumber, int newControllerValue) override {}

    void renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) {
        if(angleDelta!=0.0)
        {
            if(tailOff>0.0)
            {
                while(--numSamples>=0)
                {
                    auto currentSample=(float)(std::sin(currentAngle)*level*tailOff);
                    for(auto i = outputBuffer.getNumChannels();--i>=0;)
                        outputBuffer.addSample(i,startSample,currentSample);
                    currentAngle+=angleDelta;
                    ++startSample;
                    tailOff*=0.99;
                    if(tailOff<=0.005)
                    {
                        clearCurrentNote();
                        angleDelta=0.0;
                        break;
                    }
                }
            }
            else
            {
                while(--numSamples>=0)
                {
                    auto currentSample=(float)(std::sin(currentAngle)*level);
                    for(auto i = outputBuffer.getNumChannels();--i>=0;)
                        outputBuffer.addSample(i,startSample,currentSample);
                    currentAngle+=angleDelta;
                    ++startSample;
                }
            }
        }

    }

    using juce::SynthesiserVoice::renderNextBlock;
private:
    double currentAngle = 0.0, angleDelta = 0.0, level = 0.0, tailOff = 0.0;
};