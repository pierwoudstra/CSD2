import simpleaudio as sa
import time

def get_info():
    timestamps = [['kick',0], ['hihat',0], ['snare', 0.75], ['snare', 1.5], ['kick', 2.5], ['snare', 3.0], ['snare', 4.0]]
    # bpm = 114.0
    # loop_amt = 1

    return timestamps

def play_sample(file_path):
    wave_object = sa.WaveObject.from_wave_file(file_path)
    play_object = wave_object.play()
    play_object.wait_done()

def play_array(timestamps):
    # get starting time
    time_zero = time.time()

    current_ts = timestamps[0]

    # TODO make loop that handles timestamps and plays right sample
    while True:

        if current_ts[1] > time_zero:
            play_sample("samples/" + current_ts[0] + ".wav")
        else:
            break


def main():
    timestamps = get_info()
    play_array(timestamps)

main()