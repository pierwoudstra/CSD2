#include "Effect.h"

#ifndef INC_02_WAVESHAPER_WAVESHAPER_H
#define INC_02_WAVESHAPER_WAVESHAPER_H

class Waveshaper : public Effect {
public:
  // enum to determine type of wave-shaping
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
  float drive; // from 1 till ∞
};

#endif // INC_02_WAVESHAPER_WAVESHAPER_H
