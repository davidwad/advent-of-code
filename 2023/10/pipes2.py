# TODO: The functions can_squeeze_x only work if you start on ground, but not while you are squeezing between pipes.
# Need different logic for when you are on a tile in the main loop

import networkx as nx


def can_escape(i: int, j: int , loop_edges: list[tuple[tuple[int,int]]], visited: list[list[bool]]) -> bool:
    # Have we visited before?
    if visited[i][j]:
        return False
    visited[i][j] = True
    # Are we on the edge of the map?
    if i == 0 or i == len(visited) - 1 or j == 0 or j == len(visited[0]) - 1:
        return True
    can_escape_left = can_squeeze_left(i, j, loop_edges) and can_escape(i, j - 1, loop_edges, visited)
    can_escape_right = can_squeeze_right(i, j, loop_edges) and can_escape(i, j + 1, loop_edges, visited)
    can_escape_down = can_squeeze_down(i, j, loop_edges) and can_escape(i + 1, j, loop_edges, visited)
    can_escape_up = can_squeeze_up(i, j, loop_edges) and can_escape(i - 1, j, loop_edges, visited)
    return can_escape_left or can_escape_right or can_escape_down or can_escape_up

def can_squeeze_left(i: int, j: int, loop_edges: list[tuple[tuple[int,int]]]) -> bool:
    up_left = (i - 1, j - 1)
    left = (i, j - 1)
    down_left = (i + 1, j - 1)
    return not ((up_left, left) in loop_edges and (left, down_left) in loop_edges)

def can_squeeze_right(i: int, j: int, loop_edges: list[tuple[tuple[int,int]]]) -> bool:
    up_right = (i - 1, j + 1)
    right = (i, j + 1)
    down_right = (i + 1, j + 1)
    return not ((up_right, right) in loop_edges and (right, down_right) in loop_edges)

def can_squeeze_down(i: int, j: int, loop_edges: list[tuple[tuple[int,int]]]) -> bool:
    down_left = (i + 1, j - 1)
    down = (i + 1, j)
    down_right = (i + 1, j + 1)
    return not ((down_left, down) in loop_edges and (down, down_right) in loop_edges)

def can_squeeze_up(i: int, j: int, loop_edges: list[tuple[tuple[int,int]]]) -> bool:
    up_left = (i - 1, j - 1)
    up = (i - 1, j)
    up_right = (i - 1, j + 1)
    return not ((up_left, up) in loop_edges and (up, up_right) in loop_edges)


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


file = open('example_input_2_simple.txt', 'r')
lines = [line.strip() for line in file.readlines()]

n_rows = len(lines)
n_cols = len(lines[0])

map = []
enclosed_map = []
graph = nx.Graph()
for i, line in enumerate(lines):
    chars = []
    enclosed_row = []
    for j, char in enumerate(line):
        if char != '.':
            graph.add_node((i, j))
        chars.append(char)
        enclosed_row.append(None)
    map.append(chars)
    enclosed_map.append(enclosed_row)

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

for i in range(len(map)):
    for j in range(len(map[0])):
        visited = []
        for _ in range(len(map)):
            visited_row = []
            for _ in range(len(map[0])):
                visited_row.append(False)
            visited.append(visited_row)
        if (i, j) == (6, 2):
            a = 0
        if not graph.has_node((i, j)):
            enclosed_map[i][j] = not can_escape(i, j, list(graph.edges), visited)

n_enclosed = 0
for row in enclosed_map:
    for square in row:
        if square == True:
            n_enclosed += 1

print(n_enclosed)

# print_map(map)
print_enclosed_map(enclosed_map)
# print(graph)
# print_loop(map, distance_map)
# print(max_distance)

# print_dist(dist)
# print(start)

# print(list(nx.cycles.simple_cycles(graph)))
print(list(graph.edges))