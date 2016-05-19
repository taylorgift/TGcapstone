#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TgcapstoneAudioProcessor::TgcapstoneAudioProcessor() : delayBuffer(2,1)
{
    // Delay
    delayOnOff = false;
    delayT = 0.5f;
    dryD = 0.5f;
    wetD = 0.5f;
    feedbackD = 0.0f;
    
    // Circular buffer
    delayReadPos = 0;
    delayWritePos = 0;
    delayBuffLength = 1;
    
    // Distortion
    distortionID = 1;
    distortion = 1.0f;
}

TgcapstoneAudioProcessor::~TgcapstoneAudioProcessor()
{
}

//==============================================================================
const String TgcapstoneAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int TgcapstoneAudioProcessor::getNumParameters()
{
    // 7 parameters
    // delayOnOff, delayT, wetD, dryD, feedbackD, distortionID, distortion
    return kNumParameters;
}

float TgcapstoneAudioProcessor::getParameter (int index)
{
    switch (index)
    {
        case kDistortionID:     return distortionID;
        case kDistortion:       return distortion;
        case kDelayOnOffParam:  return delayOnOff;
        case kDelayTParam:      return delayT;
        case kDryParam:         return dryD;
        case kWetParam:         return wetD;
        case kFeedbackParam:    return feedbackD;
        default:                return 0.0f;
    }
}

void TgcapstoneAudioProcessor::setParameter (int index, float newValue)
{
    switch (index)
    {
        case kDistortionID:
            distortionID = newValue;
            break;
        case kDistortion:
            distortion = newValue;
            break;
        case kDelayOnOffParam:
            delayOnOff = newValue;
            break;
        case kDelayTParam:
            delayT = newValue;
            break;
        case kDryParam:
            dryD = newValue;
            break;
        case kWetParam:
            wetD = newValue;
            break;
        case kFeedbackParam:
            feedbackD = newValue;
            break;
        default:
            break;
    }
}

const String TgcapstoneAudioProcessor::getParameterName (int index)
{
    switch (index)
    {
        case kDistortionID:     return "Distortion Select";
        case kDistortion:       return "Distortion";
        case kDelayOnOffParam:  return "Delay On/Off";
        case kDelayTParam:      return "Delay Length";
        case kDryParam:         return "Dry Mix";
        case kWetParam:         return "Wet Mix";
        case kFeedbackParam:    return "Feedback";
        default:                break;
    }
    
    return String::empty;
}

const String TgcapstoneAudioProcessor::getParameterText (int index)
{
    return String (getParameter (index), 2);
}

const String TgcapstoneAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String TgcapstoneAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool TgcapstoneAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool TgcapstoneAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool TgcapstoneAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool TgcapstoneAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool TgcapstoneAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double TgcapstoneAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TgcapstoneAudioProcessor::getNumPrograms()
{
    return 1;
}

int TgcapstoneAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TgcapstoneAudioProcessor::changeProgramName (int index, const String& newName)
{
    
}

void TgcapstoneAudioProcessor::setCurrentProgram(int index)
{
}

const String TgcapstoneAudioProcessor::getProgramName (int index)
{
    return String();
}

void TgcapstoneAudioProcessor::reset()
{
    delayBuffer.clear();
}

void TgcapstoneAudioProcessor::releaseResources()
{
    
}

void TgcapstoneAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Sizing the delay buffer to match the sample rate
    delayBuffLength = (int)(2 * sampleRate);
    
    if (delayBuffLength < 1)
        delayBuffLength = 1;
    
    delayBuffer.setSize(2, delayBuffLength);
    delayBuffer.clear();
    
    // Converting the delay position offset from seconds to samples
    delayReadPos = (int)(delayWritePos - (delayT * getSampleRate()) + delayBuffLength) % delayBuffLength;
}

void TgcapstoneAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // Information on the current block of samples
    const int numInputChannels = getNumInputChannels();
    const int numOutputChannels = getNumOutputChannels();
    const int numSamples = buffer.getNumSamples();
    const int sampleRate = getSampleRate();
    
    // Distortion
    
    for (int channel = 0; channel < numInputChannels; ++channel)
    {
        // Apply distortion gain
        buffer.applyGain(channel, 0, numSamples, distortion);
        
        // Put track audio data into current buffer
        float * originalData = new float;
        originalData = buffer.getSampleData(channel);
        
        if (distortionID != 1)
        {
            if (distortionID == 2)
            {
                // full wave rectifier
                for (int sample = 0; sample < numSamples; ++sample)
                {
                    originalData[sample] = fabs(originalData[sample]);
                }
            }
            else if (distortionID == 3)
            {
                // half wave rectifier
                for (int sample = 0; sample < numSamples; ++sample)
                {
                    if (originalData[sample] <= 0)
                    {
                        originalData[sample] = 0;
                    }
                }
            }
            else if (distortionID == 4)
            {
                // hard clipping
                
                for (int sample = 0; sample < numSamples; ++sample)
                {
                    float thresh = 1.0f;
                    if (originalData[sample] > thresh)
                    {
                        originalData[sample] = thresh;
                    }
                    else if (originalData[sample] < -thresh)
                    {
                        originalData[sample] = -thresh;
                    }
                }
            }
            else if (distortionID == 5)
            {
                // soft clipping based on quadratic function
                
                float thresh1 = 1.0f/3.0f;
                float thresh2 = 2.0f/3.0f;
                
                for (int sample = 0; sample < numSamples; ++sample)
                {
                    if (originalData[sample] > thresh2)
                    {
                        originalData[sample] = 1.0f;
                    }
                    else if (originalData[sample] > thresh1)
                    {
                        originalData[sample] = (3.0f - (2.0f - 3.0f * originalData[sample]) * (2.0f - 3.0f * originalData[sample])) / 3.0f;
                    }
                    else if (originalData[sample] < -thresh2)
                    {
                        originalData[sample] = -1.0f;
                    }
                    else if (originalData[sample] < -thresh1)
                    {
                        originalData[sample] = - (3.0f - (2.0f + 3.0f * originalData[sample]) * (2.0f + 3.0f * originalData[sample])) / 3.0f;
                    }
                    else
                    {
                        originalData[sample] = 2.0f * originalData[sample];
                    }
                }
            }
            else if (distortionID == 6)
            {
                // soft clipping based on exponential function
                
                for (int sample = 0; sample < numSamples; ++sample)
                {
                    if (originalData[sample] > 0)
                    {
                        originalData[sample] = 1.0f - expf(-originalData[sample]);
                    }
                    else
                    {
                        originalData[sample] = -1.0f + expf(originalData[sample]);
                    }
                }
            }
        }
    }
    
    if (delayOnOff)
    {
        // Delay read and write pointers
        int channel, dpr, dpw;
        
        // Processing audio as stereo delay where processing is identical for both channels
        for (channel = 0; channel < numInputChannels; ++channel)
        {
            // set delay time
            delayReadPos = (int)(delayWritePos - delayT * sampleRate + delayBuffLength) % delayBuffLength;
            
            // contains audio of one channel
            float* currentSampleData = buffer.getSampleData(channel);
            // circular buffer for implementing delay on the channel
            float* currentDelayData = delayBuffer.getSampleData(jmin(channel, delayBuffer.getNumChannels() - 1));
            
            // temp copy of variables that need to be maintained between processBlock() calls
            dpr = delayReadPos;
            dpw = delayWritePos;
            
            for (int i = 0; i < numSamples; ++i)
            {
                const float in = currentSampleData[i];
                float out = 0.0;
                
                // weighting the current output for with the dry/wet parameters
                out = (dryD * in + wetD * currentDelayData[dpr]);
                
                // put current sample block in the delay buffer
                currentDelayData[dpw] = in + (currentDelayData[dpr] * feedbackD);
                
                if (++dpr >= delayBuffLength)
                    dpr = 0;
                if (++dpw >= delayBuffLength)
                    dpw = 0;
                
                // put output data in the buffer, replace the input
                currentSampleData[i] = out;
            }
        }
        
        // replace the temp copy of variables
        delayReadPos = dpr;
        delayWritePos = dpw;
    }
    
    //Clears output channels that don't have any input data
    for (int i = numInputChannels; i < numOutputChannels; ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
    
}

bool TgcapstoneAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* TgcapstoneAudioProcessor::createEditor()
{
    return new TgcapstoneAudioProcessorEditor (this);
}

void TgcapstoneAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // Outer XML element
    XmlElement xml ("PLUGINSETTINGS");
    
    // add attributes to it
    xml.setAttribute("delayOnOff", delayOnOff);
    xml.setAttribute("delayT", delayT);
    xml.setAttribute("dryD", dryD);
    xml.setAttribute("wetD", wetD);
    xml.setAttribute("feedbackD", feedbackD);
    
    xml.setAttribute("distortionID", distortionID);
    xml.setAttribute("gain", distortion);
    
    copyXmlToBinary(xml, destData);
    
}

void TgcapstoneAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary(data, sizeInBytes));
    
    if (xmlState != 0)
    {
        // make sure that it's actually our type of XML object
        if (xmlState->hasTagName("PLUGINSETTINGS"));
        {
            // pull out parameters
            delayOnOff = (bool)xmlState->getIntAttribute("delayOnOff", delayOnOff);
            delayT = (float)xmlState->getDoubleAttribute("delayT", delayT);
            dryD = (float)xmlState->getDoubleAttribute("dryD", dryD);
            wetD = (float)xmlState->getDoubleAttribute("wetD", wetD);
            feedbackD = (float)xmlState->getDoubleAttribute("feedbackD", feedbackD);
            
            distortionID = xmlState->getIntAttribute("distortionID", distortionID);
            distortion = (float)xmlState->getDoubleAttribute("gain", distortion);
        }
    }
    
}

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TgcapstoneAudioProcessor();
}
