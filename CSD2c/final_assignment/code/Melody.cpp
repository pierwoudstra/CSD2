#include "melody.h"

// Melody Constructor
Melody::Melody()
{
  // Seed the random number generator
  std::srand(static_cast<unsigned>(std::time(nullptr)));

  // Generate a random melody
  generateRandomMelody();

  // Initialize the index
  index = 0;
}

// Melody deconstructor
Melody::~Melody()
{

}

float Melody::getNote()
{
    float note = melody[index];
    index = (index + 1) % NUM_NOTES;  // Loop back to the beginning of the melody
    return note;
}

// ChatGPT used to generate generate random melody function
void Melody::generateRandomMelody() {
    // Define the range of MIDI notes for the melody
    int minNote = 60; // C4
    int maxNote = 72; // C5

    for (int i = 0; i < NUM_NOTES; ++i) {
        melody[i] = std::rand() % (maxNote - minNote + 1) + minNote;
    }
}