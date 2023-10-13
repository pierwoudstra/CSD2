import random

num = 15 # natural number between 2 and ∞
num2 = num

print("input: " + str(num))

kicks = []
snares = []

while True:
    if num == 7:
        kicks.append(7)
        break
    elif num == 4:
        kicks.append(4)
        break
    elif num == 5:
        kicks.append(4)
        kicks.append(1)
        break
    elif num == 6:
        kicks.append(4)
        kicks.append(2)
        break
    elif num == 3:
        kicks.append(3)
        break
    else:
        kicks.append(5)
        num = num-5

random.shuffle(kicks)

print("output kicks: " + str(kicks))

while True:
    if num2 == 9:
        snares.append(2)
        snares.append(2)
        snares.append(5)
        break
    elif num2 == 6:
        snares.append(3)
        snares.append(3)
        break
    elif num2 == 3:
        snares.append(3)
        break
    elif num2 == 4:
        snares.append(1)
        snares.append(3)
        break
    else:
        snares.append(2)
        num2 = num2-2

random.shuffle(snares)

snare_offset = snares.pop(0)

print("output snares: " + str(snares))
print("offset: " + str(snare_offset))