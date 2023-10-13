import random

def generate_kick_snare(meter):
    meter2 = meter # second meter for generating the snare

    kicks = []
    snares = []

    # generate kicks
    while True:
        if meter == 7:
            kicks.append(7)
            break
        elif meter == 4:
            kicks.append(4)
            break
        elif meter == 5:
            kicks.append(4)
            kicks.append(1)
            break
        elif meter == 6:
            kicks.append(4)
            kicks.append(2)
            break
        elif meter == 3:
            kicks.append(3)
            break
        else:
            kicks.append(5)
            meter = meter-5

    random.shuffle(kicks) # shuffles kicks

    # generate snares
    while True:
        if meter2 == 9:
            snares.append(2)
            snares.append(2)
            snares.append(5)
            break
        elif meter2 == 6:
            snares.append(3)
            snares.append(3)
            break
        elif meter2 == 3:
            snares.append(3)
            break
        elif meter2 == 4:
            snares.append(1)
            snares.append(3)
            break
        else:
            snares.append(2)
            meter2 = meter2-2

    random.shuffle(snares)

    snare_offset = float(snares.pop(0))

    # make fill at the end
    rand_int = random.randint(1, 3)

    last_num = kicks.pop()

    for _ in range(rand_int):
        kicks.append(last_num/rand_int)

    # loop kick pattern
    for _ in range(2):
        kicks += kicks

    # loop snare pattern
    last_snare = snares.pop()
    last_snare += snare_offset
    snares.append(float(last_snare))
    for _ in range(2):
        snares += snares

    return kicks, snares, snare_offset


def generate_hihat(meter):
    num = meter * 2

    hihats = []

    # fill array with either 2's or 3's
    while True:
        if num == 6:
            hihats.append(3)
            hihats.append(3)
            break
        elif num == 3:
            hihats.append(3)
            break
        elif num == 2:
            hihats.append(2)
            break
        else:
            hihats.append(2)
            num = num-2

    # loop hihat pattern
    for _ in range(2):
        hihats += hihats

    openhats = [meter, meter, meter, meter]

    return hihats, openhats


def generate_sequence(meter):
    kicks, snares, snare_offset = generate_kick_snare(meter)
    hihats, openhats = generate_hihat(meter)
   
    return kicks, snares, snare_offset, hihats, openhats


def kicks_snares_to_ts(kicks, snares, snare_offset, bpm):
    kicks_snares_ts = []

    # use bpm in durations
    quarternote = 60.0 / bpm
    eighthnote = quarternote / 2

    # make kicks correct length
    kicks2 = []

    for dur in kicks:
        kicks2.append(eighthnote * dur)

    # make snares correct length
    snares2 = []

    for dur in snares:
        snares2.append(eighthnote * dur)

    snare_offset *= eighthnote

    # add kicks to new list
    sum = 0.00
    for note_dur in kicks2:
        kicks_snares_ts.append({'instrument': 'kick', 'ts': float(sum)})
        sum += note_dur

    # add snares to new list
    sum = snare_offset
    for note_dur in snares2:
        kicks_snares_ts.append({'instrument': 'snare', 'ts': float(sum)})
        sum += note_dur

    return kicks_snares_ts


def hihats_to_ts(hihats, openhats, bpm):
    quarternote = 60.0 / bpm
    eighthnote = quarternote / 2.0
    sixteenthnote = eighthnote / 2.0 # here we use sixteenth notes

    openhats2 = []
    for note_dur in openhats:
        openhats2.append(eighthnote * note_dur)

    hihats2 = []
    # convert to sixeenths
    for note_dur in hihats:
        hihats2.append(sixteenthnote * note_dur)

    hihats_timestamps = []

    sum = 0.0

    for note_dur in hihats2:
        hihats_timestamps.append({'instrument': "hihat", 'ts': float(sum)})
        sum += note_dur

    sum = 0.0

    for note_dur in openhats2:
        hihats_timestamps.append({'instrument': "openhat", 'ts': float(sum)})
        sum += note_dur

    return hihats_timestamps


def sequence_to_timestamps(kicks, snares, snare_offset, hihats, openhats, bpm):
    kicks_snares_ts = kicks_snares_to_ts(kicks, snares, snare_offset, bpm)
    hihats_timestamps = hihats_to_ts(hihats, openhats, bpm)

    timestamps = kicks_snares_ts + hihats_timestamps

    timestamps = sorted(timestamps, key=lambda x: x['ts']) # used lambda function for elegant sort function

    return timestamps
