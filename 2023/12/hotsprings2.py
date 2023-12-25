import re


def num_possible_arrangements(conditions: str, group_sizes: list[int]) -> int:
    n_possible_arrangements = 0
    group_sizes = sorted(group_sizes, reverse=True)
    biggest_group = max(group_sizes)
    pure_matches = re.finditer(r'(?=(#{{{}}}))'.format(biggest_group), conditions)
    mixed_matches = re.finditer(r'(?=([#\?]{{{}}}))'.format(biggest_group), conditions)

    # Pick out all the pure matches. Surround them with operational machines and call function with the surrounding machines.
    for match in pure_matches:
        conditions_list = list(conditions)
        start = max(match.start(1), 0)
        end = min(match.end(1), len(conditions_list) - 1)
        conditions_list[max(match.start(1) - 1, 0)] = '.'
        conditions_list[min(match.end(1), len(conditions_list) - 1)] = '.'
        conditions_list = conditions_list[:start] + conditions_list[end:]
        conditions_str = ''.join(conditions_list)

        print('-' * 99)
        print(start)
        print(end)
        print(conditions)
        print(conditions_str)

        n_possible_arrangements += num_possible_arrangements(condition_str, group_sizes)

    # TODO: Pick out all mixed matches. Make a base case
    return 1


file = open('2023/12/example_input.txt', 'r')
lines = [line.strip() for line in file.readlines()]
n_rows = len(lines)
n_cols = len(lines[0])

n_possible_arrangements = 0
current_row = 0
for line in lines:
    split = line.split(' ')
    condition_str = split[0]
    conditions = list(condition_str)
    group_sizes_str = split[1]
    group_sizes = [int(s) for s in group_sizes_str.split(',')]

    unknown_indices = [idx for idx, char in enumerate(condition_str) if char == '?']
    n_possible_arrangements += num_possible_arrangements(condition_str, group_sizes)
    current_row += 1

print(n_possible_arrangements)
