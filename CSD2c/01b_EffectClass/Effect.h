#ifndef INC_01B_EFFECTCLASS_EFFECTCLASS_H
#define INC_01B_EFFECTCLASS_EFFECTCLASS_H

class Effect {
public:
  Effect(float wet);
  virtual ~Effect();

  void setDryWet(float wet);
  float processFrame(float input);

  // virtual methods
  virtual void prepare(float sampleRate);
  virtual float applyEffect(float input) = 0;

protected:
  float sampleRate = 44100.f;
  float input;
  float output; // wet output

private:
  float wet; // value from 0 to 1
  float dry; // 1 - wet
};

#endif // INC_01B_EFFECTCLASS_EFFECTCLASS_H
