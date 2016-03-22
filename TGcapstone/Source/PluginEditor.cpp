/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
TgcapstoneAudioProcessorEditor::TgcapstoneAudioProcessorEditor (TgcapstoneAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), rms ("rms", "No Change")
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 400);
    
    // gain
    gain.setSliderStyle(Slider::LinearBarVertical);
    gain.setRange(0.0, 1.0, 0.1);
    gain.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    gain.setPopupDisplayEnabled(true, this);
    gain.setTextValueSuffix(" Gain");
    gain.setValue(0.0);
    
    addAndMakeVisible(&gain);
    
    // add the listener to the slider
    gain.addListener(this);
    
    // threshold
    threshold.setSliderStyle(Slider::LinearBarVertical);
    threshold.setRange(0.0, 1.0, 0.1);
    threshold.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    threshold.setPopupDisplayEnabled(true, this);
    threshold.setTextValueSuffix(" Threshold");
    threshold.setValue(0.0);
    
    addAndMakeVisible(&threshold);
    threshold.addListener(this);
    
    // ratio
    ratio.setSliderStyle(Slider::LinearBarVertical);
    ratio.setRange(2, 20, 1);
    ratio.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    ratio.setPopupDisplayEnabled(true, this);
    ratio.setTextValueSuffix(" Ratio");
    ratio.setValue(0);
    
    addAndMakeVisible(&ratio);
    ratio.addListener(this);
    
    // input metering
    
    inputMeterOnOff.setButtonText("ON/OFF");
    addAndMakeVisible(&inputMeterOnOff);
    
    
    
    // add the listener to the button
    inputMeterOnOff.addListener(this);
    
    // testButton
    compressorOnOff.setButtonText("OFF");
    addAndMakeVisible(&compressorOnOff);
    compressorOnOff.addListener(this);
    
    //rms label
    addAndMakeVisible(&rms);
    rms.addListener(this);
    
    /*
     *      Delay Components
     */
    
    // Delay On/Off
    delayOnOff.setButtonText("OFF");
    addAndMakeVisible(&delayOnOff);
    delayOnOff.addListener(this);
    
    // Delay Time
    delayTime.setSliderStyle(Slider::LinearHorizontal);
    delayTime.setRange(0, 1, 0.1);
    delayTime.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    delayTime.setPopupDisplayEnabled(true, this);
    delayTime.setTextValueSuffix(" Delay (msec)");
    delayTime.setValue(0.0);
    
    addAndMakeVisible(&delayTime);
    delayTime.addListener(this);
    
    // Dry Delay
    dryDelay.setSliderStyle(Slider::LinearHorizontal);
    dryDelay.setRange(0, 1, 0.1);
    dryDelay.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    dryDelay.setPopupDisplayEnabled(true, this);
    dryDelay.setTextValueSuffix(" Dry Signal");
    dryDelay.setValue(0.0);
    
    addAndMakeVisible(&dryDelay);
    dryDelay.addListener(this);
    
    // Wet Delay
    wetDelay.setSliderStyle(Slider::LinearHorizontal);
    wetDelay.setRange(0, 1, 0.1);
    wetDelay.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    wetDelay.setPopupDisplayEnabled(true, this);
    wetDelay.setTextValueSuffix(" Wet Signal");
    wetDelay.setValue(0.0);
    
    addAndMakeVisible(&wetDelay);
    wetDelay.addListener(this);
    
    // Feedback Delay
    feedbackDelay.setSliderStyle(Slider::LinearHorizontal);
    feedbackDelay.setRange(0, 1, 0.1);
    feedbackDelay.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    feedbackDelay.setPopupDisplayEnabled(true, this);
    feedbackDelay.setTextValueSuffix(" Delay Feedback");
    feedbackDelay.setValue(0.0);
    
    addAndMakeVisible(&feedbackDelay);
    feedbackDelay.addListener(this);
}

TgcapstoneAudioProcessorEditor::~TgcapstoneAudioProcessorEditor()
{
    // deletes any instances of children components on the heap when the parent component itself is destroyed
    //deleteAllChildren();
}

//==============================================================================
void TgcapstoneAudioProcessorEditor::paint (Graphics& g)
{
    //fill the whole window white
    g.fillAll (Colours::white);

    //set the current drawing color to black
    g.setColour (Colours::black);
    
    //set the font size
    g.setFont (15.0f);
    
    g.drawFittedText ("Gain", 0, 0, getWidth(), 30, Justification::centred, 1);
    
    g.setColour (Colours::seashell.withAlpha(0.9f));
    g.fillRect (0, 0, getWidth()/2, getHeight()/2);
    g.fillRect (getWidth()/2, getHeight()/2, getWidth(), getHeight());
    
    g.setColour(Colours::black.withAlpha(0.5f));
    g.drawRoundedRectangle(10, 160, getWidth()-20, getHeight()/3, 20, 2);
    
    g.setColour(Colours::whitesmoke);
    g.setFont(40);
    g.drawFittedText("painted text", 10, 160, getWidth()-20, getHeight()/3, Justification::centred, 1);
    
}

void TgcapstoneAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    //Places components in a resizable boundry
    gain.setBounds(40, 30, 20, 100);
    threshold.setBounds(60, 30, 20, 100);
    ratio.setBounds(80, 30, 20, 100);
    inputMeterOnOff.setBounds(100, 30, 50, 50);
    compressorOnOff.setBounds(150,100, 50, 50);
    rms.setBounds(80, 100, 50, 50);
    delayOnOff.setBounds(200, 100, 50, 50);
    delayTime.setBounds(40, 200, 320, 50);
    dryDelay.setBounds(40, 250, 320, 50);
    wetDelay.setBounds(40, 300, 320, 50);
    feedbackDelay.setBounds(40, 350, 320, 50);
}

void TgcapstoneAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider == &gain)
    {
        processor.gain = gain.getValue();
    }
    else if (slider == &threshold)
    {
        processor.thresh = threshold.getValue();
    }
    else if (slider == &ratio)
    {
        
    }
    else if (slider == &delayTime)
    {
        processor.delayT = delayTime.getValue();
    }
    else if (slider == &dryDelay)
    {
        processor.dryD = dryDelay.getValue();
    }
    else if (slider == &wetDelay)
    {
        processor.wetD = wetDelay.getValue();
    }
    else if (slider == &feedbackDelay)
    {
        processor.feedbackD = feedbackDelay.getValue();
    }
}

void TgcapstoneAudioProcessorEditor::buttonClicked (Button* button)
{
    if (button == &inputMeterOnOff)
    {
        rms.setCentrePosition(10, 10);
        gain.setValue(.5);
    }
    else if (button == &compressorOnOff)
    {
        if (processor.compOnOff)
        {
            compressorOnOff.setButtonText("OFF");
            processor.compOnOff = false;
        }
        else
        {
            compressorOnOff.setButtonText("ON");
            processor.compOnOff = true;
        }
    }
    else if (button == &delayOnOff)
    {
        if (processor.delayOnOff)
        {
            delayOnOff.setButtonText("OFF");
            processor.delayOnOff = false;
        }
        else
        {
            delayOnOff.setButtonText("ON");
            processor.delayOnOff = true;
        }
    }
}

void TgcapstoneAudioProcessorEditor::changeListenerCallback(ChangeBroadcaster* changeSource)
{
    
}

void TgcapstoneAudioProcessorEditor::labelTextChanged(Label* label)
{
    //rms.setText(String (processor.rmsValueL), NotificationType::dontSendNotification);
    //processor.rmsValueL =
    
}
