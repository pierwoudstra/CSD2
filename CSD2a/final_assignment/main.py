from user_input import get_info
from generate import generate_sequence, sequence_to_timestamps

def main():
    meter, bpm, sound_choice = get_info()
    sequence = generate_sequence(meter, bpm)
    timestamps = sequence_to_timestamps(sequence)
    play_timestamps(timestamps, sound_choice)
    save_to_midi(sequence)


main()
