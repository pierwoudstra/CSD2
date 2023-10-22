import os
from midiutil.MidiFile import MIDIFile


class Text:
    # class to represent different text effects
    BLUE = "\033[94m"
    RED = "\033[91m"
    UNDERLINE = "\033[4m"
    END = "\033[0m"


def get_meter():
    # gets meter, using standard way to troubleshoot input
    text1 = "what do you want the time signature to be?"
    text2 = " (in eighth notes)"
    text3 = "\nput '5' for 5/8, '7' for 7/8, etc... \n\n"

    while True:
        value = input(Text.BLUE + Text.UNDERLINE + text1 + Text.END + text2 + text3)
        try:
            value = int(value)
        except ValueError:
            print("\nplease input an integer :) \n")
            continue
        if 4 <= value <= 21:
            return value
        else:
            print("\nplease input a value between 4 and 21\n")


def get_bpm():
    # gets bpm, using standard way to troubleshoot input
    text1 = "\nwhat do you want the bpm to be?\n\n"

    while True:
        value = input(Text.BLUE + Text.UNDERLINE + text1 + Text.END)
        try:
            value = int(value)
        except ValueError:
            print("\nplease input an integer :) \n")
            continue
        if 40 <= value <= 200:
            return value
        else:
            print("\nplease input a value between 40 and 200\n")


def get_sound_choice():
    # gets sound choice, using standard way to troubleshoot input
    text1 = "\nwhat kind of sounds do you want to hear?\n\n"
    text2 = "~ type '1' for funk carioca 🇧🇷\n~ type '2' for uk garage 💿\n~ type '3' for balkan traditional 🎺\n\n"

    while True:
        value = input(Text.BLUE + Text.UNDERLINE + text1 + Text.END + text2)
        try:
            value = int(value)
        except ValueError:
            print("\nplease input an integer :) \n")
            continue
        if 1 <= value <= 3:
            return value
        else:
            print("\nplease input a value between 1 and 3\n")


def get_info():
    # title screen
    print(
        "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n| welcome 2 my "
        + Text.RED
        + "RHYTHM GENERATOR"
        + Text.END
        + " |\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n"
    )

    meter = get_meter()
    bpm = get_bpm()
    sound_choice = get_sound_choice()

    return meter, bpm, sound_choice


def save_to_midi(kicks, snares, snare_offset, hihats, openhats, bpm):
    # following code is mostly taken for Ciska's example

    # set the necessary values for MIDI util
    velocity = 100
    track = 0
    channel = 9  # corresponds to channel 10 drums

    # create the MIDIfile object, to which we can add notes
    mf = MIDIFile(1)
    # set name and tempo
    time_beginning = 0
    mf.addTrackName(track, time_beginning, "generated rhythm")
    mf.addTempo(track, time_beginning, bpm)

    time = 0

    # add the notes for the kick
    kick_midi_pitch = 36
    for dur in kicks:
        mf.addNote(track, channel, kick_midi_pitch, time, dur / 2, velocity)
        # increment time based on the duration of the added note
        time = time + (dur / 2)

    time = 0

    # add the notes for the hihat
    hihat_midi_pitch = 42
    for dur in hihats:
        mf.addNote(track, channel, hihat_midi_pitch, time, dur / 4, velocity)
        # increment time based on the duration of the added note
        time = time + (dur / 4)

    time = 0

    # add the notes for the open-hat
    openhat_midi_pitch = 46
    for dur in openhats:
        mf.addNote(track, channel, openhat_midi_pitch, time, dur / 2, velocity)
        # increment time based on the duration of the added note
        time = time + (dur / 2)

    # reset the time to snare offset in case the snare does not start at the beginning
    time = snare_offset / 2
    # add the notes for the snare
    snare_midi_pitch = 38
    for dur in snares:
        mf.addNote(track, channel, snare_midi_pitch, time, dur / 2, velocity)
        # increment time based on the duration of the added note
        time = time + (dur / 2)

    # variable to find path to sub folder
    filepath = os.path.abspath("./exports/generated_rhythm.midi")

    with open(filepath, "wb") as outf:
        mf.writeFile(outf)


def get_midi(kicks, snares, snare_offset, hihats, openhats, bpm):
    # asks if user wants to save the rhythm as midi
    text1 = "\ndo you want to save this rhythm as midi?"
    text2 = " y/n\n\n"

    while True:
        value = input(Text.BLUE + Text.UNDERLINE + text1 + Text.END + text2)

        if value.lower() == "y":
            save_to_midi(kicks, snares, snare_offset, hihats, openhats, bpm)
            print("\nyour rhythm has been saved in the exports folder :)")
            break
        elif value.lower() == "n":
            print("\nok bye")
            quit()
        else:
            print("please type 'y' or 'n' :) ")
