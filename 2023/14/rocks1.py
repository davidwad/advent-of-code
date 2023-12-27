from queue import PriorityQueue
from enum import Enum


class RockType(Enum):
    SQUARE = 1
    ROUND = 2
    EMPTY = 3

file = open('2023/14/input.txt', 'r')
lines = [line.strip() for line in file.readlines()]
n_rows = len(lines)
n_cols = len(lines[0])


columns: list[str] = [''] * n_cols
for i in range(n_cols):
    for line in lines:
        columns[i] += line[i]

sum = 0
for column in columns:
    queue = PriorityQueue()
    priority = 0
    for char in column:
        if char == '#':
            priority += 100
            queue.put((priority, RockType.SQUARE.value))
        elif char == 'O':
            queue.put((priority, RockType.ROUND.value))
        else:
            queue.put((priority, RockType.EMPTY.value))
    
    load = n_rows
    while load > 0:
        element = queue.get()
        if element[1] == RockType.ROUND.value:
            sum += load
        load -= 1

print(sum)