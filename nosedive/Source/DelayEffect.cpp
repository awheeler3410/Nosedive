/*
  ==============================================================================

    DelayEffect.cpp
    Created: 8 May 2020 9:57:36pm
    Author:  Andrew Wheeler

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DelayEffect.h"

//==============================================================================
DelayEffect::DelayEffect(NosediveAudioProcessor& p)
: processor (p)
{
    delayTime.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    delayTime.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    delayTime.setRange(0, 500, 1);
    delayTime.setTextValueSuffix(" ms");
    addAndMakeVisible(delayTime);
    delayTimeLabel.setText("Delay", dontSendNotification);
    delayTimeLabel.setFont(Font("Quicksand", "Regular", 24.0f));
    delayTimeLabel.setJustificationType(Justification::centred);
    delayTimeLabel.attachToComponent(&delayTime, false);
    addAndMakeVisible(delayTimeLabel);
    
    delayFeedback.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    delayFeedback.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    delayFeedback.setRange(0.0f, 50.0f, 0.1f);
    delayFeedback.setTextValueSuffix(" %");
    addAndMakeVisible(delayFeedback);
    delayFeedbackLabel.setText("Feedback", dontSendNotification);
    delayFeedbackLabel.setFont(Font("Quicksand", "Regular", 24.0f));
    delayFeedbackLabel.setJustificationType(Justification::centred);
    delayFeedbackLabel.attachToComponent(&delayFeedback, false);
    addAndMakeVisible(delayFeedbackLabel);
    
    delayMix.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    delayMix.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    delayMix.setRange(0, 100, 1); //2 as midpoint skew
    delayMix.setTextValueSuffix(" %");
    addAndMakeVisible(delayMix);
    delayMixLabel.setText("Mix", dontSendNotification);
    delayMixLabel.setFont(Font("Quicksand", "Regular", 24.0f));
    delayMixLabel.setJustificationType(Justification::centred);
    delayMixLabel.attachToComponent(&delayMix, false);
    addAndMakeVisible(delayMixLabel);
    
    //adds the slider values to the value tree
    dTimeValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.delayParams, "DTIME", delayTime);
    dFeedbackValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.delayParams, "DFEEDBACK", delayFeedback);
    dMixValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.delayParams, "DMIX", delayMix);
}

DelayEffect::~DelayEffect()
{
}

void DelayEffect::paint (Graphics& g)
{
    auto colour1 = Colours::yellowgreen;
    auto colour2 = Colours::black;
    auto pastelgreen = colour1.interpolatedWith(colour2, 0.40f);
    g.fillAll(pastelgreen);
    
    Rectangle<float> knobArea (25, 85, getWidth() - 50, 190);
    g.setColour(Colours::white);
    g.drawRoundedRectangle(knobArea, 20.0f, 2.0f);
    
    g.setFont(Font("Leckerli One", "Regular", 75.0f));
    g.drawText("Delay", 190, 30, 300, 20, Justification::centred);
}

void DelayEffect::resized()
{
    int knobSize = 125;
    int knobSpace = 10;
    //draws each slider to the screen relative to the plugin size
    delayTime.setBounds(getWidth() / 2 - (1.5 * knobSize + knobSpace), getHeight() / 2 - 20, knobSize, knobSize);
    delayFeedback.setBounds(getWidth() / 2 - (0.5 * knobSize), getHeight() / 2 - 20, knobSize, knobSize);
    delayMix.setBounds(getWidth() / 2 + (0.5 * knobSize + knobSpace), getHeight() / 2 - 20, knobSize, knobSize);
}
