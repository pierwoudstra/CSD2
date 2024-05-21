#include "PluginEditor.h"
#include "PluginProcessor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(
    AudioPluginAudioProcessor &p, juce::AudioProcessorValueTreeState &Reference)
    : AudioProcessorEditor(&p), ref(Reference), processorRef(p) {
  juce::ignoreUnused(processorRef);

  // detune knob
  detuneKnob.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
  detuneKnob.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 30, 10);
  detuneKnobAttachment =
      std::make_unique<SliderAttachment>(ref, "detuneKnob", detuneKnob);

  // bit depth knob
  bitDepthKnob.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
  bitDepthKnob.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 30, 10);
  bitDepthKnobAttachment =
      std::make_unique<SliderAttachment>(ref, "bitDepthKnob", bitDepthKnob);

  // mod freq knob
  modFreqKnob.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
  modFreqKnob.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 30, 10);
  modFreqKnobAttachment =
      std::make_unique<SliderAttachment>(ref, "modFreqKnob", modFreqKnob);

  // mod depth knob
  modDepthKnob.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
  modDepthKnob.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 30, 10);
  modDepthKnobAttachment =
      std::make_unique<SliderAttachment>(ref, "modDepthKnob", modDepthKnob);

  // saturation knob
  saturationKnob.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
  saturationKnob.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 30, 10);
  saturationKnobAttachment =
      std::make_unique<SliderAttachment>(ref, "saturationKnob", saturationKnob);

  // dey/wet knob
  dryWetKnob.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
  dryWetKnob.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 30, 10);
  dryWetKnobAttachment =
      std::make_unique<SliderAttachment>(ref, "dryWetKnob", dryWetKnob);

  addAndMakeVisible(detuneKnob);
  addAndMakeVisible(bitDepthKnob);
  addAndMakeVisible(modFreqKnob);
  addAndMakeVisible(modDepthKnob);
  addAndMakeVisible(saturationKnob);
  addAndMakeVisible(dryWetKnob);

  setSize(400, 300);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint(juce::Graphics &g) {
  g.fillAll(juce::Colours::blue);
}

void AudioPluginAudioProcessorEditor::resized() {
  detuneKnob.setBounds(75, 25, 100, 50);
  bitDepthKnob.setBounds(75, 125, 100, 50);
  modFreqKnob.setBounds(75, 225, 100, 50);
  modDepthKnob.setBounds(225, 25, 100, 50);
  saturationKnob.setBounds(225, 125, 100, 50);
  dryWetKnob.setBounds(225, 225, 100, 50);
}
