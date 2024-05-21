#include <iostream>

#pragma once

// Effect baseclass by Ciska

class Effect {
public:
  // drywet: drywet balance
  // drywet == 0:     dry
  // 0 < drywet < 1:  mix
  // drywet == 1:     wet
  // default is wet

  Effect(float dryWet = 0.5f) {
    setDryWet(dryWet);
    setBypass(false);
  }

  virtual ~Effect() {}

  // not pure virtual, since not all subclasses require the sampleRate
  virtual void prepare(float sampleRate) {}

  // process frame
  void processFrame(const float &input, float &output) {
    // using bypass to determine signal
    if (bypass) {
      output = input;
    } else {
      applyEffect(input, output);
      output = input * float(wetDry) + output * float(dryWet);
    }
    // cache output samples
    m_sample = output;
  }
  // returns the last outputted sample
  float getSample() { return m_sample; }

  // setters
  void setDryWet(float dryWet) {
    //    std::cout << "dryWet: " << dryWet << std::endl;

    if (dryWet < 0.f || dryWet > 1.f) {
      throw "Effect::setDryWet - dryWet value is not in range [0, 1]";
    }
    //  std::cout << "drywet: " << dryWet << std::endl;
    this->dryWet = dryWet;
    // cache 1.0 - dryWet used to calculate mix of dry wet signal
    wetDry = float(1.0f - dryWet);
  }
  void setBypass(bool bypass) { this->bypass = bypass; }

  float dryWet;

protected:
  // pure virtual method
  virtual void applyEffect(const float &input, float &output) = 0;

private:
  bool bypass;
  // balance between dry and wet signal
  float wetDry; // = 1 - dryWet
  // cache last sample
  float m_sample;
};
