# TODO: The functions can_squeeze_x only work if you start on ground, but not while you are squeezing between pipes.
# Need different logic for when you are on a tile in the main loop
import sys
import networkx as nx


def can_go_left(i: int, j: int, map: list[list[str]]) -> bool:
    return j > 0 and (map[i][j-1] == '-' or map[i][j-1] == 'F' or map[i][j-1] == 'L' or map[i][j-1] == 'S')

def can_go_right(i: int, j: int, map: list[list[str]]) -> bool:
    return j < len(map[0]) - 1 and (map[i][j+1] == '-' or map[i][j+1] == '7' or map[i][j+1] == 'J' or map[i][j+1] == 'S')

def can_go_down(i: int, j: int, map: list[list[str]]) -> bool:
    return i < len(map) - 1 and (map[i+1][j] == '|' or map[i+1][j] == 'L' or map[i+1][j] == 'J' or map[i+1][j] == 'S')

def can_go_up(i: int, j: int, map: list[list[str]]) -> bool:
    return i > 0 and (map[i-1][j] == '|' or map[i-1][j] == '7' or map[i-1][j] == 'F' or map[i-1][j] == 'S')

def print_enclosed_map(dist: list[list[bool]]):
    for row in dist:
        row_str = ''
        for square in row:
            if square is None:
                row_str = row_str + 'X'
            elif square:
                row_str = row_str + 'I'
            else:
                row_str = row_str + 'O'
        print(row_str)

def print_map(map: list[list[str]]):
    for row in map:
        print(''.join(row))


s_is_vertical = True
file = open('input.txt', 'r')
lines = [line.strip() for line in file.readlines()]

n_rows = len(lines)
n_cols = len(lines[0])

map = []
enclosed_map = []
distance_map = []
graph = nx.Graph()
for i, line in enumerate(lines):
    chars = []
    enclosed_row = []
    distance_row = []
    for j, char in enumerate(line):
        if char != '.':
            graph.add_node((i, j))
        chars.append(char)
        enclosed_row.append(None)
        distance_row.append(sys.maxsize)
    map.append(chars)
    enclosed_map.append(enclosed_row)
    distance_map.append(distance_row)

sum = 0
for i, line in enumerate(lines):

    for j, char in enumerate(line):
        if char == 'S':
            start = (i, j)
            # Left
            if can_go_left(i, j, map):
                graph.add_edge((i, j), (i, j-1))
            # Right
            if can_go_right(i, j, map):
                graph.add_edge((i, j), (i, j+1))
            # Up
            if can_go_up(i, j, map):
                graph.add_edge((i, j), (i-1, j))
            # Down
            if can_go_down(i, j, map):
                graph.add_edge((i, j), (i+1, j))
        elif char == '-':
            # Left
            if can_go_left(i, j, map):
                graph.add_edge((i, j), (i, j-1))
            # Right
            if can_go_right(i, j, map):
                graph.add_edge((i, j), (i, j+1))
        elif char == '7':
            # Left
            if can_go_left(i, j, map):
                graph.add_edge((i, j), (i, j-1))
            # Down
            if can_go_down(i, j, map):
                graph.add_edge((i, j), (i+1, j))
        elif char == '|':
            # Up
            if can_go_up(i, j, map):
                graph.add_edge((i, j), (i-1, j))
            # Down
            if can_go_down(i, j, map):
                graph.add_edge((i, j), (i+1, j))
        elif char == 'J':
            # Up
            if can_go_up(i, j, map):
                graph.add_edge((i, j), (i-1, j))
            # Left
            if can_go_left(i, j, map):
                graph.add_edge((i, j), (i, j-1))
        elif char == 'L':
            # Up
            if can_go_up(i, j, map):
                graph.add_edge((i, j), (i-1, j))
            # Right
            if can_go_right(i, j, map):
                graph.add_edge((i, j), (i, j+1))
        elif char == 'F':
            # Down
            if can_go_down(i, j, map):
                graph.add_edge((i, j), (i+1, j))
            # Right
            if can_go_right(i, j, map):
                graph.add_edge((i, j), (i, j+1))
                
distance_map[start[0]][start[1]] = 0
for neighbor in graph.neighbors(start):
    distance = 0
    current = neighbor
    previous = start
    while current != start:
        distance += 1
        if distance_map[current[0]][current[1]] > distance:
            distance_map[current[0]][current[1]] = distance
        candidates = list(graph.neighbors(current))
        candidates.remove(previous)
        assert len(candidates) == 1
        previous = current
        current = candidates[0]

n_enclosed = 0
for i in range(len(map)):
    enclosed = False
    for j in range(len(map[0])):
        if distance_map[i][j] < sys.maxsize:
            if map[i][j] in "|JL" or (map[i][j]=="S" and s_is_vertical):
                enclosed = not enclosed
        else:
            n_enclosed += enclosed
        enclosed_map[i][j] = enclosed

print(n_enclosed)

# print_map(map)
# print_enclosed_map(enclosed_map)
# print(graph)
# print_loop(map, distance_map)
# print(max_distance)

# print_dist(dist)
# print(start)

# print(list(nx.cycles.simple_cycles(graph)))
# print(list(graph.edges))