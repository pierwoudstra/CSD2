# versie twee die exact hetzelfde doet als de eerste maar overzichtelijker geordend met behulp van functies
#
# ook heb ik alle variablen en functies volgens de python conventie genoemd - bron: https://realpython.com/python-pep8/
# verdere bron voor efficientie was: https://www.loginradius.com/blog/engineering/speed-up-python-code/
#                                  & https://towardsdatascience.com/5-simple-techniques-to-write-your-code-more-efficiently-in-python-f095bb2b1e15
#
# te doen:
#
# multithreading toevoegen oid om
# - t̶w̶e̶e̶ ̶r̶i̶t̶m̶e̶s̶ ̶t̶e̶g̶e̶l̶i̶j̶k̶e̶r̶t̶i̶j̶d̶ ̶t̶e̶ ̶k̶u̶n̶n̶e̶n̶ ̶o̶f̶ 
# - commands in te kunnen voeren tijdens dat het programma speelt

import simpleaudio as sa
import time
import threading

def get_bpm():

    # bpm wordt opgehaald
    # met lower() functie wordt de input als lowercase gelezen
    try:
        standard_bpm = str(input("the standard BPM is 120, do you want to use this one? y/n \n"))
    except:
        print("please input 'y' or 'n' >:(")
        main()       

    try:
        return 120 if standard_bpm.lower() == 'y' else int(input("what do you want the BPM to be? "))
    except:
        print("please input a number >:(")
        main()


def get_rhythm_pattern():

    # ritme patroon wordt opgehaald
    # ↓ array itereert om lijst te maken, bron:  https://devsheet.com/get-integer-only-values-from-a-list-in-python/
    try:
        return [i for i in input("what rhythm pattern do you want to play? \n write:\n 'k' for kick,\n 's' for snare,\n 'b' for kick and snare,\n 'h' for hihat, \n and '-' for nothing. \n you can also add numbers in front of the letters to make the sample repeat :o \n")]
    except TypeError or ValueError:
        print("please input a pattern >:(")
        main()

def get_loop_amt():

    # haalt het aantal loops op en houdt rekening met de optie dat gebruiker geen int invoert

    try:
        return int(input("how often do you want the pattern to repeat? ")) 
    
    except ValueError:
          print("please input a number >:(")
          main()

def play_sample(file_path, bpm_to_seconds):

    # functie om een sample te spelen
    wave_object = sa.WaveObject.from_wave_file(file_path)
    play_object = wave_object.play()
    time.sleep(bpm_to_seconds/4)
    play_object.stop()

def play_rhythm_step(note, bpm_to_seconds, next_note):

    # checkt welke sample gespeeld moet worden
    if note == 'k':
        play_sample("samples/kick.wav", bpm_to_seconds)
    elif note == 's':
        play_sample("samples/snare.wav", bpm_to_seconds)
    elif note == 'h':
        play_sample("samples/hihat.wav", bpm_to_seconds)
    elif note.isdigit() and isinstance(next_note, str):

        # checkt of er een getal voor letter zit (om rolls te kunnen maken)
        amt = int(note)

        # hierbij geruik ik een for loop puur voor herhaling
        # de iterator is niet belangrijk dus kan ik _ neerzetten
        for _ in range(amt):
            if next_note == 'k':
                play_sample("samples/kick.wav", bpm_to_seconds)
            elif next_note == 's':
                play_sample("samples/snare.wav", bpm_to_seconds)
            else:
                play_sample("samples/hihat.wav", bpm_to_seconds)

            time.sleep((bpm_to_seconds/4)/amt)
    elif len(note) == 2:
        amt = int(note[0])

        for _ in range(amt):
            if note[1] == 'k':
                play_sample("samples/kick.wav", bpm_to_seconds)
            elif note[1] == 's':
                play_sample("samples/snare.wav", bpm_to_seconds)
            else:
                play_sample("samples/hihat.wav", bpm_to_seconds)
                
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

    bpm_to_seconds = 60 / bpm
    index = 0

    while index < len(note_array) - 1:
        note = note_array[index]
        try:
            next_note = note_array[index + 1] # deze variabele laat zien wat de volgende noot zal zijn (voor de repeat functie)
        except IndexError:
            next_note = None

        if note.isdigit() and isinstance(next_note, str):
            repeat_note = note + next_note
            note_array[index] = repeat_note
            note_array.pop(index + 1)
        
        index += 1
   
        play_rhythm_step(note, bpm_to_seconds, next_note)

def loop_rhythm(bpm, note_array, loop_amt):
    for _ in range(loop_amt):
        play_rhythm(bpm, note_array)

def main():
    bpm = get_bpm()
    note_array = get_rhythm_pattern()
    loop_amt = get_loop_amt()
    loop_rhythm(bpm, note_array, loop_amt)

main()