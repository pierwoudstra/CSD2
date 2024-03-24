#pragma once

// Effect baseclass by Ciska

class Effect {
public:
  // drywet: drywet balance
  // drywet == 0:     dry
  // 0 < drywet < 1:  mix
  // drywet == 1:     wet
  // default is wet
  Effect(float dryWet = 1.0);
  virtual ~Effect();

  // not pure virtual, since not all subclasses require the samplerate
  virtual void prepare(float samplerate) {}
  // process frame
  void processFrame(const float &input, float &output);
  // returns the last outputted sample
  float getSample();

  // setters
  void setDryWet(float dryWet);
  void setBypass(bool bypass);

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
  /*
   * NOTE: other possible extra base class functionality:
   * • bypass
   */
};
