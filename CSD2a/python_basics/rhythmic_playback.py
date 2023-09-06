import simpleaudio
import array as arr
import time

# wav file wordt naar WaveObject overgezet
snare = "samples/snare.wav"
wave_object = simpleaudio.WaveObject.from_wave_file(snare)

# met try en except wordt bepaald of het input getal een int is of niet, 
# dit kreeg ik niet aan de praat met if en else statements
# via deze website heb ik deze oplossing gevonden:
# https://pieriantraining.com/python-tutorial-how-to-take-an-integer-input-in-python/
# ↓

try:
  numPlaybackTimes = int(input("how often do you want the sample to be played? "))

  initial = 1
  rhythmArray = []

  while initial < numPlaybackTimes + 1:
    # dit werkt als de input een int is

    # vragen welke ritmes er moeten worden opgeslagen (evenvaak als dat de sample moet klinken)
    rhythmArray.append(input("duration nº " + str(initial) + ": "))

    # play_object = wave_object.play()
    # print(initial)
    # play_object.wait_done()

    initial += 1

  print(rhythmArray)
except ValueError:
  # wat er gebeurt als de input geen int is

  print("please input an integer number >:(")