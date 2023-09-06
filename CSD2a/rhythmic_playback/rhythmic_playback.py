import simpleaudio
import time

snare = "samples/snare.wav"
kick = "samples/kick.wav"

# met try en except wordt bepaald of het input getal een int is of niet, 
# dit kreeg ik niet aan de praat met if en else statements
# via deze website heb ik deze oplossing gevonden:
# https://pieriantraining.com/python-tutorial-how-to-take-an-integer-input-in-python/
# ↓

try:
  numPlaybackTimes = int(input("how often do u want the sample 2 be played? \n"))

  initial = 1
  rhythmArray = []
  poly_wave_objects = []


  while initial < numPlaybackTimes + 1:
    # dit werkt als de input een int is

    poly_wave_objects.append(simpleaudio.WaveObject.from_wave_file(snare))

    # vragen welke ritmes er moeten worden opgeslagen (evenvaak als dat de sample moet klinken)
    rhythmArray.append(float(input("duration nº " + str(initial) + ": \n")))

    initial += 1

  print("your pattern is " + str(rhythmArray) + "!")

  bpm = float(input("what do u want the bpm 2 be? \n"))
  bpmToSeconds = 60 / bpm

  initial = 1

  while initial < numPlaybackTimes + 1:

    # door de wave objects in een array te zetten probeer ik de sample poly te maken

    play_object = poly_wave_objects[initial-1].play()
    print(initial)

    # berekent tijdsinterval en wacht
    time.sleep(bpmToSeconds * rhythmArray[initial-1])

    # play_object.wait_done() <- dit kan ik verwerken in de code zodra ik snap hoe
    # je polyfoon samples af kunt spelen

    initial += 1
  
except ValueError:
  # wat er gebeurt als de input niet het correcte type heeft

  print("please input a number >:(")