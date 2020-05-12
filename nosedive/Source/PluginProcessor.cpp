/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NosediveAudioProcessor::NosediveAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
editorParams(*this, nullptr, "EDITORPARAMS", editorParameterLayout()),
tremoloParams(*this, nullptr, "TREMOLOPARAMS", tremoloParameterLayout()),
chorusParams(*this, nullptr, "CHORUSPARAMS", chorusParameterLayout()),
delayParams(*this, nullptr, "DELAYPARAMS", delayParameterLayout())

#endif
{
}

NosediveAudioProcessor::~NosediveAudioProcessor()
{
}

//==============================================================================
//parameters are added to the parameter layout here, and are added to the tree
AudioProcessorValueTreeState::ParameterLayout NosediveAudioProcessor::editorParameterLayout()
{
    std::vector <std::unique_ptr<RangedAudioParameter>> layoutParams;
    
    auto effectChoiceParam = std::make_unique<AudioParameterChoice>("EFFECTCHOICE", "effectChoice", StringArray("Tremolo", "Chorus", "Delay"), 0);

    layoutParams.push_back(std::move(effectChoiceParam));
    
    return { layoutParams.begin(), layoutParams.end() };
}
//parameters are added to the parameter layout here, and are added to the tree
AudioProcessorValueTreeState::ParameterLayout NosediveAudioProcessor::tremoloParameterLayout()
{
    std::vector <std::unique_ptr<RangedAudioParameter>> layoutParams;

    auto tFrequencyParam = std::make_unique<AudioParameterFloat>("TFREQUENCY", "tFrequency", 0.02f, 20.0f, 10.0f);
    auto tDepthParam = std::make_unique<AudioParameterInt>("TDEPTH", "tDepth", 0, 100, 50);

    layoutParams.push_back(std::move(tFrequencyParam));
    layoutParams.push_back(std::move(tDepthParam));
    
    return { layoutParams.begin(), layoutParams.end() };
}
AudioProcessorValueTreeState::ParameterLayout NosediveAudioProcessor::chorusParameterLayout()
{
    std::vector <std::unique_ptr<RangedAudioParameter>> layoutParams;
    
    auto cFrequencyParam = std::make_unique<AudioParameterFloat>("CFREQUENCY", "cFrequency", 0.02f, 20.0f, 10.0f);
    auto cIntensityParam = std::make_unique<AudioParameterFloat>("CINTENSITY", "cIntensity", 0, 100, 50);
    auto cMixParam = std::make_unique<AudioParameterInt>("CMIX", "cMix", 0, 100, 50);

    layoutParams.push_back(std::move(cFrequencyParam));
    layoutParams.push_back(std::move(cIntensityParam));
    layoutParams.push_back(std::move(cMixParam));
    
    return { layoutParams.begin(), layoutParams.end() };
}
AudioProcessorValueTreeState::ParameterLayout NosediveAudioProcessor::delayParameterLayout()
{
    std::vector <std::unique_ptr<RangedAudioParameter>> layoutParams;
    
    auto dTimeParam = std::make_unique<AudioParameterInt>("DTIME", "dTime", 0, 1000, 500);
    auto dFeedbackParam = std::make_unique<AudioParameterFloat>("DFEEDBACK", "dFeedback", 0.0f, 50.0f, 25.0f);
    auto dMixParam = std::make_unique<AudioParameterInt>("DMIX", "dMix", 0, 100, 50);

    layoutParams.push_back(std::move(dTimeParam));
    layoutParams.push_back(std::move(dFeedbackParam));
    layoutParams.push_back(std::move(dMixParam));
    
    return { layoutParams.begin(), layoutParams.end() };
}

const String NosediveAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NosediveAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NosediveAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NosediveAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NosediveAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NosediveAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NosediveAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NosediveAudioProcessor::setCurrentProgram (int index)
{
}

const String NosediveAudioProcessor::getProgramName (int index)
{
    return {};
}

void NosediveAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void NosediveAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    const int numChannels = getTotalNumInputChannels();
    const int delayBufferSize = (sampleRate * samplesPerBlock);
    const int chorusBufferSize = (sampleRate * samplesPerBlock);
    mSampleRate = sampleRate;
    
    mDelayBuffer.setSize(numChannels, delayBufferSize);
    mChorusBuffer.setSize(numChannels, chorusBufferSize);
}

void NosediveAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NosediveAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void NosediveAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    auto boxChoice = editorParams.getRawParameterValue("EFFECTCHOICE");
    
    if(*boxChoice == 0) tremoloProcessor(buffer);
    else if(*boxChoice == 1) chorusProcessor(buffer);
    else if(*boxChoice == 2) delayProcessor(buffer);
}

void NosediveAudioProcessor::tremoloProcessor (AudioBuffer<float>& buffer)
{
    auto freqPointer = tremoloParams.getRawParameterValue("TFREQUENCY");
    auto depthPointer = tremoloParams.getRawParameterValue("TDEPTH");
    float freq = *freqPointer;
    float PI_double = 2 * float_Pi;
    float increment = freq * PI_double / mSampleRate;
    float mod;
    float depth = *depthPointer / 200;
    float offset = 1 - depth;
    float numSamples = buffer.getNumSamples();
    for(int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        for (int sample = 0; sample < numSamples; ++sample)
        {
            mod = offset + depth * sin(phase);
            channelData[sample] *=  mod;
            phase += increment;
            if (phase >= PI_double) phase -= PI_double;
        }
    }
}

void NosediveAudioProcessor::chorusProcessor (AudioBuffer<float>& buffer)
{
    const int bufferLength = buffer.getNumSamples();
    const int chorusBufferLength = mChorusBuffer.getNumSamples();
    for(int channel = 0; channel < getTotalNumInputChannels(); ++channel)
    {
        //create some variables to pass later on
        const float* bufferData = buffer.getReadPointer(channel);
        const float* chorusBufferData = mChorusBuffer.getReadPointer(channel);
        //extract variables from value tree
        auto chorusFrequency = chorusParams.getRawParameterValue("CFREQUENCY");
        auto intensityValue = chorusParams.getRawParameterValue("CINTENSITY");
        auto mixValue = chorusParams.getRawParameterValue("CMIX");
        float mix = (*mixValue/100); 
        float chorusFreq = *chorusFrequency; 
        float incr = PI_double * chorusFreq / mSampleRate;
        float intensity = *intensityValue / 10;
        float phaseVal = sin(phase);
        float delayTime = 15 + phaseVal * intensity;
        phase += incr;
        if (phase >= PI_double) phase -= PI_double;
        
        //create our second buffer and do some manipulation
        fillChorusBuffer(channel, bufferLength, chorusBufferLength, bufferData, chorusBufferData);
        getFromChorusBuffer(buffer, channel, bufferLength, chorusBufferLength, bufferData, chorusBufferData, delayTime, mix);
    }
    mWritePosition += bufferLength;
    mWritePosition %= chorusBufferLength;
}

void NosediveAudioProcessor::fillChorusBuffer (int channel, const int bufferLength, const int chorusBufferLength, const float* bufferData, const float* chorusBufferData)
{
    //copy from main buffer to chorus buffer
    if(chorusBufferLength > bufferLength + mWritePosition)
    {
        mChorusBuffer.copyFrom(channel, mWritePosition, bufferData, bufferLength);
    }
    else
    {
        const int bufferRemaining = chorusBufferLength - mWritePosition;
        mChorusBuffer.copyFrom(channel, mWritePosition, bufferData, bufferRemaining);
        mChorusBuffer.copyFrom(channel, 0, bufferData + bufferRemaining, bufferLength - bufferRemaining);
    }
}

void NosediveAudioProcessor::getFromChorusBuffer (AudioBuffer<float>& buffer, int channel, const int bufferLength, const int chorusBufferLength, const float* bufferData, const float* chorusBufferData, float delayTime, float mix)
{
    const int readPosition = static_cast<int> (chorusBufferLength + mWritePosition - (mSampleRate * delayTime / 1000)) % chorusBufferLength;
    if (chorusBufferLength > bufferLength + readPosition)
    {
        buffer.addFrom(channel, 0, chorusBufferData + readPosition, bufferLength, mix);
    }
    else
    {
        const int bufferRemaining = chorusBufferLength - readPosition;
        buffer.addFrom(channel, 0, chorusBufferData + readPosition, bufferRemaining, mix);
        buffer.addFrom(channel, bufferRemaining, chorusBufferData, bufferLength - bufferRemaining, mix);
    }
}

