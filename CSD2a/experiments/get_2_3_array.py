import random

num = 7 # natural number between 2 and ∞

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

print("output: " + str(array))