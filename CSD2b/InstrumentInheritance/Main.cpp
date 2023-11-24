#include "Instrument.h"
#include "StringedInstrument.h"

int main() {
  StringedInstrument piano("ping", 88, "copper", "hammer");

  piano.play(1, 127);
  piano.play(5, 48);
}