void NosediveAudioProcessor::delayProcessor (AudioBuffer<float>& buffer)
{
    const int bufferLength = buffer.getNumSamples();
    const int delayBufferLength = mDelayBuffer.getNumSamples();
    for(int channel = 0; channel < getTotalNumInputChannels(); ++channel)
    {
        //create some variables to pass later on
        const float* bufferData = buffer.getReadPointer(channel);
        const float* delayBufferData = mDelayBuffer.getReadPointer(channel);
        float* dryBuffer = buffer.getWritePointer(channel);
        
        //extract variables from value tree
        auto delayTime = delayParams.getRawParameterValue("DTIME");
        auto feedback = delayParams.getRawParameterValue("DFEEDBACK");
        auto mix = delayParams.getRawParameterValue("DMIX");
        float mixValue = (*mix/100);
        float feedbackValue = (*feedback/100);
        int delayTimeValue = *delayTime;
        
        //create our second buffer and do some manipulation
        fillDelayBuffer(channel, bufferLength, delayBufferLength, bufferData, delayBufferData);
        getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData, delayTimeValue, mixValue);
        delayFeedback(channel, bufferLength, delayBufferLength, dryBuffer, feedbackValue);
    }
    mWritePosition += bufferLength;
    mWritePosition %= delayBufferLength;
}

void NosediveAudioProcessor::fillDelayBuffer (int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData)
{
    //copy from main buffer to delay buffer
    if(delayBufferLength > bufferLength + mWritePosition)
    {
        mDelayBuffer.copyFrom(channel, mWritePosition, bufferData, bufferLength);
    }
    else
    {
        const int bufferRemaining = delayBufferLength - mWritePosition;
        mDelayBuffer.copyFrom(channel, mWritePosition, bufferData, bufferRemaining);
        mDelayBuffer.copyFrom(channel, 0, bufferData + bufferRemaining, bufferLength - bufferRemaining);
    }
}

void NosediveAudioProcessor::getFromDelayBuffer (AudioBuffer<float>& buffer, int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData, int delayTime, float mix)
{
    const int readPosition = static_cast<int> (delayBufferLength + mWritePosition - (mSampleRate * delayTime / 1000)) % delayBufferLength;
    if (delayBufferLength > bufferLength + readPosition)
    {
        buffer.addFrom(channel, 0, delayBufferData + readPosition, bufferLength, mix);
    }
    else
    {
        const int bufferRemaining = delayBufferLength - readPosition;
        buffer.addFrom(channel, 0, delayBufferData + readPosition, bufferRemaining, mix);
        buffer.addFrom(channel, bufferRemaining, delayBufferData, bufferLength - bufferRemaining, mix);
    }
}

void NosediveAudioProcessor::delayFeedback (int channel, const int bufferLength, const int delayBufferLength, float* dryBuffer, float feedback)
{
    if(delayBufferLength > bufferLength + mWritePosition)
    {
        mDelayBuffer.addFrom(channel, mWritePosition, dryBuffer, bufferLength, feedback);
    }
    else
    {
        const int bufferRemaining = delayBufferLength - mWritePosition;
        
        mDelayBuffer.addFrom(channel, bufferRemaining, dryBuffer, bufferRemaining, feedback);
        mDelayBuffer.addFrom(channel, 0, dryBuffer, bufferLength - bufferRemaining, feedback);
    }
}

//==============================================================================
bool NosediveAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* NosediveAudioProcessor::createEditor()
{
    return new NosediveAudioProcessorEditor (*this);
}

//==============================================================================
void NosediveAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    auto tremoloState = tremoloParams.copyState();
    auto chorusState = chorusParams.copyState();
    auto delayState = delayParams.copyState();
    std::unique_ptr<XmlElement> xmlTremolo (tremoloState.createXml());
    std::unique_ptr<XmlElement> xmlChorus (chorusState.createXml());
    std::unique_ptr<XmlElement> xmlDelay (delayState.createXml());
    copyXmlToBinary (*xmlTremolo, destData);
    copyXmlToBinary (*xmlChorus, destData);
    copyXmlToBinary (*xmlDelay, destData);
}

void NosediveAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName (tremoloParams.state.getType()))
        {
            tremoloParams.replaceState (ValueTree::fromXml (*xmlState));
        }
        if (xmlState->hasTagName (chorusParams.state.getType()))
        {
            chorusParams.replaceState (ValueTree::fromXml (*xmlState));
        }
        if (xmlState->hasTagName (delayParams.state.getType()))
        {
            delayParams.replaceState (ValueTree::fromXml (*xmlState));
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NosediveAudioProcessor();
} 
