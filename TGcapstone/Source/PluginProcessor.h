#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class TgcapstoneAudioProcessor  : public AudioProcessor
{
public:
    TgcapstoneAudioProcessor();
    ~TgcapstoneAudioProcessor();

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void reset();

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const String getName() const override;

//    int getNumParameters() override;
//    float getParameter (int index) override;
//    void setParameter (int index, float newValue) override;

    //const String getParameterName (int index) override;
    const String getParameterText (int index) override;

    const String getInputChannelName (int channelIndex) const override;
    const String getOutputChannelName (int channelIndex) const override;
    bool isInputChannelStereoPair (int index) const override;
    bool isOutputChannelStereoPair (int index) const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    AudioProcessorParameter* delayOnOff;
    AudioProcessorParameter* delayT;
    AudioProcessorParameter* dryD;
    AudioProcessorParameter* wetD;
    AudioProcessorParameter* feedbackD;
    AudioProcessorParameter* distortion;
    AudioProcessorParameter* distortionID;
    
    // Adjustable parameters
//    bool delayOnOff;
//    float delayT;
//    float dryD;
//    float wetD;
//    float feedbackD;
//
//    int distortionID;
//    float distortion;
//    
//    enum Parameters
//    {
//        kDistortionID = 0,
//        kDistortion,
//        kDelayOnOffParam,
//        kDelayTParam,
//        kDryParam,
//        kWetParam,
//        kFeedbackParam,
//        kNumParameters
//    };
    
private:
    // Circular buffer for delay implementation
    int delayBuffLength;
    int delayReadPos, delayWritePos;
    AudioSampleBuffer delayBuffer;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TgcapstoneAudioProcessor)
};


#endif
