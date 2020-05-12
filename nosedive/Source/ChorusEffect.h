/*
  ==============================================================================

    ChorusEffect.h
    Created: 6 May 2020 2:01:04am
    Author:  Andrew Wheeler

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class ChorusEffect    : public Component
{
public:
    ChorusEffect(NosediveAudioProcessor&);
    ~ChorusEffect();

    void paint (Graphics&) override;
    void resized() override;

private:
    NosediveAudioProcessor& processor;
    
    Slider chorusFrequency;
    Slider chorusIntensity;
    Slider chorusMix;
    Label chorusFrequencyLabel;
    Label chorusIntensityLabel;
    Label chorusMixLabel;
    
public:
    //creates a unique pointer to a new slider attachment value store in the tree
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> cFrequencyValue;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> cIntensityValue;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> cMixValue;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChorusEffect)
};
