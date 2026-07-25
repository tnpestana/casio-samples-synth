/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
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
		  std::make_unique<AudioParameterChoice>("keyboard", "keyboard",
			StringArray("MT-40", "Rapman", "SA-10", "SK-1"), 1),
		  std::make_unique<AudioParameterInt>("tone", "tone", 0, 23, 1)
		}),
    midiState(),
	localKeyboard(0),
	localTone(0)
	
#endif
{
	for (auto i = 0; i < 10; ++i)
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
	for (auto i = 0; i < 128; ++i)
		synth.noteOff(1, i, 0.0f, true);

	WavAudioFormat wavFormat;
	std::unique_ptr<AudioFormatReader> audioReader;
	localKeyboard = (int)*treeState.getRawParameterValue("keyboard");
	localTone = (int)*treeState.getRawParameterValue("tone");
    
    switch (localKeyboard)
    {
        case 0:
        {
            audioReader = (std::unique_ptr<AudioFormatReader>)wavFormat.createReaderFor(new MemoryInputStream(sampleData.CasioMt40[localTone].first, sampleData.CasioMt40[localTone].second, false), true);
            break;
        }
        case 1:
        {
            audioReader = (std::unique_ptr<AudioFormatReader>)wavFormat.createReaderFor(new MemoryInputStream(sampleData.CasioRapman[localTone].first, sampleData.CasioRapman[localTone].second, false), true);
            break;
        }
        case 2:
        {
            // to map [A, B] --> [a, b] use: (val - A)*(b-a)/(B-A) + a
            int convertedLocalTone = localTone * 12 / 24;
            audioReader = (std::unique_ptr<AudioFormatReader>)wavFormat.createReaderFor(new MemoryInputStream(sampleData.CasioSa10[convertedLocalTone].first, sampleData.CasioSa10[convertedLocalTone].second, false), true);
            break;
        }
        case 3:
        {
            // accomodate the combo attachment linear distribution of values by converting the range intervals
            // to map [A, B] --> [a, b] use: (val - A)*(b-a)/(B-A) + a
            int convertedLocalTone = localTone * 8 / 24;
            audioReader = (std::unique_ptr<AudioFormatReader>)wavFormat.createReaderFor(new MemoryInputStream(sampleData.CasioSk1[convertedLocalTone].first, sampleData.CasioSk1[convertedLocalTone].second, false), true);
            break;
        }
        default:
            break;
    }


	BigInteger allNotes;
	allNotes.setRange(0, 128, true);

	synth.clearSounds();
	synth.addSound(new SamplerSound("demo sound",
		*audioReader,
		allNotes,
		60,   // root midi note
		0.01,  // attack time
		0.1,  // release time
		10.0  // maximum sample length
	));
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
	midiCollector.reset(sampleRate);
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
	// the synth always adds its output to the audio buffer, so we have to clear it
	// first..
	buffer.clear();

	midiCollector.removeNextBlockOfMessages(midiMessages, buffer.getNumSamples());

	if (localTone != (int)*treeState.getRawParameterValue("tone") ||
		localKeyboard != (int)*treeState.getRawParameterValue("keyboard"))
		setVoice();

	midiState.processNextMidiBuffer(midiMessages, 0, buffer.getNumSamples(), true);

	// get the synth to process the midi events and generate its output.
	synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
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
