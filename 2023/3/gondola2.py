import numpy as np
import re
from dataclasses import dataclass


@dataclass
class SchematicNumber:
    value: int
    indexes: list[tuple[int, int]]


def adjacent_numbers(gear: tuple[int, int], numbers: list[SchematicNumber]) -> list[int]:
    adjacent_numbers = set()
    y = gear[0]
    x = gear[1]

    for i in [max(y - 1, 0), y, min(y + 1, schematic.shape[0] - 1)]:
        for j in [max(x - 1, 0), x, min(x + 1, schematic.shape[1] - 1)]:
            for number in numbers:
                if is_adjacent((i, j), number):
                    adjacent_numbers.add(number.value)

    return list(adjacent_numbers)


def is_adjacent(gear_index: tuple[int, int], number: SchematicNumber):
    for index in number.indexes:
        if gear_index == index:
            return True
    return False


sum = 0

file = open('input.txt', 'r')
lines = [line.strip() for line in file.readlines()]

schematic = np.zeros((len(lines), len(lines[0])))
schematic_numbers: list[SchematicNumber] = []
gears = []

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
        elif char == '*':
            gears.append((i, j))

for gear in gears:
    adjacent_nums = adjacent_numbers(gear, schematic_numbers)
    if len(adjacent_nums) == 2:
        sum += adjacent_nums[0] * adjacent_nums[1]

print(sum)
