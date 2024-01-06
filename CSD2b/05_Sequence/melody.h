#pragma once

#include <iostream>

#define TETRIS_LEN 64
#define NOKIA_LEN 26
#define TITANIC_LEN 64

class Melody {
public:
  Melody();
  ~Melody();

  // setters and getters
  float getTetrisNote();
  float getNokiaNote();
  float getTitanicNote();

protected:
  // nokia ringtone
  float nokia[NOKIA_LEN] = {64, 62, 66, 66, 68, 68, 61, 59, 50, 50, 52, 52, 59,
                            57, 49, 49, 52, 52, 57, 57, 57, 57, 57, 57, 57, 57};
  float tetris[TETRIS_LEN] = {
      64, 64, 59, 60, 62, 62, 60, 59, 57, 57, 57, 60, 64, 64, 62, 60,
      59, 59, 59, 60, 62, 62, 64, 64, 60, 60, 57, 57, 57, 57, 57, 57,
      0,  62, 62, 65, 69, 69, 67, 65, 64, 64, 64, 60, 64, 64, 62, 60,
      59, 59, 59, 60, 62, 62, 64, 64, 60, 60, 57, 57, 57, 57, 57, 57};
  float titanic[TITANIC_LEN] = {
      57, 57, 57, 57, 57, 57, 55, 53, 55, 60, 60, 60, 60, 60, 58, 57,
      53, 53, 53, 53, 53, 53, 50, 50, 48, 48, 48, 48, 48, 48, 53, 55,
      57, 57, 57, 57, 57, 57, 58, 53, 55, 60, 60, 60, 60, 60, 57, 60,
      62, 62, 62, 62, 60, 60, 60, 60, 55, 55, 55, 55, 55, 55, 53, 55};

  // the index of the current note - readIndex
  int index;
};
