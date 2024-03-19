#include "bitcrusher.h"
#include <cmath>

BitCrusher::BitCrusher(double bitDepth, float dryWet) :
  Effect(dryWet), bitDepth(bitDepth)
{
    std::cout << "BitCrusher Constructor" << std::endl;
    setQuantizedBitDepth(bitDepth);
};

BitCrusher::~BitCrusher()
{
    std::cout << "BitCrusher Destructor" << std::endl;
};

void BitCrusher::applyEffect(const float &input, float &output) 
{
    output = quantizationLevel * float(int(input / quantizationLevel));
}

void BitCrusher::setQuantizedBitDepth(double bitDepth) 
{
    quantizationLevel = 2.0 / (pow(2.0, bitDepth) - 1.0);
    // std::cout << "quantizationLevel: " << quantizationLevel << std::endl;
}
