#include "melody.h"

Melody::Melody() {}

Melody::~Melody() {}

/*
 * getNote() reads the next note from the melody
 *  and wraps around to the beginning when it reached the end
 *  of the melody
 */
float Melody::getBeethovenNote() {
  // wrap index back to the beginning
  if (index >= 128) {
    index = 0;
  }
  // index++ --> use value, then increment
  return beethoven[index++];
}

float Melody::getTetrisNote() {
  // wrap index back to the beginning
  if (index >= 64) {
    index = 0;
  }
  // index++ --> use value, then increment
  return tetris[index++];
}

float Melody::getTitanicNote() {
  // wrap index back to the beginning
  if (index >= 64) {
    index = 0;
  }
  // index++ --> use value, then increment
  return titanic[index++];
}
