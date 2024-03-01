#include "Filters.h"
#include <iostream>

int main() {
  Biquad filter;

  filter.setCoefficient(0.9);

  std::cout << "filters" << std::endl;

  // delta function
  double input;

  for (int i = -3; i < 14; i++) {
    if (i == 0) {
      input = 1.0;
    } else {
      input = 0.0;
    }

    std::cout << filter.process(input) << std::endl;
  }

}
