#ifndef INC_04_ENVELOPEGENERATOR_ENVELOPE_H
#define INC_04_ENVELOPEGENERATOR_ENVELOPE_H

class Envelope {
public:
  Envelope(float attack, float decay, bool loop, int sampleRate);
  ~Envelope();

  float getValue();
  void tick();
  void resetPhase();

private:
  float attack;
  float decay;
  int sampleRate;
  float phase;
  float value;
  bool loop;

};

#endif // INC_04_ENVELOPEGENERATOR_ENVELOPE_H
