#include "CircBuffer.h"

CircBuffer::CircBuffer(int size) {
  buffer = new float[size]; // dynamically allocating buffer

  for (int i = 0; i < size; i++) {
    buffer[i] = 0.f;
  }
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

void CircBuffer::setReadHead(int readHead) {
  this->readHead = readHead;
  if (readHead < 0) {
    readHead += size;
  }
}
