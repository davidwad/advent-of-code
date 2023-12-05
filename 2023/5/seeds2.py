import re
from dataclasses import dataclass


@dataclass
class Range:
    min: int
    max: int


class Map:
    def __init__(self, destination: int, source: int, range: int):
        self.allowed_source_range = Range(source, source + range - 1)
        self.term = destination - source

    def contains(self, source: Range) -> bool:
        return source.max >= self.allowed_source_range.min and source.min <= self.allowed_source_range.max

    def get_destination(self, source: Range) -> list[Range]:
        destinations = []
        unmapped = []

        if source.min < self.allowed_source_range.min:
            unmapped.append(Range(min=source.min, max=self.allowed_source_range.min - 1))

        destinations.append(Range(min=max(self.allowed_source_range.min, source.min) + self.term,
                                  max=min(self.allowed_source_range.max, source.max) + self.term))

        if source.max > self.allowed_source_range.max:
            unmapped.append(Range(min=self.allowed_source_range.max + 1, max=source.max))

        return destinations, unmapped


file = open('input.txt', 'r')
lines = [line.strip() for line in file.readlines()]

seeds_str = lines[0].split(':')[1].split(' ')
seed_ints = [int(n.strip()) for n in seeds_str if n != '']
seeds: list[Range] = []

for idx in range(0, len(seed_ints), 2):
    seed_min = seed_ints[idx]
    seed_max = seed_min + seed_ints[idx + 1] - 1
    seeds.append(Range(min=seed_min, max=seed_max))

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

locations: list[Range] = []

for seed in seeds:
    sources = [seed]
    for category_maps in maps:
        original_sources = [s for s in sources]
        new_sources = []
        for map in category_maps:
            for source in sources:
                if map.contains(source):
                    results, unmapped = map.get_destination(source)
                    sources.remove(source)
                    sources.extend(unmapped)
                    new_sources.extend(results)
                    break
        sources.extend(new_sources)
    locations.extend(sources)

min_locs = [loc.min for loc in locations]
types = [type(loc.min) for loc in locations]
min_locs.sort()
print(min_locs[0])
