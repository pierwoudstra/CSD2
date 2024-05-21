#pragma once

#include "PluginProcessor.h"
#include "StyleSheet.h"

//==============================================================================
class AudioPluginAudioProcessorEditor final
    : public juce::AudioProcessorEditor {
public:
  AudioPluginAudioProcessorEditor(
      AudioPluginAudioProcessor &,
      juce::AudioProcessorValueTreeState &Reference);
  ~AudioPluginAudioProcessorEditor() override;

  //==============================================================================
  void paint(juce::Graphics &) override;
  void resized() override;

private:
  // This reference is provided as a quick way for your editor to
  // access the processor object that created it.

  juce::CustomLNF customLNF;

  juce::AudioProcessorValueTreeState &ref;

  juce::Slider detuneKnob, bitDepthKnob, modFreqKnob, modDepthKnob,
      saturationKnob, dryWetKnob;

  // attachment moet na knob
  using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
  std::unique_ptr<SliderAttachment> detuneKnobAttachment,
      bitDepthKnobAttachment, modFreqKnobAttachment, modDepthKnobAttachment,
      saturationKnobAttachment, dryWetKnobAttachment;

  AudioPluginAudioProcessor &processorRef;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessorEditor)
};
