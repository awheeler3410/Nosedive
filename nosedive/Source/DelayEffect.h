/*
  ==============================================================================

    DelayEffect.h
    Created: 8 May 2020 9:57:36pm
    Author:  Andrew Wheeler

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class DelayEffect    : public Component
{
public:
    DelayEffect(NosediveAudioProcessor&);
    ~DelayEffect();

    void paint (Graphics&) override;
    void resized() override;

private:
    NosediveAudioProcessor& processor;

    Slider delayTime;
    Slider delayFeedback;
    Slider delayMix;
    Label delayTimeLabel;
    Label delayFeedbackLabel;
    Label delayMixLabel;
    
public:
    //creates a unique pointer to a new slider attachment value store in the tree
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> dTimeValue;
1    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> dFeedbackValue;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> dMixValue;    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayEffect)
};
