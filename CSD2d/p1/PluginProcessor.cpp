#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessor::AudioPluginAudioProcessor()
    : AudioProcessor(
          BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
              .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
              .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
              ),
      Params(*this, nullptr, "Parameters",
             {
                 std::make_unique<juce::AudioParameterFloat>(
                     juce::ParameterID{"detuneKnob", 1}, "detune", -1, 1, 0),
                 std::make_unique<juce::AudioParameterFloat>(
                     juce::ParameterID{"bitDepthKnob", 1}, "bit-depth",
                     juce::NormalisableRange<float>(4.f, 16.f, 0.001f, 0.2f),
                     16.f),
                 std::make_unique<juce::AudioParameterFloat>(
                     juce::ParameterID{"modFreqKnob", 1}, "frequency", 1.f,
                     30.f, 5.f),
                 std::make_unique<juce::AudioParameterFloat>(
                     juce::ParameterID{"modDepthKnob", 1}, "mod-depth", 0.f,
                     1.f, 0.5f),
                 std::make_unique<juce::AudioParameterFloat>(
                     juce::ParameterID{"saturationKnob", 1}, "saturation", 1.f,
                     50.f, 1.f),
                 std::make_unique<juce::AudioParameterFloat>(
                     juce::ParameterID{"dryWetKnob", 1}, "dry/wet", 0.f, 1.f,
                     0.5f),
             }) {

  // Use the parameter ID to return a pointer to our parameter data
  pitch = Params.getRawParameterValue("detuneKnob");
  bitDepth = Params.getRawParameterValue("bitDepthKnob");
  modFreq = Params.getRawParameterValue("modFreqKnob");
  modDepth = Params.getRawParameterValue("modDepthKnob");
  saturation = Params.getRawParameterValue("saturationKnob");
  dryWet = Params.getRawParameterValue("dryWetKnob");

  // for each input channel emplace one effect
  for (auto i = 0; i < getBusesLayout().getNumChannels(true, 0); ++i) {
    bitCrusher.emplace_back();
    pitchShifter.emplace_back();
    tremolo.emplace_back();
    compressor.emplace_back();

    bitCrusher[i].setQuantizedBitDepth(16.f);
    pitchShifter[i].setPitch(1.f);
    tremolo[i].setFrequency(5.f);
    tremolo[i].setModDepth(0.5f);
  }
}

AudioPluginAudioProcessor::~AudioPluginAudioProcessor() {}

//==============================================================================
const juce::String AudioPluginAudioProcessor::getName() const {
  return JucePlugin_Name;
}

bool AudioPluginAudioProcessor::acceptsMidi() const {
#if JucePlugin_WantsMidiInput
  return true;
#else
  return false;
#endif
}

bool AudioPluginAudioProcessor::producesMidi() const {
#if JucePlugin_ProducesMidiOutput
  return true;
#else
  return false;
#endif
}

bool AudioPluginAudioProcessor::isMidiEffect() const {
#if JucePlugin_IsMidiEffect
  return true;
#else
  return false;
#endif
}

double AudioPluginAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int AudioPluginAudioProcessor::getNumPrograms() {
  return 1; // NB: some hosts don't cope very well if you tell them there are 0
            // programs, so this should be at least 1, even if you're not really
            // implementing programs.
}

int AudioPluginAudioProcessor::getCurrentProgram() { return 0; }

void AudioPluginAudioProcessor::setCurrentProgram(int index) {
  juce::ignoreUnused(index);
}

const juce::String AudioPluginAudioProcessor::getProgramName(int index) {
  juce::ignoreUnused(index);
  return {};
}

void AudioPluginAudioProcessor::changeProgramName(int index,
                                                  const juce::String &newName) {
  juce::ignoreUnused(index, newName);
}

//==============================================================================
void AudioPluginAudioProcessor::prepareToPlay(double sampleRate,
                                              int samplesPerBlock) {
  // Use this method as the place to do any pre-playback
  // initialisation that you need..
  juce::ignoreUnused(sampleRate, samplesPerBlock);
}

