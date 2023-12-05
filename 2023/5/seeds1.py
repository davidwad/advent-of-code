import re


class Map:
    def __init__(self, destination: int, source: int, range: int):
        self.min_source = source
        self.max_source = source + range
        self.term = destination - source

    def contains(self, source: int) -> bool:
        return self.min_source <= source and source <= self.max_source

    def get_destination(self, source: int) -> int:
        return source + self.term


file = open('input.txt', 'r')
lines = [line.strip() for line in file.readlines()]

seeds_str = lines[0].split(':')[1].split(' ')
seeds = [int(n.strip()) for n in seeds_str if n != '']

map_regex_pattern = r'(\d+) (\d+) (\d+)'
sum = 0
maps: list[list[Map]] = []
category_maps = []

for line in lines[2:]:
    match = re.match(map_regex_pattern, line)
    if line == '':
        maps.append(category_maps)
        category_maps = []
    elif match:
        map_numbers = [int(g) for g in match.groups()]
        category_maps.append(Map(map_numbers[0], map_numbers[1], map_numbers[2]))

maps.append(category_maps)

locations = []

for seed in seeds:
    source = seed
    for category_maps in maps:
        for map in category_maps:
            if map.contains(source):
                source = map.get_destination(source)
                break
    locations.append(source)

print(min(locations))
