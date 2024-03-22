#pragma once

#include <iostream>

#define NUM_NOTES 100

class Melody
{
    public:
        // constructor and deconstructor
        Melody();
        ~Melody();

        // setters and getters
        float getNote();
        // ChatGPT used to generate generate random melody function
        void generateRandomMelody();

    protected:
        float melody[NUM_NOTES];
        int index;

};
