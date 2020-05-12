/*
  ==============================================================================

    TremoloEffect.cpp
    Created: 6 May 2020 3:31:51am
    Author:  Andrew Wheeler

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TremoloEffect.h"

//==============================================================================
TremoloEffect::TremoloEffect(NosediveAudioProcessor& p)
: processor (p)
{
    tremFrequency.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    tremFrequency.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    tremFrequency.setRange(0.02f, 20.0f, 0.01f);
    tremFrequency.setTextValueSuffix(" Hz");
    addAndMakeVisible(tremFrequency);
    addAndMakeVisible(tremFrequencyLabel);
    tremFrequencyLabel.setText("Frequency", dontSendNotification);
    tremFrequencyLabel.setFont(Font("Quicksand", "Regular", 24.0f));
    tremFrequencyLabel.setJustificationType(Justification::centred);
    tremFrequencyLabel.attachToComponent(&tremFrequency, false);
    
    tremDepth.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    tremDepth.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    tremDepth.setRange(0, 100, 1);
    tremDepth.setTextValueSuffix(" %");
    addAndMakeVisible(tremDepth);
    addAndMakeVisible(tremDepthLabel);
    tremDepthLabel.setText("Depth", dontSendNotification);
    tremDepthLabel.setFont(Font("Quicksand", "Regular", 24.0f));
    tremDepthLabel.setJustificationType(Justification::centred);
    tremDepthLabel.attachToComponent(&tremDepth, false);
    
    //adds the slider values to the value tree
    tFrequencyValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.tremoloParams, "TFREQUENCY", tremFrequency);
    tDepthValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.tremoloParams, "TDEPTH", tremDepth);

}

TremoloEffect::~TremoloEffect()
{
}

void TremoloEffect::paint (Graphics& g)
{
    //sets background color to blend of darkgrey, black, and teal
    auto colour1 = Colours::darkgrey;
    auto colour2 = Colours::black;
    auto colour3 = Colours::teal;
    auto darkgrey = colour1.interpolatedWith(colour2, 0.5f);
    auto darkblue = darkgrey.interpolatedWith(colour3, 0.5f);
    g.fillAll(darkblue);
    
    Rectangle<float> knobArea (25, 85, getWidth() - 50, 190);
    g.setColour(Colours::white);
    g.drawRoundedRectangle(knobArea, 20.0f, 2.0f);
    
    g.setFont(Font("Leckerli One", "Regular", 80.0f));
    g.drawText("Tremolo", 180, 30, 300, 20, Justification::centred);
}

void TremoloEffect::resized()
{
    int knobSize = 140;
    int knobSpace = 40;
    //draws each slider to the screen relative to the plugin size
    tremFrequency.setBounds(getWidth() / 2 - (0.5 * knobSpace + knobSize), getHeight() / 2 - 25, knobSize, knobSize);
    tremDepth.setBounds(getWidth() / 2 + (0.5 * knobSpace), getHeight() / 2 - 25, knobSize, knobSize);
}