void AudioPluginAudioProcessor::releaseResources() {
  // When playback stops, you can use this as an opportunity to free up any
  // spare memory, etc.
}

bool AudioPluginAudioProcessor::isBusesLayoutSupported(
    const BusesLayout &layouts) const {
#if JucePlugin_IsMidiEffect
  juce::ignoreUnused(layouts);
  return true;
#else
  // This is the place where you check if the layout is supported.
  // In this template code we only support mono or stereo.
  // Some plugin hosts, such as certain GarageBand versions, will only
  // load plugins that support stereo bus layouts.
  if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() &&
      layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
    return false;

    // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
  if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
    return false;
#endif

  return true;
#endif
}

// function that controls dry wet
std::atomic<float> AudioPluginAudioProcessor::setDryWet(float wetSignal,
                                                        float drySignal,
                                                        float dryWetValue) {
  return drySignal * (1.f - dryWetValue) + (wetSignal * dryWetValue);
}

void AudioPluginAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer,
                                             juce::MidiBuffer &midiMessages) {
  juce::ignoreUnused(midiMessages);

  juce::ScopedNoDenormals noDenormals;
  auto totalNumInputChannels = getTotalNumInputChannels();
  auto totalNumOutputChannels = getTotalNumOutputChannels();

  for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    buffer.clear(i, 0, buffer.getNumSamples());

  for (int channel = 0; channel < totalNumInputChannels; ++channel) {

    float output[totalNumOutputChannels];

    for (int i = 0; i < totalNumOutputChannels; i++)
      output[i] = 0.f;

    // input data
    const float *inputData = buffer.getReadPointer(channel);

    // output data
    float *outputData = buffer.getWritePointer(channel);

    juce::ignoreUnused(outputData);

    for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {

      // edit parameters
      pitchShifter[channel].setPitch(*pitch);
      bitCrusher[channel].setQuantizedBitDepth(*bitDepth);
      tremolo[channel].setFrequency(*modFreq);
      tremolo[channel].setModDepth(*modDepth);

      // get current value from read pointer
      float inputSample = inputData[sample];

      // edit input signal with effect
      pitchShifter[channel].processFrame(inputSample, output[channel]);
      bitCrusher[channel].processFrame(output[channel], output[channel]);
      tremolo[channel].processFrame(output[channel], output[channel]);
      compressor[channel].processFrame(output[channel], output[channel]);
      output[channel] = tanh(*saturation * output[channel]) / tanh(*saturation);

      // combine input & output for working dry/wet balance
      outputData[sample] = setDryWet(output[channel], inputSample, *dryWet);
    }
  }
}

//==============================================================================
bool AudioPluginAudioProcessor::hasEditor() const { return true; }

juce::AudioProcessorEditor *AudioPluginAudioProcessor::createEditor() {
  return new AudioPluginAudioProcessorEditor(*this, Params);
}

//==============================================================================
void AudioPluginAudioProcessor::getStateInformation(
    juce::MemoryBlock &destData) {
  // You should use this method to store your parameters in the memory block.
  // You could do that either as raw data, or use the XML or ValueTree classes
  // as intermediaries to make it easy to save and load complex data.
  juce::ignoreUnused(destData);
  auto state = Params.copyState();
  std::unique_ptr<juce::XmlElement> xml(state.createXml());
  copyXmlToBinary(*xml, destData);
}

void AudioPluginAudioProcessor::setStateInformation(const void *data,
                                                    int sizeInBytes) {
  // You should use this method to restore your parameters from this memory
  // block, whose contents will have been created by the getStateInformation()
  // call.
  std::unique_ptr<juce::XmlElement> xmlState(
      getXmlFromBinary(data, sizeInBytes));
  if (xmlState.get() != nullptr)
    if (xmlState->hasTagName(Params.state.getType()))
      Params.replaceState(juce::ValueTree::fromXml(*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
  return new AudioPluginAudioProcessor();
}
