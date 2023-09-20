import simpleaudio as sa
import time

def get_info():
    rhythm_array = [['k',0], ['h',0], ['s', 0.75], ['s', 1.5], ['k', 2.5], ['s', 3.0], ['s', 4.0]]
    bpm = 114.0
    loop_amt = 1

    return rhythm_array, bpm, loop_amt

def play_sample(file_path):
    wave_object = sa.WaveObject.from_wave_file(file_path)
    wave_object.play()

def play_array(rhythm_array, bpm, loop_amt):

    # get first timestamp
    if rhythm_array:
        current_ts = rhythm_array.pop(0)
    else:
        play_array(rhythm_array,bpm,loop_amt)

    # get starting time
    time_zero = time.time()

    while True:
        now = time.time() - time_zero
        if now >= current_ts[1]:
            play_sample("samples/kick.wav") if current_ts[0] == 'k' else play_sample("samples/snare.wav")

            if rhythm_array:
                current_ts = rhythm_array.pop(0)
            else:
                break
        
        time.sleep(0.00000001)



def main():
    rhythm_array, bpm, loop_amt = get_info()
    play_array(rhythm_array, bpm, loop_amt)

main()