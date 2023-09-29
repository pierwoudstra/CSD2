# event based sequencer:
# sequence samples with better timing

import simpleaudio as sa
import time

kick = sa.WaveObject.from_wave_file("samples/kick.wav")
snare = sa.WaveObject.from_wave_file("samples/snare.wav")
hihat = sa.WaveObject.from_wave_file("samples/hihat.wav")

def get_info():
    
    rhythm_array = 'k-s-k-s-k-s-k-s-k-s-k-s-k-s-k-s-'
    bpm = 60.0

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

def play_sample(instrument):
    if instrument == 'kick':
        kick.play()
    elif instrument == 'snare':
        snare.play()
    elif instrument == 'hihat':
        hihat.play()
    # play_object.wait_done()

def play_array(timestamps):
    # get starting time
    time_zero = time.time()

    current_ts = timestamps.pop(0)

    while True:

        print(current_ts)

        now = time.time() - time_zero

        # print("current ts = " + str(current_ts))

        if now < current_ts[1]:
            time.sleep(current_ts[1] - now)
            now = time.time() - time_zero

        play_sample(current_ts[0])
        
        if timestamps:
            current_ts = timestamps.pop(0)
        else:
            time.sleep(0.5)
            break
        

        # if now >= current_ts[1]:
        #     print("now = " + str(now))
        #     play_sample(current_ts[0])
        #     if timestamps:
        #         current_ts = timestamps.pop(0)
        #     else:
        #         break
        
        # time.sleep(0.001)
   

def main():
    rhythm_array, bpm = get_info()
    timestamps = rhythm_to_timestamps(rhythm_array, bpm)
    print(timestamps)

    # TODO make arrays based on loop amount
    play_array(timestamps)
    time.sleep(2)

main()