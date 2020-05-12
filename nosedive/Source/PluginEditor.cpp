/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NosediveAudioProcessorEditor::NosediveAudioProcessorEditor (NosediveAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), tremoloEffect(p), chorusEffect(p), delayEffect(p)
{
    effectMenu.setSize(100, 30);
    effectMenu.addItem("Tremolo", 1);
    effectMenu.addItem("Chorus", 2);
    effectMenu.addItem("Delay", 3);
    effectMenu.setSelectedId(1);
    effectMenu.setJustificationType(Justification::centred);
    addAndMakeVisible(&effectMenu);
    effectMenu.addListener(this);
    
    addAndMakeVisible(&effectMenu);
    addAndMakeVisible(&chorusEffect);
    addAndMakeVisible(&delayEffect);
    addAndMakeVisible(&tremoloEffect);
    
    //adds the slider values to the value tree
    effectChoiceValue = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.editorParams, "EFFECTCHOICE", effectMenu);
    
    setSize(475, 300);
}

NosediveAudioProcessorEditor::~NosediveAudioProcessorEditor()
{
}

//==============================================================================
void NosediveAudioProcessorEditor::paint (Graphics& g)
{
}

void NosediveAudioProcessorEditor::resized()
{
    effectMenu.setBounds(25, 25, 100, 30);
    chorusEffect.setBounds(getLocalBounds());
    delayEffect.setBounds(getLocalBounds());
    tremoloEffect.setBounds(getLocalBounds());
}

void NosediveAudioProcessorEditor::comboBoxChanged(ComboBox* box)
{
    if(effectMenu.getSelectedId() == 1)
    {
        tremoloEffect.toFront(true);
    }
    else if(effectMenu.getSelectedId() == 2)
    {
        chorusEffect.toFront(true);
    }
    else if(effectMenu.getSelectedId() == 3)
    {
        delayEffect.toFront(true);
    }
    effectMenu.toFront(true);
}
