#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class TgcapstoneAudioProcessorEditor  : public AudioProcessorEditor, private Slider::Listener, private ButtonListener, private ComboBox::Listener
{
public:
    TgcapstoneAudioProcessorEditor (TgcapstoneAudioProcessor&);
    ~TgcapstoneAudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;
    
    void sliderValueChanged (Slider* slider) override;
    void buttonClicked (Button* button) override;
    void comboBoxChanged (ComboBox* comboBox);

private:
    TgcapstoneAudioProcessor& getProcessor() const
    {
        return static_cast<TgcapstoneAudioProcessor&> (processor);
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
