/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "SampleData.h"
#include "PluginEditor.h"

//==============================================================================
namespace
{
    constexpr int numVoices = 10;
    constexpr int numMidiNotes = 128;

    constexpr int zoneRoots[] = { 36, 48, 60, 72, 84 };
    constexpr int zoneHalfRange = 6;
    constexpr int zoneWidth = 12;

    constexpr double attackTime = 0.01;
    constexpr double maxSampleLength = 10.0;
}

TnpCasioMt40AudioProcessor::TnpCasioMt40AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
#endif
	),
	treeState(*this, nullptr, "CasioState", 
		{ 
		  std::make_unique<AudioParameterChoice>(ParameterID("keyboard", 1), "keyboard",
			StringArray("MT-40", "Rapman", "SA-10", "SK-1"), 0),
		  std::make_unique<AudioParameterInt>(ParameterID("tone", 1), "tone", 0, numTones - 1, 1),
		  std::make_unique<AudioParameterBool>(ParameterID("sustain", 1), "Sustain", false)
		}),
    midiState(),
	localKeyboard(0),
	localTone(0),
	sampleData(std::make_unique<SampleData>())
	
#endif
{
	for (auto i = 0; i < numVoices; ++i)
		synth.addVoice(new SamplerVoice());
	setVoice();
}

TnpCasioMt40AudioProcessor::~TnpCasioMt40AudioProcessor()
{
}


//==============================================================================
AudioProcessorValueTreeState& TnpCasioMt40AudioProcessor::getTreeState()
{
	return treeState;
}

MidiKeyboardState & TnpCasioMt40AudioProcessor::getMidiState()
{
	return midiState;
}

//==============================================================================
void TnpCasioMt40AudioProcessor::setVoice()
{
	WavAudioFormat wavFormat;
	localKeyboard = (int)*treeState.getRawParameterValue("keyboard");
	localTone = (int)*treeState.getRawParameterValue("tone");

	double releaseTime = *treeState.getRawParameterValue("sustain") >= 0.5f ? 3.0 : 0.1;

	const char* samplePtr = nullptr;
	int sampleSize = 0;

	switch (localKeyboard)
	{
		case 0:
			samplePtr = sampleData->CasioMt40[localTone].first;
			sampleSize = sampleData->CasioMt40[localTone].second;
			break;
		case 1:
			samplePtr = sampleData->CasioRapman[localTone].first;
			sampleSize = sampleData->CasioRapman[localTone].second;
			break;
		case 2:
		{
			int i = jmap((int)localTone, 0, numTones - 1, 0, numSa10Tones - 1);
			samplePtr = sampleData->CasioSa10[i].first;
			sampleSize = sampleData->CasioSa10[i].second;
			break;
		}
		case 3:
		{
			int i = jmap((int)localTone, 0, numTones - 1, 0, numSk1Tones - 1);
			samplePtr = sampleData->CasioSk1[i].first;
			sampleSize = sampleData->CasioSk1[i].second;
			break;
		}
		default:
			return;
	}

	synth.clearSounds();

	for (auto root : zoneRoots)
	{
		BigInteger notes;
		notes.setRange(root - zoneHalfRange, zoneWidth, true);
		auto reader = std::unique_ptr<AudioFormatReader>(
			wavFormat.createReaderFor(
				new MemoryInputStream(samplePtr, sampleSize, false), true));
		if (reader != nullptr)
			synth.addSound(new SamplerSound("demo",
				*reader, notes, root, attackTime, releaseTime, maxSampleLength));
	}
}

//==============================================================================
const String TnpCasioMt40AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TnpCasioMt40AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TnpCasioMt40AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TnpCasioMt40AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TnpCasioMt40AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TnpCasioMt40AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TnpCasioMt40AudioProcessor::getCurrentProgram()
{
    return 0;
}

void TnpCasioMt40AudioProcessor::setCurrentProgram (int index)
{
}

const String TnpCasioMt40AudioProcessor::getProgramName (int index)
{
    return {};
}

void TnpCasioMt40AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void TnpCasioMt40AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	synth.setCurrentPlaybackSampleRate(sampleRate);
}

void TnpCasioMt40AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TnpCasioMt40AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void TnpCasioMt40AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	buffer.clear();

	if (localTone != (int)*treeState.getRawParameterValue("tone") ||
		localKeyboard != (int)*treeState.getRawParameterValue("keyboard"))
	{
		for (auto i = 0; i < numMidiNotes; ++i)
			synth.noteOff(1, i, 0.0f, true);

		if (!voiceNeedsUpdate.exchange(true))
			triggerAsyncUpdate();
	}

	midiState.processNextMidiBuffer(midiMessages, 0, buffer.getNumSamples(), true);

	synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

void TnpCasioMt40AudioProcessor::handleAsyncUpdate()
{
	voiceNeedsUpdate = false;
	setVoice();
}

//==============================================================================
bool TnpCasioMt40AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TnpCasioMt40AudioProcessor::createEditor()
{
	return new TnpCasioMt40AudioProcessorEditor(*this);
}

//==============================================================================
void TnpCasioMt40AudioProcessor::getStateInformation (MemoryBlock& destData)
{
	auto state = treeState.copyState();
	std::unique_ptr<XmlElement> xml(state.createXml());
	copyXmlToBinary(*xml, destData);
}

void TnpCasioMt40AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
	if (xmlState.get() != nullptr)
		if (xmlState->hasTagName(treeState.state.getType()))
			treeState.replaceState(ValueTree::fromXml(*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TnpCasioMt40AudioProcessor();
}
