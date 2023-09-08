import simpleaudio as sa
import time

def getInput():
    standardBPM = input("the standard BPM is 120, do you want to use this one? y/n \n")
    if standardBPM == 'y' or standardBPM == 'Y':
        bpm = 120
    elif standardBPM == 'n' or standardBPM == 'N':
        bpm = input("what do you want the BPM to be? ")
    else:
        print("please input 'y' or 'n' ")
    
    noteArray = [i for i in input("what rhythm pattern do you want to play? ")]
    # wordt niet overgezet naar ints in een array ↑

    print(bpm, noteArray)

    return bpm, noteArray

def playRhythm(bpm, noteArray):

    # maakt nog geen geluid

    snare = "samples/snare.wav"
    wave_object = sa.WaveObject.from_wave_file(snare)

    bpmToSeconds = 60 / bpm

    i = 0
    while i < 15:

        if i in noteArray:
            play_object = wave_object.play()
            time.sleep(bpmToSeconds)
            play_object.stop()
        
        else:
            time.sleep(bpmToSeconds)

        i += 1


def main():
    bpm, noteArray = getInput()
    playRhythm(bpm, noteArray)

main()