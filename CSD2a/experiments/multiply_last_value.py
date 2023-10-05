import random

array = [3, 2, 3]

rand_int = random.randint(2, 5)

print(rand_int)

last_num = array.pop()

for _ in range(rand_int):
    array.append(last_num/rand_int)

print(array)