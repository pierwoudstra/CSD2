import random

array = [3, 2, 3]

def multiply_last_value(array):
    rand_int = random.randint(2, 5)

    last_num = array.pop()

    for _ in range(rand_int):
        array.append(last_num/rand_int)

    return array

print(multiply_last_value(array))
