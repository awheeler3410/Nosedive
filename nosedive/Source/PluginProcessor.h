/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class NosediveAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    NosediveAudioProcessor();
    ~NosediveAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //instantiates the process block for each effect
    void tremoloProcessor (AudioBuffer<float>& buffer);
    void chorusProcessor (AudioBuffer<float>& buffer);
    void delayProcessor (AudioBuffer<float>& buffer);
    
    //==============================================================================
    void fillDelayBuffer (int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData);
    void getFromDelayBuffer (AudioBuffer<float>& buffer, int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData, int delayTime, float mix);
    void delayFeedback (int channel, const int bufferLength, const int delayBufferLength, float* dryBuffer, float feedback);
    
    //==============================================================================
    void fillChorusBuffer (int channel, const int bufferLength, const int chorusBufferLength, const float* bufferData, const float* chorusBufferData);
    void getFromChorusBuffer (AudioBuffer<float>& buffer, int channel, const int bufferLength, const int chorusBufferLength, const float* bufferData, const float* chorusBufferData, float delayTime, float mix);
        
    //==============================================================================
    //value tree states that store effect parameters
    AudioProcessorValueTreeState editorParams;
    AudioProcessorValueTreeState tremoloParams;
    AudioProcessorValueTreeState chorusParams;
    AudioProcessorValueTreeState delayParams;
    
    //parameter layouts used to better organize each parameter being added its corrosponding tree
    AudioProcessorValueTreeState::ParameterLayout editorParameterLayout();
    AudioProcessorValueTreeState::ParameterLayout tremoloParameterLayout();
    AudioProcessorValueTreeState::ParameterLayout chorusParameterLayout();
    AudioProcessorValueTreeState::ParameterLayout delayParameterLayout();
    
private:
    AudioBuffer<float> mChorusBuffer;
    AudioBuffer<float> mDelayBuffer;
    
    float freq;
    
    int mWritePosition { 0 };
    int mSampleRate{ 44100 };
    float phase { 0.0 };
    float incr { 0.0 };
    float PI_double { 2 * float_Pi };
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NosediveAudioProcessor)
};
