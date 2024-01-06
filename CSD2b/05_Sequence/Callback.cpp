#include "Callback.h"

CustomCallback::CustomCallback() {
  UI console_ui; // starting ui

  // ascii art & title
  std::cout << "\e[0;104m" << "\e[1;97m" << "                    ___  ____  ____ " << std::endl;
  std::cout << "                   / __)(  _ \\/ ___)" << std::endl;
  std::cout << "  //pirko-2024    ( (_ \\ )   /\\___ \\" << std::endl;
  std::cout << "                   \\___/(__\\_)(____/" << std::endl;
  std::cout << "\n * welcome to the G̳a̳b̳b̳e̳r̳ R̳e̳m̳i̳x̳ S̳y̳n̳t̳h̳ *\n\nwhich song would you like to remix? " << "\e[1;96m" << std::endl;
  int numSongSelection = console_ui.retrieveUserSelection(songOptions,3);

  std::cout << "\e[0;104m" << "\e[1;97m" << "\nwhich instrument would you like 2 use?" << "\e[1;96m" << std::endl;
  int numSynthSelection = console_ui.retrieveUserSelection(synthOptions,2);
  std::cout << "\e[0;104m" << "\e[1;97m" << "\nenjoy :)\n" << "\e[1;96m" << std::endl;

  if (numSongSelection == 0) {
    songChoice = "ode-to-joy";
  } else if (numSongSelection == 1) {
    songChoice = "tetris";
  } else {
    songChoice = "titanic";
  }

  if (numSynthSelection == 0) {
    synthChoice = "fm-synth";
  } else {
    synthChoice = "dance-lead";
  }

}

CustomCallback::~CustomCallback() {}

void CustomCallback::updatePitch(Melody &melody, DetunedSaw &saw, FMSynth &fm) {
  float note;

  if (songChoice == "ode-to-joy") {
    note = melody.getBeethovenNote();
  } else if (songChoice == "tetris") {
    note = melody.getTetrisNote();
  } else {
    note = melody.getTitanicNote();
  }

  saw.setPitch(note);
  fm.setPitch(note);
} // updatePitch()

void CustomCallback::prepare(int rate) {
  sampleRate = (float)rate;
  updatePitch(melody, saw, fm);
}

void CustomCallback::process(AudioBuffer buffer) {
  auto [inputChannels, outputChannels, numInputChannels, numOutputChannels,
        numFrames] = buffer;

  for (int channel = 0; channel < numOutputChannels; ++channel) {
    for (int sample = 0; sample < numFrames; ++sample) {
      //

      if (synthChoice == "fm-synth") {
        outputChannels[channel][sample] = fm.getSample() + kick.getSample();
        fm.tick();
      } else if (synthChoice == "dance-lead") {
        outputChannels[channel][sample] = saw.getSample() + kick.getSample();
        saw.tick();
      }
      kick.tick();

      /*
       * After every sample, check if we need to advance to the next note
       * This is a bit awkward in this scheme of buffers per channel
       * In a multichannel setting we should update pitches independently per
       * channel!
       */

      if (frameIndex >= noteDelayFactor * sampleRate) {
        // reset frameIndex
        frameIndex = 0;
        updatePitch(melody, saw, fm);
        counter++;
      } else {
        // increment frame index
        frameIndex++;
      }

      if (counter >= 31) {
        // kick plays every two eight notes
        if (counter % 2 == 1) {
          kick.resetPhase();
        }
      }
    }
  }
}
