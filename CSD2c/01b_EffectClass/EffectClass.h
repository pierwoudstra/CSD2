#ifndef INC_01B_EFFECTCLASS_EFFECTCLASS_H
#define INC_01B_EFFECTCLASS_EFFECTCLASS_H

class EffectClass {
public:
  EffectClass(float dryWetAmt = 0.5);
  ~EffectClass();

  void setDryWet(float dryWetAmt);
  virtual float processFrame(float input);

public:
  float input;
  float wetOutput;
  float output;
  float dryWetAmt; // value from 0 to 1
};

#endif // INC_01B_EFFECTCLASS_EFFECTCLASS_H
