/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "TremoloEffect.h"
#include "ChorusEffect.h"
#include "DelayEffect.h"

//==============================================================================
/**
*/
class NosediveAudioProcessorEditor  : public AudioProcessorEditor,
                                      private ComboBox::Listener
{
public:
    NosediveAudioProcessorEditor (NosediveAudioProcessor&);
    ~NosediveAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void comboBoxChanged(ComboBox*) override;
    
private:
    NosediveAudioProcessor& processor;
    
    ComboBox effectMenu;
    TremoloEffect tremoloEffect;
    ChorusEffect chorusEffect;
    DelayEffect delayEffect;
    
public:
    //creates a unique pointer to a new slider attachment value store in the tree
    std::unique_ptr <AudioProcessorValueTreeState::ComboBoxAttachment> effectChoiceValue;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NosediveAudioProcessorEditor)
};
