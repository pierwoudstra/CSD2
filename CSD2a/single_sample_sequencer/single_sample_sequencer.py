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
        getInput()

    # ↓ array itereert om lijst te maken, bron:  https://devsheet.com/get-integer-only-values-from-a-list-in-python/
    noteArray = [i for i in input("what rhythm pattern do you want to play? \n write 'k' for kick, 's' for snare and '-' for nothing \n you can also add numbers in front of the letters to make the sample repeat :o \n ")]

    return bpm, noteArray

def playRhythm(bpm, noteArray):

    # samples inladen
    snare = "samples/snare.wav"
    kick = "samples/kick.wav"

    bpmToSeconds = 60 / int(bpm)

    # loopt langs alle tellen en checkt of het een kick of snare is
    i = 0
    while i < len(noteArray):

        # print(i)

        # speel kick
        if noteArray[i] == 'k':
            wave_object = sa.WaveObject.from_wave_file(kick)
            play_object = wave_object.play()
            time.sleep(bpmToSeconds/4)
            play_object.stop()

        # speel snare
        elif noteArray[i] == 's':
            wave_object = sa.WaveObject.from_wave_file(snare)
            play_object = wave_object.play()
            time.sleep(bpmToSeconds/4)
            play_object.stop()

        # optie om snelle ghost notes te spelen
        elif noteArray[i].isdigit():

            try:
                # hoevaak ghost note zal worden gespeeld
                amt = noteArray[i]

                if noteArray[i+1] == 'k':
                    for l in range(int(amt)):
                        wave_object = sa.WaveObject.from_wave_file(kick)
                        play_object = wave_object.play()
                        time.sleep((bpmToSeconds/4)/int(amt))

                elif noteArray[i+1] == 's':
                    for l in range(int(amt)):
                        wave_object = sa.WaveObject.from_wave_file(snare)
                        play_object = wave_object.play()
                        time.sleep((bpmToSeconds/4)/int(amt))

                else:
                    time.sleep(bpmToSeconds/4)

            except IndexError:
                # index error ontstaat doordat je niet altijd i+1 kunt doen
                time.sleep(bpmToSeconds/4)

            # zorgt ervoor dat lijst toch uitkomt (dat de getallen die achter elkaar moeten als 1 worden gezien)
        
        else:
            # stilte
            time.sleep(bpmToSeconds/4)

        i += 1

    # ritme speelt maar één keer


def main():
    bpm, noteArray = getInput()
    playRhythm(bpm, noteArray)

main()