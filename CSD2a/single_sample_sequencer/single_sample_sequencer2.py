# versie twee die exact hetzelfde doet als de eerste maar overzichtelijker geordend met behulp van functies
#
# ook heb ik alle variablen en functies volgens de python conventie genoemd - bron: https://realpython.com/python-pep8/
#
# te doen:
# multithreading toevoegen of 
# - om twee ritmes tegelijkertijd te kunnen of 
# - om commands in te kunnen tijdens dat het programma speelt

import simpleaudio as sa
import time
import threading

def get_bpm():

    # bpm wordt opgehaald
    # met lower() functie wordt de input als lowercase gelezen
    standard_bpm = input("the standard BPM is 120, do you want to use this one? y/n \n")
    return 120 if standard_bpm.lower() == 'y' else int(input("what do you want the BPM to be? "))

def get_rhythm_pattern():

    # ritme patroon wordt opgehaald
    # ↓ array itereert om lijst te maken, bron:  https://devsheet.com/get-integer-only-values-from-a-list-in-python/
    return [i for i in input("what rhythm pattern do you want to play? \n write 'k' for kick, 's' for snare, 'b' for both and '-' for nothing. \n you can also add numbers in front of the letters to make the sample repeat :o \n")]

def get_loop_amt():

    # haalt het aantal loops op en houdt rekening met de optie dat gebruiker geen int invoert

    try:
        return int(input("how often do you want the pattern to repeat? ")) 
    
    except ValueError:
          print("please input a number >:(")

def play_sample(file_path, bpm_to_seconds):

    # functie om een sample te spelen
    wave_object = sa.WaveObject.from_wave_file(file_path)
    play_object = wave_object.play()
    time.sleep(bpm_to_seconds/4)
    play_object.stop()

def play_rhythm_step(note, bpm_to_seconds):

    # checkt welke sample gespeeld moet worden
    if note == 'k':
        play_sample("samples/kick.wav", bpm_to_seconds)
    elif note == 's':
        play_sample("samples/snare.wav", bpm_to_seconds)
    elif note.isdigit():

        # checkt of er een getal voor letter zit (om rolls te kunnen maken)
        amt = int(note)

        # hierbij geruik ik een for loop puur voor herhaling
        # de iterator is niet belangrijk dus kan ik _ neerzetten
        for _ in range(amt):
            play_sample("samples/kick.wav", bpm_to_seconds) if note == 'k' else play_sample("samples/snare.wav", bpm_to_seconds)
            time.sleep((bpm_to_seconds/4)/amt)
    elif note == 'b':

        # functies worden gespesificeerd voor de threads
        thread1 = threading.Thread(target=play_sample, args=("samples/kick.wav", bpm_to_seconds))
        thread2 = threading.Thread(target=play_sample, args=("samples/snare.wav", bpm_to_seconds))

        # threads beginnen
        thread1.start()
        thread2.start()

        # wacht tot beide threads klaar zijn
        thread1.join()
        thread2.join()

    else:
        time.sleep(bpm_to_seconds/4)

def play_rhythm(bpm, note_array):

    # loopt door de ingevoerde lijst en roept die functie op de beslist wat daar gespeeld moet worden
    bpm_to_seconds = 60 / bpm
    for note in note_array:
        play_rhythm_step(note, bpm_to_seconds)

def loop_rhythm(bpm, note_array, loop_amt):
    for _ in range(loop_amt):
        play_rhythm(bpm, note_array)

def main():
    bpm = get_bpm()
    note_array = get_rhythm_pattern()
    loop_amt = get_loop_amt()
    loop_rhythm(bpm, note_array, loop_amt)

main()