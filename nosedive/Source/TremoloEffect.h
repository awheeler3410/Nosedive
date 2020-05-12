/*
  ==============================================================================

    TremoloEffect.h
    Created: 6 May 2020 3:31:51am
    Author:  Andrew Wheeler

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class TremoloEffect    : public Component
{
public:
    TremoloEffect(NosediveAudioProcessor&);
    ~TremoloEffect();

    void paint (Graphics&) override;
    void resized() override;

private:
    NosediveAudioProcessor& processor;
    
    Slider tremFrequency;
    Slider tremDepth;
    Label tremFrequencyLabel;
    Label tremDepthLabel;
    
public:
    //creates a unique pointer to a new slider attachment value store in the tree
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> tFrequencyValue;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> tDepthValue;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TremoloEffect)
};
