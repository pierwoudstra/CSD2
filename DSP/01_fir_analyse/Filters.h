#pragma once

struct Filter {
  virtual double process(double input) = 0;
};

//                   IIRFilter
//   X[n] ---->(+)--->[ 1 sample ] ---> Y[n]
//              |                   |
//             (a)<-----------------
//

struct IIRFilter : Filter {
  double process(double input) override {
    // Y[n] = X[n] + aY[n-1]
    feedback = input + (a * feedback);
    return feedback;
  }

  void setCoefficient(double coefficient) {
    // Do not exceed 1, for the safety of all our ears
    a = coefficient;
  }

private:
  double feedback{0.0};
  double a{0.0}; // Coefficient "a" is mostly used for feedback lines
};

//                    OneZero
//   X[n] ---->(+)--------------------> Y[n]
//              |                  |
//             (b)-->[ 1 sample ]-->
//
struct FIRFilter : Filter {
  double process(double input) override {
    // Y[n] = X[n] + bX[n-1]
    auto output = input - (b * x1);

    x1 = input; // Recaching Delay
    return output;
  }

  void setCoefficient(double coefficient) { b = coefficient; }

private:
  double x1{0.0}; // x1 for a single sample delay
  double b{0.0};  // Coefficient "b" is usually used for feed forward lines
};

//                   OnePole
//   X[n] --(b)->(+)--->[ 1 sample ] ---> Y[n]
//                |                   |
//               (a)<-----------------
//
struct OnePole : Filter {
  double process(double input) override {
    // Y[n] = bX[n] + aY[n-1]
    feedback = (b * input) + (a * feedback);
    return feedback;
  }

  void setCoefficient(double coefficient) {
    a = coefficient;
    b = 1.0f - a;
  }

private:
  double feedback{0.0};
  double a{0.0};
  double b{0.0};
};

//                   4_Pole / Simple Cascade
//   X[n]--->[OnePole][OnePole][OnePole][OnePole]--->Y[n]
//
struct SimpleLadder : Filter {
  double process(double input) override {
    A = (b * input) + (a * A);
    B = (b * A) + (a * B);
    C = (b * B) + (a * C);
    D = (b * C) + (a * D);

    double output = D;
    return output;
  }

  void setCoefficient(double coefficient) {
    a = coefficient;
    b = 1.0f - a;
  }

private:
  double A{0.0};
  double B{0.0};
  double C{0.0};
  double D{0.0};

  double b{0.0};
  double a{0.0};
};

//                   4 Sample
//   X[n] --(b)->(+)--->[ 4 sample ] ---> Y[n]
//              |                   |
//             (a)<-----------------
//
struct FourSample : Filter {
  double process(double input) override {
    // Y[n] = X[n] + aY[n-4]
    double output = (b * input) + (a * prevPrevPrevPrev);
    prevPrevPrevPrev = prevPrevPrev;
    prevPrevPrev = prevPrev;
    prevPrev = prev;
    prev = output;

    return output;
  }

  void setCoefficient(double coefficient) {
    a = coefficient;
    b = 1.0f - a;
  }

private:
  double feedback{0.0};
  double prev{0.0};
  double prevPrev{0.0};
  double prevPrevPrev{0.0};
  double prevPrevPrevPrev{0.0};
  double b{0.0};
  double a{0.0};
};

//                   Halve Biquad
//   X[n] --(b)->(+)--------------------> Y[n]
//                |                  |
//               (-a1)<----------[ 1 sample ]
//                |                  |
//               (-a2)<----------[ 1 sample ]
//
//
struct HalfBiquad : Filter {
  double process(double input) override {
    // y[n] = bX[n] - a1Y[n-1] - a2Y[n-2]
    double output = (b * input) - (a1 * prev) - (a2 * prevPrev);
    prevPrev = prev;
    prev = output;
    return output;
  }

  void setCoefficient(double coefficient) {
    a1 = coefficient;
    a2 = coefficient;
    b = coefficient;
  }

private:
  double prev{0.0};
  double prevPrev{0.0};

  double b{0.0};
  double a1{0.0};
  double a2{0.0};
};

struct Biquad : Filter {
  double process(double input) override {
    // Direct form 1
    //
    // y[n] = b1X[n] + b2X[n-1] + b3X[n-2] - a1Y[n-1] - a2Y[n-2]
    //
    // here b1, b2 & b3 coefficients determine zeros
    // a1 & a2 coefficients determine the position of the poles

    double output = (b1 * input) + (b2 * prevInput) + (b3 * prevPrevInput) - (a1 * prevOutput) - (a2 * prevPrevOutput);
    prevPrevInput = prevInput;
    prevPrevOutput = prevOutput;
    prevInput = input;
    prevOutput = output;
    return output;
  }

  void setCoefficient(double coefficient) {
    a1 = coefficient;
    a2 = coefficient;
    b1 = coefficient;
    b2 = coefficient;
    b3 = coefficient;
  }

private:
  double prevInput{0.0};
  double prevPrevInput{0.0};
  double prevOutput{0.0};
  double prevPrevOutput{0.0};

  double b1{0.0};
  double b2{0.0};
  double b3{0.0};
  double a1{0.0};
  double a2{0.0};
};
