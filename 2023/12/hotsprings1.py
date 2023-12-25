import re
from itertools import product


def arrangement_is_valid(candidate: str, group_sizes: list[int]) -> bool:
    broken_groups = re.split(r'\.+', candidate)
    candidate_group_sizes = [len(group) for group in broken_groups if len(group) > 0]
    return candidate_group_sizes == group_sizes


file = open('2023/12/input.txt', 'r')
lines = [line.strip() for line in file.readlines()]
n_rows = len(lines)
n_cols = len(lines[0])

n_possible_arrangements = 0
current_row = 0
for line in lines:
    print('{}/{}'.format(current_row, n_rows))
    split = line.split(' ')
    condition_str = split[0]
    conditions = list(condition_str)
    group_sizes_str = split[1]
    group_sizes = [int(s) for s in group_sizes_str.split(',')]

    unknown_indices = [idx for idx, char in enumerate(condition_str) if char == '?']
    combinations = product('.#', repeat=len(unknown_indices))
    for combination in combinations:
        candidate = conditions
        for idx, c in zip(unknown_indices, combination):
            candidate[idx] = c
        if arrangement_is_valid(''.join(candidate), group_sizes):
            n_possible_arrangements += 1
    current_row += 1

print(n_possible_arrangements)
