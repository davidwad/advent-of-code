from queue import PriorityQueue
from enum import Enum
from matplotlib import pyplot as plt


class RockType(Enum):
    SQUARE = 1
    ROUND = 2
    EMPTY = 3


def shuffle_north(platform: list[list[str]]):
    columns: list[list[str]] = [[] for _ in range(n_cols)]
    for i in range(n_cols):
        for row in platform:
            columns[i].append(row[i])
    shuffled_columns = [shuffle_rocks(col) for col in columns]
    for i in range(n_rows):
        for j in range(n_cols):
            platform[i][j] = shuffled_columns[j][i]


def shuffle_west(platform: list[list[str]]):
    for i in range(len(platform)):
        platform[i] = shuffle_rocks(platform[i])


def shuffle_south(platform: list[list[str]]):
    columns: list[list[str]] = [[] for _ in range(n_cols)]
    for i in range(n_cols):
        for row in platform:
            columns[i].append(row[i])
    shuffled_columns = [shuffle_rocks_reverse(col) for col in columns]
    for i in range(n_rows):
        for j in range(n_cols):
            platform[i][j] = shuffled_columns[j][i]


def shuffle_east(platform: list[list[str]]):
    for i in range(len(platform)):
        platform[i] = shuffle_rocks_reverse(platform[i])


def shuffle_rocks(rocks: list[str]) -> list[str]:
    queue = PriorityQueue()
    priority = 0
    for char in rocks:
        if char == '#':
            priority += 100
            queue.put((priority, RockType.SQUARE.value))
        elif char == 'O':
            queue.put((priority, RockType.ROUND.value))
        else:
            queue.put((priority, RockType.EMPTY.value))

    result = []
    for _ in range(len(rocks)):
        element = queue.get()[1]
        if element == RockType.SQUARE.value:
            result.append('#')
        elif element == RockType.ROUND.value:
            result.append('O')
        else:
            result.append('.')
        
    return result


def shuffle_rocks_reverse(rocks: list[str]) -> list[str]:
    queue = PriorityQueue()
    priority = 0
    rocks.reverse()
    for char in rocks:
        if char == '#':
            priority -= 100
            queue.put((priority, -RockType.SQUARE.value))
        elif char == 'O':
            queue.put((priority, -RockType.ROUND.value))
        else:
            queue.put((priority, -RockType.EMPTY.value))

    result = []
    for _ in range(len(rocks)):
        element = queue.get()[1]
        if element == -RockType.SQUARE.value:
            result.append('#')
        elif element == -RockType.ROUND.value:
            result.append('O')
        else:
            result.append('.')

    return result


def calculate_load(platform: list[list[str]]) -> int:
    total_load = 0
    columns: list[list[str]] = [[] for _ in range(n_cols)]
    for i in range(n_cols):
        for row in platform:
            columns[i].append(row[i])
    for column in columns:
        load = len(platform)
        for char in column:
            if char == 'O':
                total_load += load
            load -= 1
    return total_load


def print_platform(platform: list[list[str]]):
    print('-' * 99)
    for row in platform:
        print(row)


TOTAL_CYCLES = 1000000000
TRIAL_CYCLES = 230 # TOTAL CYCLES % PERIOD = TRIAL_CYCLES % PERIOD => last load is correct if number of trail cycles is sufficient
PERIOD = 70  # Experimental

file = open('2023/14/input.txt', 'r')
platform = [list(line.strip()) for line in file.readlines()]
n_rows = len(platform)
n_cols = len(platform[0])

loads = []
for idx in range(TRIAL_CYCLES):
    shuffle_north(platform)
    shuffle_west(platform)
    shuffle_south(platform)
    shuffle_east(platform)

    load = calculate_load(platform)
    loads.append(load)

print(loads[-1])
plt.plot(loads)
plt.show()
