#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class TgcapstoneAudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener, public ButtonListener, public ComboBox::Listener, public Timer
{
public:
    TgcapstoneAudioProcessorEditor (TgcapstoneAudioProcessor* p);
    ~TgcapstoneAudioProcessorEditor();
    
    void paint (Graphics&) override;
    void resized() override;
    
    void timerCallback();
    void sliderValueChanged (Slider*);
    void buttonClicked (Button* button) override;
    void comboBoxChanged (ComboBox* comboBox);
    
private:
    TgcapstoneAudioProcessor* getProcessor() const
    {
        return static_cast <TgcapstoneAudioProcessor*> (getAudioProcessor());
    }
    
    Slider delayTime,
           dryDelay,
           wetDelay,
           feedbackDelay,
           distortion;
    TextButton delayOnOff;
    ComboBox distSelect;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TgcapstoneAudioProcessorEditor)
};


#endif
