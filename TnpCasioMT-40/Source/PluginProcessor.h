/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <atomic>
#include "../JuceLibraryCode/JuceHeader.h"
#include "SampleData.h"

//==============================================================================
/**
*/
class TnpCasioMt40AudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    TnpCasioMt40AudioProcessor();
    ~TnpCasioMt40AudioProcessor();

	//==============================================================================
	AudioProcessorValueTreeState& getTreeState();
	MidiKeyboardState& getMidiState();

	//==============================================================================
	void setVoice();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    AudioProcessorValueTreeState treeState;
    MidiKeyboardState midiState;
    Synthesiser synth;
    std::atomic<int> localKeyboard;
	std::atomic<int> localTone;
    SampleData sampleData;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TnpCasioMt40AudioProcessor)
};
