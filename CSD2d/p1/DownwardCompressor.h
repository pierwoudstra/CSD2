#include "Effect.h"
#include <cmath>

#ifndef MYPROJECT_DOWNWARDCOMPRESSOR_H
#define MYPROJECT_DOWNWARDCOMPRESSOR_H

class DownwardCompressor : public Effect {
public:
  DownwardCompressor(int attackTime = 3000, int releaseTime = 2000) {
    this->attackTime = attackTime;
    this->releaseTime = releaseTime;
    currentState = States::noOperationState;

    holdTime = 1000;

    threshold = 0.6f;

    // compression ratio 6:1 -> 6dB = 0.5
    gainReduceAmt = 0.5f;

    gainStepAttack = (1.f - gainReduceAmt) / attackTime;
    gainStepRelease = (1.f - gainReduceAmt) / releaseTime;

    // initial gain
    gain = 1.f;
  }

  ~DownwardCompressor() {}

  void applyEffect(const float &input, float &output) override {

    // analyse incoming signal

    if (abs(input) > threshold) {
      if (gain >= gainReduceAmt) {
        if (currentState == States::noOperationState) {
          currentState = States::attackState;
          timeOut = attackTime;
        } else if (currentState == States::releaseState) {
          currentState = States::attackState;
          timeOut = attackTime;
        }
      }
      if (currentState == States::gainReductionState)
        timeOut = holdTime;
    }

    if (abs(input) < threshold && gain <= 1.f) {
      if (timeOut == 0 && currentState == States::gainReductionState) {
        currentState = States::releaseState;
        timeOut = releaseTime;
      }
    }

    // operate on relevant state

    switch (currentState) {
    case States::attackState:
      if (timeOut > 0 && gain > gainReduceAmt) {
        gain -= gainStepAttack;
        timeOut--;
      } else {
        currentState = States::gainReductionState;
        timeOut = holdTime;
      }
      break;
    case States::gainReductionState:
      if (timeOut > 0)
        timeOut--;
      else {
        currentState = States::releaseState;
        timeOut = releaseTime;
      }
      break;
    case States::releaseState:
      if (timeOut > 0 && gain < 1.f) {
        timeOut--;
        gain += gainStepRelease;
      } else {
        currentState = States::noOperationState;
      }
      break;
    case States::noOperationState:
      if (gain < 1.f)
        gain = 1.f;
      break;

    default:
      break;
    }
  }

private:
  // 0 = no gain reduction
  // 1 = attack
  // 2 = gain reduction
  // 3 = release
  enum States {
    noOperationState,
    attackState,
    gainReductionState,
    releaseState
  };
  States currentState;

  // parameters in samples
  int attackTime, releaseTime, holdTime, timeOut;
  float gainReduceAmt, gainStepAttack, gainStepRelease, gain, threshold;
};

#endif // MYPROJECT_DOWNWARDCOMPRESSOR_H
