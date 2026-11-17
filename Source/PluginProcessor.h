#pragma once
#include <JuceHeader.h>
#include "SynthVoice.h"
#include "SynthSound.h"

class Osci3000AudioProcessor : public juce::AudioProcessor {
public:
    Osci3000AudioProcessor();
    ~Osci3000AudioProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    // sine -> return std::sin(x);
    // saw -> return x / juce::MathConstants<float>::pi;
    // square -> return x < 0.0f ? -1.0f : 1.0f;
    
    // juce::dsp::Oscillator<float> osc { [](float x) { return std::sin(x); }, 200 };
    // juce::dsp::Oscillator<float> osc { [](float x) { return x / juce::MathConstants<float>::pi; }, 200 };
    // juce::dsp::Oscillator<float> osc { [](float x) { return x < 0.0f ? -1.0f : 1.0f; }, 200 };
    
    // juce::dsp::Gain<float> gain;
    
    juce::Synthesiser synth;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Osci3000AudioProcessor)
};
