file = open('2023/15/input.txt', 'r')
line = file.readlines()[0]
steps = line.strip().split(',')

sum = 0
for step in steps:
    value = 0
    for char in step:
        value += ord(char)
        value = value * 17
        value = value % 256

    sum += value

print(sum)
