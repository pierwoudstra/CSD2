#include <iostream>

class Piano {
public:
    Piano( int initRange = 88, std::string initColor = "black", std::string initBrand = "Steinway" ) {
        range = initRange;
        color = initColor;
        brand = initBrand;
    }

    void playNote( int midiNote ) {
        if (midiNote > 0 && midiNote < range) {
            // speel piano
        }
    }

    void tunePiano() {
        for (int i = 0; i < range; i++) {
            // stem piano
        }
    }

    void setRange( int newRange ) {
        range = newRange;
    }

    int getRange() {
        return range; 
    }

    void setColor( std::string newColor ) {
        color = newColor;
    }

    std::string getColor() {
        return color;
    }

    void setBrand( std::string newBrand ) {
        brand = newBrand;
    }

    std::string getBrand() {
        return brand;
    }
    
private:
    int range;
    std::string color;
    std::string brand;
};