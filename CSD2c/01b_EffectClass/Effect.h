#ifndef INC_01B_EFFECTCLASS_EFFECTCLASS_H
#define INC_01B_EFFECTCLASS_EFFECTCLASS_H

class Effect {
public:
  Effect(float dryWetAmt);
  ~Effect();

  void setDryWet(float dryWetAmt);

protected:
  float input;
  float wetOutput;
  float output;
  float dryWetAmt; // value from 0 to 1
};

#endif // INC_01B_EFFECTCLASS_EFFECTCLASS_H
