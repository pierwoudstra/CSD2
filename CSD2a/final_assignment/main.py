#
# irregular rhythm generator
#

from user_input import get_info, get_midi
from generate import generate_sequence, sequence_to_timestamps
from play_ts import play_timestamps


def main():
    # get input from user
    meter, bpm, sound_choice = get_info()

    # generate a rhythm
    kicks, snares, snare_offset, hihats, openhats = generate_sequence(meter)

    # convert rhythm to timestamps
    timestamps = sequence_to_timestamps(
        kicks, snares, snare_offset, hihats, openhats, bpm
    )

    # play rhythm
    play_timestamps(timestamps, sound_choice)

    # ask if user wants to save rhythm
    get_midi(kicks, snares, snare_offset, hihats, openhats, bpm)


main()
