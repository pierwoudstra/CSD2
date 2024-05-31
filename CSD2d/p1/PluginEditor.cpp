#include "PluginEditor.h"
#include "PluginProcessor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(
    AudioPluginAudioProcessor &p, juce::AudioProcessorValueTreeState &Reference)
    : AudioProcessorEditor(&p), ref(Reference), processorRef(p) {

  juce::ignoreUnused(processorRef);

  /*
   * set look & feel
   */

  juce::LookAndFeel::setDefaultLookAndFeel(&customLNF);

  // detune knob
  detuneKnob.setSliderStyle(
      juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  detuneKnob.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 50, 20);
  detuneKnobAttachment =
      std::make_unique<SliderAttachment>(ref, "detuneKnob", detuneKnob);

  detuneKnob.onValueChange = [this] {
    xyPad.sliderValueChanged(&detuneKnob);
  };

  // bit depth knob
  bitDepthKnob.setSliderStyle(
      juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  bitDepthKnob.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 50, 20);
  bitDepthKnobAttachment =
      std::make_unique<SliderAttachment>(ref, "bitDepthKnob", bitDepthKnob);

  bitDepthKnob.onValueChange = [this] {
    xyPad.sliderValueChanged(&bitDepthKnob);
  };


  // mod freq knob
  modFreqKnob.setSliderStyle(
      juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  modFreqKnob.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 50, 20);
  modFreqKnobAttachment =
      std::make_unique<SliderAttachment>(ref, "modFreqKnob", modFreqKnob);

  modFreqKnob.onValueChange = [this] {
    xyPad.sliderValueChanged(&modFreqKnob);
  };

  // mod depth knob
  modDepthKnob.setSliderStyle(
      juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  modDepthKnob.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 50, 20);
  modDepthKnobAttachment =
      std::make_unique<SliderAttachment>(ref, "modDepthKnob", modDepthKnob);

  modDepthKnob.onValueChange = [this] {
    xyPad.sliderValueChanged(&modDepthKnob);
  };

  // saturation knob
  saturationKnob.setSliderStyle(
      juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  saturationKnob.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 50, 20);
  saturationKnobAttachment =
      std::make_unique<SliderAttachment>(ref, "saturationKnob", saturationKnob);

  saturationKnob.onValueChange = [this] {
    xyPad.sliderValueChanged(&saturationKnob);
  };

  // dry/wet knob
  dryWetKnob.setSliderStyle(
      juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  dryWetKnob.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 50, 20);
  dryWetKnobAttachment =
      std::make_unique<SliderAttachment>(ref, "dryWetKnob", dryWetKnob);

  dryWetKnob.onValueChange = [this] {
    xyPad.sliderValueChanged(&dryWetKnob);
  };

  /*
   * xy-pad
   */

  // assigning sliders to axis
  xyPad.registerSlider(&detuneKnob, Gui::XYPad::Axis::X1);
  xyPad.registerSlider(&bitDepthKnob, Gui::XYPad::Axis::Y1);
  xyPad.registerSlider(&modFreqKnob, Gui::XYPad::Axis::X2);
  xyPad.registerSlider(&modDepthKnob, Gui::XYPad::Axis::Y2);
  xyPad.registerSlider(&saturationKnob, Gui::XYPad::Axis::X3);
  xyPad.registerSlider(&dryWetKnob, Gui::XYPad::Axis::Y3);

  addAndMakeVisible(xyPad);

  setSize(400, 300);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {
  juce::LookAndFeel::setDefaultLookAndFeel(nullptr);

  xyPad.deregisterSlider(&detuneKnob);
  xyPad.deregisterSlider(&bitDepthKnob);
  xyPad.deregisterSlider(&modFreqKnob);
  xyPad.deregisterSlider(&modDepthKnob);
  xyPad.deregisterSlider(&saturationKnob);
  xyPad.deregisterSlider(&dryWetKnob);
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint(juce::Graphics &g) {
  background = juce::ImageCache::getFromMemory(imageData, imageDataSize);

  g.drawImageWithin(background, 0, 0, getWidth(), getHeight(),
                    juce::RectanglePlacement::stretchToFit);
}

void AudioPluginAudioProcessorEditor::resized() {
  xyPad.setBounds(25, 25, 350, 250);
}
