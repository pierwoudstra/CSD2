#ifndef INC_04_ENVELOPEGENERATOR_ENVELOPE_H
#define INC_04_ENVELOPEGENERATOR_ENVELOPE_H

class Envelope {
public:
  Envelope(int sampleRate);
  ~Envelope();

  float getValue();
  void tick();

private:
  int sampleRate;
  float phase;
  float value;

};

#endif // INC_04_ENVELOPEGENERATOR_ENVELOPE_H
