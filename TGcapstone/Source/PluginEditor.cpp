#include "PluginProcessor.h"
#include "PluginEditor.h"

TgcapstoneAudioProcessorEditor::TgcapstoneAudioProcessorEditor (TgcapstoneAudioProcessor& p)
    : AudioProcessorEditor (&p)
{
    setSize (400, 400);
    
    /*
     *      Delay Components
     */
    
    // Delay On/Off
    delayOnOff.setButtonText("OFF");
    addAndMakeVisible(&delayOnOff);
    delayOnOff.addListener(this);
    
    // Delay Time
    delayTime.setSliderStyle(Slider::LinearHorizontal);
    delayTime.setRange(0, 1, 0.01);
    delayTime.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    delayTime.setPopupDisplayEnabled(true, this);
    delayTime.setTextValueSuffix(" Delay");
    delayTime.setValue(0.5);
    
    addAndMakeVisible(&delayTime);
    delayTime.addListener(this);
    
    // Dry Delay
    dryDelay.setSliderStyle(Slider::LinearHorizontal);
    dryDelay.setRange(0, 1, 0.1);
    dryDelay.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    dryDelay.setPopupDisplayEnabled(true, this);
    dryDelay.setTextValueSuffix(" Dry Signal");
    dryDelay.setValue(0.5);
    
    addAndMakeVisible(&dryDelay);
    dryDelay.addListener(this);
    
    // Wet Delay
    wetDelay.setSliderStyle(Slider::LinearHorizontal);
    wetDelay.setRange(0, 1, 0.1);
    wetDelay.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    wetDelay.setPopupDisplayEnabled(true, this);
    wetDelay.setTextValueSuffix(" Wet Signal");
    wetDelay.setValue(0.5);
    
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
    
    /*
     *      Distortion Components
     */
    
    // Distortion Gain
    distortion.setSliderStyle(Slider::LinearBarVertical);
    distortion.setRange(0, 10, 0.01);
    distortion.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    distortion.setPopupDisplayEnabled(true, this);
    distortion.setTextValueSuffix(" Gain");
    distortion.setValue(1.0);
    
    addAndMakeVisible(&distortion);
    distortion.addListener(this);
    
    /*
     *      Distortion Combobox
     */
    distSelect.setText("Off");
    addAndMakeVisible(&distSelect);
    distSelect.addItem("Off", 1);
    distSelect.addItem("Full-wave Rectifier", 2);
    distSelect.addItem("Half-wave Rectifier", 3);
    distSelect.addItem("Hard clipping", 4);
    distSelect.addItem("Soft clipping (poly)", 5);
    distSelect.addItem("Soft clipping (exp)", 6);
    distSelect.addListener(this);
        
}

TgcapstoneAudioProcessorEditor::~TgcapstoneAudioProcessorEditor()
{
    // deletes any instances of children components on the heap when the parent component itself is destroyed
    //deleteAllChildren();
}

void TgcapstoneAudioProcessorEditor::paint (Graphics& g)
{
    //fill the whole window
    g.fillAll (Colours::black);

    //set the current drawing color
    g.setColour (Colours::whitesmoke);
    
    //set the font size
    g.setFont (45.0f);
    g.drawFittedText ("Taylor's Guitar Pedal", 0, 0, getWidth(), 60, Justification::centred, 1);
    
    g.setFont(15.0f);
    g.drawFittedText("Gain:", 300, 50, 80, 10, Justification::left, 1);
    g.drawFittedText("Delay Bypass", 95, 160, 80, 10, Justification::left, 1);
    g.drawFittedText("Distortion Type:", 30, 80, 200, 10, Justification::left, 1);
    g.drawFittedText("Delay Time:", 30, 200, 80, 10, Justification::left, 1);
    g.drawFittedText("Dry Signal:", 30, 250, 80, 10, Justification::left, 1);
    g.drawFittedText("Wet Signal:", 30, 300, 80, 10, Justification::left, 1);
    g.drawFittedText("Feedback:", 30, 350, 80, 10, Justification::left, 1);

}

void TgcapstoneAudioProcessorEditor::resized()
{
    //Places components in a resizable boundry
    delayOnOff.setBounds(30, 140, 50, 50);
    delayTime.setBounds(40, 200, 320, 50);
    dryDelay.setBounds(40, 250, 320, 50);
    wetDelay.setBounds(40, 300, 320, 50);
    feedbackDelay.setBounds(40, 350, 320, 50);
    distortion.setBounds(300, 70, 20, 100);
    distSelect.setBounds(30, 100, 180, 30);
}

void TgcapstoneAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider == &delayTime)
    {
        getProcessor().delayT = delayTime.getValue();
    }
    else if (slider == &dryDelay)
    {
        getProcessor().dryD = dryDelay.getValue();
    }
    else if (slider == &wetDelay)
    {
        getProcessor().wetD = wetDelay.getValue();
    }
    else if (slider == &feedbackDelay)
    {
        getProcessor().feedbackD = feedbackDelay.getValue();
    }
    else if (slider == &distortion)
    {
        getProcessor().distortion = distortion.getValue();
    }
    
}

void TgcapstoneAudioProcessorEditor::buttonClicked (Button* button)
{
    if (button == &delayOnOff)
    {
        if (getProcessor().delayOnOff)
        {
            delayOnOff.setButtonText("OFF");
            getProcessor().delayOnOff = false;
        }
        else
        {
            delayOnOff.setButtonText("ON");
            getProcessor().delayOnOff = true;
        }
    }
}

void TgcapstoneAudioProcessorEditor::comboBoxChanged (ComboBox* comboBox)
{
    getProcessor().distortionID = distSelect.getSelectedId();
}
