def get_info():
    meter = input("what do you want the time signature to be? (in eighth notes) \n put '5' for 5/8, '7' for 7/8, etc. \n ")
    bpm = input("what do you want the bpm to be? ")
    sound_choice = input("what sound would you like to hear? \n insert: \n 1 baile funk \n 2 drill \n 3 traditional \n \n")

    return meter, bpm, sound_choice
