#include "melody.h"

Melody::Melody() {}

Melody::~Melody() {}

/*
 * getNote() reads the next note from the melody
 *  and wraps around to the beginning when it reached the end
 *  of the melody
 */
float Melody::getNokiaNote() {
  // wrap index back to the beginning
  if (index >= NOKIA_LEN) {
    index = 0;
  }
  // index++ --> use value, then increment
  return nokia[index++];
}

float Melody::getTetrisNote() {
  // wrap index back to the beginning
  if (index >= TETRIS_LEN) {
    index = 0;
  }
  // index++ --> use value, then increment
  return tetris[index++];
}

float Melody::getTitanicNote() {
  // wrap index back to the beginning
  if (index >= TITANIC_LEN) {
    index = 0;
  }
  // index++ --> use value, then increment
  return titanic[index++];
}
