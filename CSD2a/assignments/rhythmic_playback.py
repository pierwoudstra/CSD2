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
  sampleChoice = str(input("which sample do u wanna play? \n (type: 'kick' or 'snare') \n"))

  # kiest welke sample in te laden
  if sampleChoice == str('kick'):
    wave_object = simpleaudio.WaveObject.from_wave_file(kick)
  elif sampleChoice == str('snare'):
    wave_object = simpleaudio.WaveObject.from_wave_file(snare)
  else:
    print("please fill in either: kick or snare \n (︶︹︶) ")
    quit()

  # print(wave_object) <- om te zien of alles goed is ingeladen

  numPlaybackTimes = int(input("how often do u want the sample 2 be played? \n"))

  rhythmArray = []

  initial = 1
  while initial < numPlaybackTimes + 1:
    # dit werkt als de input een int is

    # vragen welke ritmes er moeten worden opgeslagen (evenvaak als dat de sample moet klinken)
    rhythmArray.append(float(input("duration nº " + str(initial) + ": \n")))

    initial += 1

  print("your pattern is " + str(rhythmArray) + "!")

  bpm = float(input("what do u want the bpm 2 be? \n"))
  bpmToSeconds = 60 / bpm

  initial = 1

  while initial < numPlaybackTimes + 1:

    # door de wave objects in een array te zetten probeer ik de sample poly te maken

    play_object = wave_object.play()
    print(initial)

    # berekent tijdsinterval en wacht
    time.sleep(bpmToSeconds * rhythmArray[initial-1])

    play_object.stop()

    # play_object.wait_done() <- dit kan ik verwerken in de code zodra ik snap hoe
    # je polyfoon samples af kunt spelen

    initial += 1
  
except ValueError:

  # wat er gebeurt als de input niet het correcte type heeft
  print("please input a number >:(")