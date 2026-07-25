/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class TnpCasioMt40AudioProcessorEditor  : public AudioProcessorEditor,
                                          public ComboBox::Listener
{
public:
    TnpCasioMt40AudioProcessorEditor (TnpCasioMt40AudioProcessor&);
    ~TnpCasioMt40AudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;

private:
    void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;
    void keyboardChanged();

    TnpCasioMt40AudioProcessor& processor;
    AudioProcessorValueTreeState& treeState;

    static StringArray casioMT40_tones;
    static StringArray casioRPMN_tones;
    static StringArray casioSA10_tones;
    static StringArray casioSK1_tones;

    Label labelKeyboard;
    Label labelTone;
    ComboBox comboKeyboard;
    ComboBox comboTone;

    MidiKeyboardComponent keyboard;

    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> attachmentTone;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> attachmentKeyboard;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TnpCasioMt40AudioProcessorEditor)
};
