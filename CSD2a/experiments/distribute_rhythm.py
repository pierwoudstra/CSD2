import random

def generate_rhythm(num):

    print("input: " + str(num))

    array = []

    while True:
        if num == 6:
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
            num = num-2

    random.shuffle(array)

    return array

def distribute_rhythm(durations):
    kick_pattern = []
    snare_pattern = []

    # every third duration is a kick
    for i in range(0, len(durations), 4):
        kick_pattern.append(sum(durations[i:i+4]))

    # for i in range(1, len(durations)):
    #     snare_pattern.append(durations[i])

    snare_offset = durations.pop(0)

    for i in range(0, len(durations), 4):
        snare_pattern.append(durations[i])

    for i in range(1, len(durations), 4):
        print(i)
        snare_pattern.append(sum(durations[i:i+3]))

    return kick_pattern, snare_pattern, snare_offset

# change 4 into 3
# change 3 into 2

# generate rhythm
input_durations = generate_rhythm(7)
print(input_durations)

# distribute rhythm
kick, snare, snare_offset = distribute_rhythm(input_durations)

# print output
print('kick: ' + str(kick) )
print('snare: ' + str(snare) )
print('snare offset: ' + str(snare_offset) )
