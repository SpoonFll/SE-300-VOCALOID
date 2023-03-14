#include "WavPlayer.h"

WavPlayer::WavPlayer(): juce::AudioProcessor(BusesProperties().withInput("Input",juce::AudioChannelSet::stereo(),true).withOutput("Output",juce::AudioChannelSet::stereo(),
                                                                                                                                  true))
{
    Manager.registerBasicFormats();
    for(int i=0;i<maxVoices;i++)
        Voice.addVoice(new juce::SamplerVoice());

}
WavPlayer::~WavPlayer() noexcept {
    ReaderPtr= nullptr;
}
void WavPlayer::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages) {
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInput= getTotalNumInputChannels();
    auto totalNumOutput= getTotalNumOutputChannels();

    for(auto i = totalNumOutput;i<totalNumOutput;i++)
        buffer.clear(i,0,buffer.getNumSamples());
    Voice.renderNextBlock(buffer,midiMessages,0,buffer.getNumSamples());
}
void WavPlayer::prepareToPlay(double sampleRate, int samplePerBlock) {
    Voice.setCurrentPlaybackSampleRate(sampleRate);

}
void WavPlayer::loadFile() {
    juce::FileChooser chooser {"please load a file"};
    auto file = chooser.getResult();
    ReaderPtr = Manager.createReaderFor(file);
    juce::BigInteger range;
    range.setRange(0,128,true);
    Voice.addSound(new juce::SamplerSound("Risea", *ReaderPtr,range,71,0.1,0.1,5));//edit this to config specs

}