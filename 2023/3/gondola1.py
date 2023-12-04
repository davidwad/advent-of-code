import numpy as np
import re
from dataclasses import dataclass


@dataclass
class SchematicNumber:
    value: int
    indexes: list[tuple[int, int]]


def has_adjacent_symbol(indexes: list[tuple[int, int]], schematic: np.ndarray):
    for index in indexes:
        y = index[0]
        x = index[1]
        for i in [max(y - 1, 0), y, min(y + 1, schematic.shape[0] - 1)]:
            for j in [max(x - 1, 0), x, min(x + 1, schematic.shape[1] - 1)]:
                if schematic[i, j] == -1:
                    return True
    return False


sum = 0

file = open('input.txt', 'r')
lines = [line.strip() for line in file.readlines()]

schematic = np.zeros((len(lines), len(lines[0])))
schematic_numbers: list[SchematicNumber] = []

for i, line in enumerate(lines):
    matches = re.finditer(r'\d+', line)
    for match in matches:
        span = match.span()
        indexes = [(i, j) for j in range(span[0], span[1])]
        number = SchematicNumber(value=int(match.group(0)), indexes=indexes)
        schematic_numbers.append(number)

    for j, char in enumerate(line):
        if char.isdigit():
            schematic[i, j] = int(char)
        elif not char == '.':
            schematic[i, j] = -1

for number in schematic_numbers:
    if has_adjacent_symbol(number.indexes, schematic):
        sum += number.value

print(sum)
