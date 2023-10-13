#
# irregular rhythm generator 
#

from user_input import get_info, ask_midi
from generate import generate_sequence, sequence_to_timestamps
from play_ts import play_timestamps

def main():
    meter, bpm, sound_choice = get_info()
    kicks, snares, snare_offset, hihats, openhats = generate_sequence(meter)
    timestamps = sequence_to_timestamps(kicks, snares, snare_offset, hihats, openhats, bpm)
    play_timestamps(timestamps, sound_choice)
    ask_midi(kicks, snares, snare_offset, hihats, openhats, bpm)


main()
