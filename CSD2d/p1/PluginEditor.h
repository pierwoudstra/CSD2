#pragma once

#include "Components/StyleSheet.h"
#include "Components/XYPad.h"
#include "PluginProcessor.h"

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
  juce::Image background;

  juce::CustomLNF customLNF;

  juce::AudioProcessorValueTreeState &ref;

  juce::Slider detuneKnob, bitDepthKnob, modFreqKnob, modDepthKnob,
      saturationKnob, dryWetKnob;

  Gui::XYPad xyPad;

  // attachment moet na knob
  using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
  std::unique_ptr<SliderAttachment> detuneKnobAttachment,
      bitDepthKnobAttachment, modFreqKnobAttachment, modDepthKnobAttachment,
      saturationKnobAttachment, dryWetKnobAttachment;

  AudioPluginAudioProcessor &processorRef;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessorEditor)
};
