class GalaxyPair:
    def __init__(self, galaxy_1: tuple[int, int], galaxy_2: tuple[int, int]) -> None:
        self.galaxy_1 = galaxy_1
        self.galaxy_2 = galaxy_2
    
    def distance(self) -> int:
        i_1, j_1 = self.galaxy_1
        i_2, j_2 = self.galaxy_2
        return abs(i_1 - i_2) + abs(j_1 - j_2)
    
    def __eq__(self, other) -> bool:
        return self.galaxy_1 == other.galaxy_1 and self.galaxy_2 == other.galaxy_2 or self.galaxy_1 == other.galaxy_2 and self.galaxy_2 == other.galaxy_1

    def __hash__(self) -> int:
        return max(hash((hash(self.galaxy_1), hash(self.galaxy_2))), hash((hash(self.galaxy_2), hash(self.galaxy_1))))

file = open('input.txt', 'r')
lines = [line.strip() for line in file.readlines()]
n_rows = len(lines)
n_cols = len(lines[0])

# Get indices of expanded rows
idx = 0
expanded_rows: list[int] = []
for line in lines:
    if '#' not in line:
        expanded_rows.append(idx)
    idx += 1

# Get indices of expanded columns
columns: list[str] = [''] * n_cols
for i in range(n_cols):
    for line in lines:
        columns[i] += line[i]
idx = 0
expanded_columns: list[int] = []
for column in columns:
    if '#' not in column:
        expanded_columns.append(idx)
    idx += 1

# Original galaxy coordinates
original_galaxy_coords: list[tuple[int, int]] = []
for i, line in enumerate(lines):
    for j, char in enumerate(line):
        if char == '#':
            original_galaxy_coords.append((i, j))

# Expanded galaxy coordinates
expanded_galaxy_coords: list[tuple[int, int]] = []
for i, j in original_galaxy_coords:
    expanded_i = i
    expanded_j = j
    for row_idx in expanded_rows:
        if row_idx < i:
            expanded_i += 1
    for col_idx in expanded_columns:
        if col_idx < j:
            expanded_j += 1
    expanded_galaxy_coords.append((expanded_i, expanded_j))

# Calculate distance
calculated_pairs: set[GalaxyPair] = set()
sum = 0
for galaxy_1 in expanded_galaxy_coords:
    for galaxy_2 in expanded_galaxy_coords:
        pair = GalaxyPair(galaxy_1, galaxy_2)
        if pair not in calculated_pairs:
            sum += pair.distance()
            calculated_pairs.add(pair)

# print(original_galaxy_coords)
# print(expanded_galaxy_coords)
print(sum)