import random


def divide_2s_3s(num):
    # divides an input number into 2's and 3's
    array = []

    while True:
        if num == 6: # maximum of two 3's
            array.append(3)
            array.append(3)
            break
        elif num == 3:
            array.append(3)
            break
        elif num == 2:
            array.append(2)
            break
        else:
            array.append(2)
            num = num - 2

    # shuffles array
    random.shuffle(array)

    return array


def distribute_rhythm(durations):
    kicks = []
    snares = []

    # every third duration is a kick
    for i in range(0, len(durations), 3):
        kicks.append(sum(durations[i : i + 3]))

    # remove first duration for snare
    snare_offset = durations.pop(0)

    # first of every three durations gets added to snare list
    for i in range(0, len(durations), 3):
        snares.append(durations[i])

    # every second and third duration gets summed
    for i in range(1, len(durations), 3):
        snares.append(sum(durations[i : i + 2]))

    return kicks, snares, snare_offset


def multiply_last_value(array):
    # choose multiplication amount
    rand_int = random.randint(1, 3)

    # use last number
    last_num = array.pop()

    # divide and multiply last value
    for _ in range(rand_int):
        array.append(last_num / rand_int)

    return array


def generate_kick_snare(meter):
    # generate general rhythm
    durations = divide_2s_3s(meter)

    # distribute rhythm between kicks and snares
    kicks, snares, snare_offset = distribute_rhythm(durations)

    # duplicate kicks
    kicks *= 2

    # duplicate snares
    snares[len(snares) - 1] += snare_offset
    snares += snares
    snares[len(snares) - 1] -= snare_offset

    # make fill at the end of the sequence
    snares = multiply_last_value(multiply_last_value(snares))

    return kicks, snares, snare_offset


def generate_hihat(meter):
    # hihats use double meter to work in sixteenth notes and not eighth
    double_meter = meter

    # generate hihats
    hihats = divide_2s_3s(double_meter)

    # double length
    hihats = hihats * 4

    # add fill at the end
    hihats = multiply_last_value(multiply_last_value(hihats))

    # open hat at start of every bar
    openhats = [meter, meter]

    return hihats, openhats


def generate_sequence(meter):
    # generate kicks and snares
    # ( in one function because one rhythm gets distributed between two sounds )
    kicks, snares, snare_offset = generate_kick_snare(meter)

    # generate hihats
    hihats, openhats = generate_hihat(meter)

    return kicks, snares, snare_offset, hihats, openhats


def kicks_to_ts(kicks, bpm):
    kicks_timestamps = []
    kicks_durations = []

    # use bpm in durations
    quarternote = 60.0 / bpm
    eighthnote = quarternote / 2

    # make kicks correct length
    for dur in kicks:
        kicks_durations.append(eighthnote * dur)

    # add kicks to list
    sum = 0.00
    for note_dur in kicks_durations:
        kicks_timestamps.append({"instrument": "kick", "ts": float(sum)})
        sum += note_dur

    return kicks_timestamps


def snares_to_ts(snares, snare_offset, bpm):
    snares_ts = []
    snares_durations = []

    # use bpm in durations
    quarternote = 60.0 / bpm
    eighthnote = quarternote / 2

    # make snares correct length
    for dur in snares:
        snares_durations.append(eighthnote * dur)

    snare_offset *= eighthnote

    # add snares to list
    sum = snare_offset
    for note_dur in snares_durations:
        snares_ts.append({"instrument": "snare", "ts": float(sum)})
        sum += note_dur

    return snares_ts


def hihats_to_ts(hihats, openhats, bpm):
    quarternote = 60.0 / bpm
    eighthnote = quarternote / 2.0
    sixteenthnote = eighthnote / 2.0  # hihats are in sixteenth notes

    openhats_durations = []
    for note_dur in openhats:
        openhats_durations.append(eighthnote * note_dur)

    hihats_durations = []
    # convert to sixeenths
    for note_dur in hihats:
        hihats_durations.append(sixteenthnote * note_dur)

    hihats_timestamps = []

    sum = 0.0

    for note_dur in hihats_durations:
        hihats_timestamps.append({"instrument": "hihat", "ts": float(sum)})
        sum += note_dur

    sum = 0.0

    for note_dur in openhats_durations:
        hihats_timestamps.append({"instrument": "openhat", "ts": float(sum)})
        sum += note_dur

    return hihats_timestamps


def sequence_to_timestamps(kicks, snares, snare_offset, hihats, openhats, bpm):
    # convert kicks to timestamps
    kicks_ts = kicks_to_ts(kicks, bpm)

    # convert snares to timestamps
    snares_ts = snares_to_ts(snares, snare_offset, bpm)

    # convert hihats to timestamps
    hihats_timestamps = hihats_to_ts(hihats, openhats, bpm)

    timestamps = kicks_ts + snares_ts + hihats_timestamps

    timestamps = sorted(
        timestamps, key=lambda x: x["ts"]
    )  # used lambda function for elegant sort function

    return timestamps
