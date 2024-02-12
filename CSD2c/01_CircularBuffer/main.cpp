#include "CircBuffer.h"
#include <iostream>

int main() {

  int bufSize = 20;

  CircBuffer circBuffer = CircBuffer(bufSize);

  std::cout << "writing values" << std::endl;

  for (int i = 0; i < bufSize; i++) {
    circBuffer.write(i);
  }

  std::cout << "reading values" << std::endl;


  for (int j = 0; j < 60; j++) {
    // std::cout << j << std::endl;
    std::cout << circBuffer.read() << std::endl;
  }

  std::cout << "done" << std::endl;

}
