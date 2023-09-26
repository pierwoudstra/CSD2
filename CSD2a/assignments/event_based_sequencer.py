# event based sequencer:
# sequence samples with better timing

import simpleaudio as sa
import time

def get_info():
    
    rhythm_array = 'k--s--k-k---s---'
    bpm = 114.0

    return rhythm_array, bpm

def rhythm_to_timestamps(rhythm_array, bpm):
    quarternote_dur = 60.0 / bpm
    sixteenthnote_dur = quarternote_dur / 4

    chopped_array = [i for i in rhythm_array]

    timestamps = []

    sum = 0.0
    for note in chopped_array:
        if note == 'k':
            timestamps.append(['kick', sum])
        elif note == 's':
            timestamps.append(['snare', sum])
        else:
            timestamps.append(['~', sum])

        sum += sixteenthnote_dur

    timestamps_no_rests = [ts for ts in timestamps if ts[0] != '~']

    return timestamps_no_rests

def play_sample(file_path):
    wave_object = sa.WaveObject.from_wave_file(file_path)
    play_object = wave_object.play()

def play_array(timestamps):
    if timestamps:
        current_ts = timestamps.pop(0)
    else:
        exit()

    # get starting time
    time_zero = time.time()

    while True:
        now = time.time() - time_zero

        print(now)

        if now >= current_ts[1]:
            play_sample("samples/" + current_ts[0] + ".wav")
            if timestamps:
                current_ts = timestamps.pop(0)
            else:
                break
        
        time.sleep(0.001)
   

def main():
    rhythm_array, bpm = get_info()
    timestamps = rhythm_to_timestamps(rhythm_array, bpm)
    print(timestamps)

    # TODO make a way to get input and convert it to timestamps
    # TODO make arrays based on loop amount
    play_array(timestamps)
    time.sleep(2)

main()