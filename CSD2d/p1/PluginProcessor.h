#pragma once

#include "Effects/BitCrusher.h"
#include "Effects/DownwardCompressor.h"
#include "Effects/PitchShifter.h"
#include "Effects/Tremolo.h"
#include "Effects/Sine.h"

#include <juce_audio_processors/juce_audio_processors.h>

//==============================================================================
class AudioPluginAudioProcessor final : public juce::AudioProcessor,
                                        juce::AudioProcessorValueTreeState::Listener {
public:
  //==============================================================================
  AudioPluginAudioProcessor();
  ~AudioPluginAudioProcessor() override;

  //==============================================================================
  void prepareToPlay(double sampleRate, int samplesPerBlock) override;
  void releaseResources() override;

  bool isBusesLayoutSupported(const BusesLayout &layouts) const override;

  void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;
  using AudioProcessor::processBlock;

  //==============================================================================
  juce::AudioProcessorEditor *createEditor() override;
  bool hasEditor() const override;

  //==============================================================================
  const juce::String getName() const override;

  bool acceptsMidi() const override;
  bool producesMidi() const override;
  bool isMidiEffect() const override;
  double getTailLengthSeconds() const override;

  //==============================================================================
  int getNumPrograms() override;
  int getCurrentProgram() override;
  void setCurrentProgram(int index) override;
  const juce::String getProgramName(int index) override;
  void changeProgramName(int index, const juce::String &newName) override;

  //==============================================================================
  void getStateInformation(juce::MemoryBlock &destData) override;
  void setStateInformation(const void *data, int sizeInBytes) override;

  void printFunc() {
    std::cout << "printing" << std::endl;
  }

  float getSaturationValue() {
    return saturationValue;
  }

private:
  //==============================================================================

  void parameterChanged(const juce::String& parameterID, float newValue) override;

  static std::atomic<float> setDryWet(float wetSignal, float drySignal,
                                      float dryWetValue);

  // controllable fields
  std::atomic<float> *pitch;
  std::atomic<float> *bitDepth;
  std::atomic<float> *modFreq;
  std::atomic<float> *modDepth;
  std::atomic<float> *saturation;
  std::atomic<float> *dryWet;

  float saturationValue;

  // effects
  std::vector<PitchShifter> pitchShifter;
  std::vector<BitCrusher> bitCrusher;
  std::vector<Tremolo> tremolo;
  std::vector<DownwardCompressor> compressor;
  Sine lfo;

  juce::AudioProcessorValueTreeState Params;
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessor)
};
