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

    for note in chopped_array:
        if note == 'k':
            timestamps.append(['kick', sixteenthnote_dur])
        elif note == 's':
            timestamps.append(['snare', sixteenthnote_dur])
        else:
            timestamps.append(['~', sixteenthnote_dur])

    timestamps_no_rests = []

    sum = 0.0
    for i in range(len(timestamps)):
        timestamps[i][1] = sum
        sum = sum + sixteenthnote_dur

        if timestamps[i][0] != '~':
            timestamps_no_rests.append(timestamps[i])

    return timestamps_no_rests

def play_sample(file_path):
    wave_object = sa.WaveObject.from_wave_file(file_path)
    play_object = wave_object.play()
    play_object.wait_done()

def play_array(timestamps):
    if timestamps:
        current_ts = timestamps.pop(0)
    else:
        exit()

    # get starting time
    time_zero = time.time()

    while True:
        now = time.time() - time_zero

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