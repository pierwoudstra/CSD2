#include "CircBuffer.h"

CircBuffer::CircBuffer(int size) {
  buffer = new float[size];
  this->size = size;
  readHead = 0;
  writeHead = 0;
}

CircBuffer::~CircBuffer() {}

void CircBuffer::write(float input) {
  buffer[writeHead] = input;
  if (writeHead < size - 1) {
    writeHead++;
  } else {
    writeHead = 0;
  }
}

float CircBuffer::read() {
  float output = buffer[readHead];
  if (readHead < size - 1) {
    readHead++;
  } else {
    readHead = 0;
  }
  return output;
}
