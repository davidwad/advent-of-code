import re


def get_steps(instructions: str, nodes: dict[str, tuple[str, str]]) -> int:
    n_steps = 0
    source = 'AAA'
    while True:
        for direction in instructions:
            n_steps += 1
            if direction == 'L':
                destination = nodes[source][0]
            else:
                destination = nodes[source][1]
            if destination == 'ZZZ':
                return n_steps
            else:
                source = destination


pattern = r'([A-Z]{3}) = \(([A-Z]{3}), ([A-Z]{3})\)'

file = open('input.txt', 'r')
lines = [line.strip() for line in file.readlines()]

instructions = lines[0]
# print(instructions)

nodes: dict[str, tuple[str, str]] = {}
for line in lines[2:]:
    source, left, right = re.match(pattern, line).groups()
    nodes[source] = (left, right)
    # print(source + ' --> (' + left + ', ' + right + ')')

print(get_steps(instructions, nodes))
