def sum_every_three(lst):
    result = []
    for i in range(0, len(lst), 3):
        result.append(lst[i])

    for i in range(1, len(lst), 3):
        print(i)
        result.append(sum(lst[i:i+2]))
    return result

# input_list = [1, 2, 3, 4, 5, 6, 7]

# output_list = input_list[1::3] + input_list[2::3]
# output_list.sort()

# print(output_list)



# Example usage
input_list = [2, 2, 2, 2, 2, 2, 2, 3, 2]
output = sum_every_three(input_list)
print(output)