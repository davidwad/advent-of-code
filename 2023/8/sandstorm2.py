import re


def get_steps_to_target(source: str, n_previous_steps: int, instructions: str, nodes: dict[str, tuple[str, str]]) -> (str, int):
    n_steps = 0
    for direction in instructions[n_previous_steps % len(instructions):]:
        n_steps += 1
        if direction == 'L':
            destination = nodes[source][0]
        else:
            destination = nodes[source][1]
        if destination[2] == 'Z':
            return destination, n_steps
        else:
            source = destination
    while True:
        for direction in instructions:
            n_steps += 1
            if direction == 'L':
                destination = nodes[source][0]
            else:
                destination = nodes[source][1]
            if destination[2] == 'Z':
                return destination, n_steps
            else:
                source = destination


def get_steps(instructions: str, nodes: dict[str, tuple[str, str]]) -> int:
    steps_to_target: dict[(str, int), (str, int)] = {}
    n_steps = 0
    sources = [s for s in nodes.keys() if s[2] == 'A']
    print(sources)
    steps_from_original_sources: dict[str, int] = {s: 0 for s in sources}
    sources: dict[str, str] = {s: s for s in sources}
    while True:
        kv_list = [(key, value) for key, value in steps_from_original_sources.items()]
        kv_list.sort(key=lambda x: x[1])
        original_source = kv_list[0][0]
        source = sources[original_source]
        direction = instructions[steps_from_original_sources[original_source] % len(instructions)]
        if source in steps_to_target:
            destination, n_steps = steps_to_target[(source, direction)]
        else:
            destination, n_steps = get_steps_to_target(source, steps_from_original_sources[original_source], instructions, nodes)
            steps_to_target[(source, direction)] = (destination, n_steps)

        sources[original_source] = destination
        steps_from_original_sources[original_source] += n_steps

        unique_steps = set(steps_from_original_sources.values())

        if len(unique_steps) == 1:
            # Done
            return unique_steps.pop()


pattern = r'([0-9A-Z]{3}) = \(([0-9A-Z]{3}), ([0-9A-Z]{3})\)'

file = open('input.txt', 'r')
lines = [line.strip() for line in file.readlines()]

instructions = lines[0]

nodes: dict[str, tuple[str, str]] = {}
for line in lines[2:]:
    source, left, right = re.match(pattern, line).groups()
    nodes[source] = (left, right)

print(get_steps(instructions, nodes))
