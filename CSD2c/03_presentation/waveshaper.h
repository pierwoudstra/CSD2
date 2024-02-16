#include "effect.h"

#ifndef INC_02_WAVESHAPER_WAVESHAPER_H
#define INC_02_WAVESHAPER_WAVESHAPER_H

class Waveshaper : public Effect {
public:
  enum WaveshapeType { SOFT = 0, HARD, DIGITAL, SINE };

  Waveshaper(float dryWet = 1.f,
             WaveshapeType waveshapeType = WaveshapeType::SOFT,
             float drive = 2.f);
  ~Waveshaper();

  void applyEffect(const float &input, float &output) override;

  // setters
  void setDrive(float drive);
  void setWaveshapeType(WaveshapeType waveshapeType);

private:
  WaveshapeType waveshapeType;
  float drive;
};

#endif // INC_02_WAVESHAPER_WAVESHAPER_H
