#pragma once
#include <iostream>
#include "effect.h"

class BitCrusher : public Effect 
{
    public:
        BitCrusher(double bitDepth = 4.0, float dryWet = 1.0f);
        ~BitCrusher();

        void setQuantizedBitDepth(double bitDepth);

    private:
        void applyEffect(const float &input, float &output) override;
        
        double bitDepth;
        double quantizationLevel;

        BitCrusher(){}
};