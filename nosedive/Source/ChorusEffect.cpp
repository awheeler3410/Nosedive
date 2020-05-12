/*
  ==============================================================================

    ChorusEffect.cpp
    Created: 6 May 2020 2:01:04am
    Author:  Andrew Wheeler

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ChorusEffect.h"

//==============================================================================
ChorusEffect::ChorusEffect(NosediveAudioProcessor& p)
: processor (p)
{
    chorusFrequency.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    chorusFrequency.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    chorusFrequency.setRange(0.0f, 20.0f, 0.01f);
    chorusFrequency.setTextValueSuffix(" Hz");
    addAndMakeVisible(chorusFrequency);
    chorusFrequencyLabel.setText("Frequency", dontSendNotification);
    chorusFrequencyLabel.setFont(Font("Quicksand", "Regular", 24.0f));
    chorusFrequencyLabel.setJustificationType(Justification::centred);
    chorusFrequencyLabel.attachToComponent(&chorusFrequency, false);
    addAndMakeVisible(chorusFrequencyLabel);
    
    chorusIntensity.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    chorusIntensity.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    chorusIntensity.setRange(0.0f, 100.0f, 1.0f);
    chorusIntensity.setTextValueSuffix(" %");
    addAndMakeVisible(chorusIntensity);
    chorusIntensityLabel.setText("Intensity", dontSendNotification);
    chorusIntensityLabel.setFont(Font("Quicksand", "Regular", 24.0f));
    chorusIntensityLabel.setJustificationType(Justification::centred);
    chorusIntensityLabel.attachToComponent(&chorusIntensity, false);
    addAndMakeVisible(chorusIntensityLabel);
    
    chorusMix.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    chorusMix.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    chorusMix.setRange(0.0f, 100.0f, 0.01f);
    chorusMix.setTextValueSuffix(" %");
    addAndMakeVisible(chorusMix);
    chorusMixLabel.setText("Mix", dontSendNotification);
    chorusMixLabel.setFont(Font("Quicksand", "Regular", 24.0f));
    chorusMixLabel.setJustificationType(Justification::centred);
    chorusMixLabel.attachToComponent(&chorusMix, false);
    addAndMakeVisible(chorusMixLabel);
    
    //adds the slider values to the value tree
    cFrequencyValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.chorusParams, "CFREQUENCY", chorusFrequency);
    cIntensityValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.chorusParams, "CINTENSITY", chorusIntensity);
    cMixValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.chorusParams, "CMIX", chorusMix);
}

ChorusEffect::~ChorusEffect()
{
}

void ChorusEffect::paint (Graphics& g)
{
    auto colour1 = Colours::darkorange;
    auto colour2 = Colours::black;
    auto darkerorange = colour1.interpolatedWith(colour2, 0.25f);
    g.fillAll(darkerorange);
    
    Rectangle<float> knobArea (25, 85, getWidth() - 50, 190);
    g.setColour(Colours::white);
    g.drawRoundedRectangle(knobArea, 20.0f, 2.0f);
    
    g.setFont(Font("Leckerli One", "Regular", 80.0f));
    g.drawText("Chorus", 190, 30, 300, 20, Justification::centred);
}

void ChorusEffect::resized()
{
    int knobSize = 125;
    int knobSpace = 10;
    //draws each slider to the screen relative to the plugin size
    chorusFrequency.setBounds(getWidth() / 2 - (1.5 * knobSize + knobSpace), getHeight() / 2 - 20, knobSize, knobSize);
    chorusIntensity.setBounds(getWidth() / 2 - (0.5 * knobSize), getHeight() / 2 - 20, knobSize, knobSize);
    chorusMix.setBounds(getWidth() / 2 + (0.5 * knobSize + knobSpace), getHeight() / 2 - 20, knobSize, knobSize);
}
