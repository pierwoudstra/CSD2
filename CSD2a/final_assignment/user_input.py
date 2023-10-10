class Text:
    BLUE = "\033[94m"
    RED = "\033[91m"
    UNDERLINE = "\033[4m"
    END = "\033[0m"


def get_meter():
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
    text1 = "\nwhat kind of sounds do you want to hear?\n\n"
    text2 = "~ type '1' for baile funk 🇧🇷\n~ type '2' for hyperpop 💿\n~ type '3' for balkan traditional 🪗\n\n"

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
    meter = get_meter()
    bpm = get_bpm()
    sound_choice = get_sound_choice()

    return meter, bpm, sound_choice
