#include "PluginProcessor.h"
#include "PluginEditor.h"

StringArray TnpCasioMt40AudioProcessorEditor::casioMT40_tones{
    "elec. piano", "banjo", "guitar", "harpsichord",
    "xylophone", "celesta", "glockenspiel", "organ",
    "accordion", "pipe organ", "oriental pipe", "brass",
    "cello", "synth fuzz", "violin", "trumpet",
    "funny fuzz", "st. ensemble", "clarinet", "flute",
    "recorder", "folk flute", "bass", "rock"
};

StringArray TnpCasioMt40AudioProcessorEditor::casioRPMN_tones{
    "agogo", "ambulance", "band hit-brass", "bells",
    "brass ens", "car horn", "church bells", "e bass",
    "echo brass", "emergency alarm", "e organ", "flute",
    "gamelan", "metal guitar", "orchestra hit", "piano",
    "sitar", "synth lead", "synth reed", "twinkle echo",
    "vibraphone", "vocoder", "warm strings", "waw voice"
};

StringArray TnpCasioMt40AudioProcessorEditor::casioSA10_tones{
    "accordion", "basson", "cello", "e piano", "flute",
    "honkypiano", "metalguitar", "piano", "poplead",
    "synthaccordion", "synthbrass", "synthlead"
};

StringArray TnpCasioMt40AudioProcessorEditor::casioSK1_tones{
    "brass", "flute", "organ", "piano", "pipeorgan",
    "synthdrum", "trumpet", "voice"
};

TnpCasioMt40AudioProcessorEditor::TnpCasioMt40AudioProcessorEditor (TnpCasioMt40AudioProcessor& p)
    : AudioProcessorEditor (&p),
    processor (p),
    treeState (p.getTreeState()),
    keyboard (p.getMidiState(), MidiKeyboardComponent::horizontalKeyboard)
{
    labelKeyboard.setText("Keyboard", dontSendNotification);
    labelKeyboard.attachToComponent(&comboKeyboard, true);
    labelKeyboard.setColour(Label::textColourId, Colours::white);

    labelTone.setText("Tone", dontSendNotification);
    labelTone.attachToComponent(&comboTone, true);
    labelTone.setColour(Label::textColourId, Colours::white);

    addAndMakeVisible(comboKeyboard);
    addAndMakeVisible(comboTone);

    comboKeyboard.setColour(ComboBox::backgroundColourId, Colours::white);
    comboKeyboard.setColour(ComboBox::textColourId, Colours::black);
    comboKeyboard.setColour(ComboBox::arrowColourId, Colours::black);
    comboKeyboard.setColour(ComboBox::outlineColourId, Colours::white);
    comboTone.setColour(ComboBox::backgroundColourId, Colours::white);
    comboTone.setColour(ComboBox::textColourId, Colours::black);
    comboTone.setColour(ComboBox::arrowColourId, Colours::black);
    comboTone.setColour(ComboBox::outlineColourId, Colours::white);

    if (auto* choiceParameter = dynamic_cast<AudioParameterChoice*>(treeState.getParameter("keyboard")))
        comboKeyboard.addItemList(choiceParameter->choices, 1);

    comboKeyboard.addListener(this);
    comboTone.addListener(this);

    attachmentKeyboard = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(treeState, "keyboard", comboKeyboard);

    if (comboKeyboard.getSelectedId() == 0)
        comboKeyboard.setSelectedId(1);

    keyboardChanged();

    attachmentTone = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(treeState, "tone", comboTone);

    sustainToggle.setButtonText("Sustain");
    sustainToggle.setColour(ToggleButton::textColourId, Colours::white);
    addAndMakeVisible(sustainToggle);
    sustainToggle.addListener(this);
    attachmentSustain = std::make_unique<AudioProcessorValueTreeState::ButtonAttachment>(treeState, "sustain", sustainToggle);

    keyboard.setKeyWidth(20);
    keyboard.setAvailableRange(24, 96);
    addAndMakeVisible(keyboard);

    setSize(520, 280);
}

TnpCasioMt40AudioProcessorEditor::~TnpCasioMt40AudioProcessorEditor()
{
}

void TnpCasioMt40AudioProcessorEditor::paint (Graphics& g)
{
    auto area = getLocalBounds();
    g.setColour(Colour(0xff2a2a2a));
    g.fillRect(area.removeFromTop(40));
    g.fillAll(Colour(0xff3a3a3a));

    g.setColour(Colours::white);
    g.setFont(Font(18.0f, Font::bold));
    g.drawText("Casio MT-40", 10, 8, 200, 24, Justification::centredLeft);
    g.setFont(Font(12.0f));
    g.setColour(Colours::lightgrey);
    g.drawText("MIDI Sampler", 10, 26, 200, 14, Justification::centredLeft);
}

void TnpCasioMt40AudioProcessorEditor::resized()
{
    auto area = getLocalBounds();

    auto headerArea = area.removeFromTop(40);
    ignoreUnused(headerArea);

    auto comboArea = area.removeFromTop(50).reduced(10, 8);
    comboKeyboard.setBounds(comboArea.removeFromLeft(240).withTrimmedLeft(50));
    comboTone.setBounds(comboArea.withTrimmedLeft(50));

    sustainToggle.setBounds(area.removeFromTop(24).withTrimmedLeft(10));

    keyboard.setBounds(area.reduced(10, 4));
}

void TnpCasioMt40AudioProcessorEditor::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{
    if (&comboKeyboard == comboBoxThatHasChanged)
        keyboardChanged();
}

void TnpCasioMt40AudioProcessorEditor::buttonClicked(Button*)
{
}

void TnpCasioMt40AudioProcessorEditor::keyboardChanged()
{
    int keyboardParam = comboKeyboard.getSelectedId();
    int toneParam = *treeState.getRawParameterValue("tone");
    int convertedToneParam = 0;

    switch(keyboardParam)
    {
    case 1:
        comboTone.clear();
        comboTone.addItemList(casioMT40_tones, 1);
        comboTone.setSelectedItemIndex(toneParam);
        break;
    case 2:
        comboTone.clear();
        comboTone.addItemList(casioRPMN_tones, 1);
        comboTone.setSelectedItemIndex(toneParam);
        break;
    case 3:
        comboTone.clear();
        comboTone.addItemList(casioSA10_tones, 1);
        convertedToneParam = jmap(toneParam, 0, numTones - 1, 0, numSa10Tones - 1);
        comboTone.setSelectedItemIndex(convertedToneParam);
        break;
    case 4:
        comboTone.clear();
        comboTone.addItemList(casioSK1_tones, 1);
        convertedToneParam = jmap(toneParam, 0, numTones - 1, 0, numSk1Tones - 1);
        comboTone.setSelectedItemIndex(convertedToneParam);
        break;
    }
}
