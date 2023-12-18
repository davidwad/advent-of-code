import sys
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
    
    return False

# def can_escape(origin: tuple[int], destination: tuple[int], loop_edges: list[tuple[tuple[int,int]]], visited: list[list[bool]]) -> bool:
#     i_o = origin[0]
#     j_o = origin[1]
#     i_d = destination[0]
#     j_d = destination[1]
#     # Have we visited origin before?
#     if visited[i_o][j_o]:
#         return False
#     # Is origin on the edge of the map?
#     if i_o == 0 or i_o == len(visited) - 1 or j_o == 0 or j_o == len(visited[0]) - 1:
#         return True
#     can_escape_left = can_squeeze_left(i_o, j_o - 1)
#     return False

def can_squeeze_left(i: int, j: int, loop_edges: list[tuple[tuple[int,int]]]) -> bool:
    up_left = (i - 1, j - 1)
    left = (i, j - 1)
    down_left = (i + 1, j - 1)
    return not ((up_left, left) in loop_edges and (left, down_left) in loop_edges)

def can_squeeze_right(i: int, j: int, loop_edges: list[tuple[tuple[int,int]]]) -> bool:
    return j < len(map[0]) - 1 and (map[i][j+1] == '-' or map[i][j+1] == '7' or map[i][j+1] == 'J' or map[i][j+1] == 'S')

def can_squeeze_down(i: int, j: int, loop_edges: list[tuple[tuple[int,int]]]) -> bool:
    return i < len(map) - 1 and (map[i+1][j] == '|' or map[i+1][j] == 'L' or map[i+1][j] == 'J' or map[i+1][j] == 'S')

def can_squeeze_up(i: int, j: int, loop_edges: list[tuple[tuple[int,int]]]) -> bool:
    return i > 0 and (map[i-1][j] == '|' or map[i-1][j] == '7' or map[i-1][j] == 'F' or map[i-1][j] == 'S')


def can_go_left(i: int, j: int, map: list[list[str]]) -> bool:
    return j > 0 and (map[i][j-1] == '-' or map[i][j-1] == 'F' or map[i][j-1] == 'L' or map[i][j-1] == 'S')

def can_go_right(i: int, j: int, map: list[list[str]]) -> bool:
    return j < len(map[0]) - 1 and (map[i][j+1] == '-' or map[i][j+1] == '7' or map[i][j+1] == 'J' or map[i][j+1] == 'S')

def can_go_down(i: int, j: int, map: list[list[str]]) -> bool:
    return i < len(map) - 1 and (map[i+1][j] == '|' or map[i+1][j] == 'L' or map[i+1][j] == 'J' or map[i+1][j] == 'S')

def can_go_up(i: int, j: int, map: list[list[str]]) -> bool:
    return i > 0 and (map[i-1][j] == '|' or map[i-1][j] == '7' or map[i-1][j] == 'F' or map[i-1][j] == 'S')

def print_distance_map(dist: list[list[int]]):
    for row in dist:
        row_str = ''
        for d in row:
            if d > 9:
                row_str = row_str + '9'
            else:
                row_str = row_str + str(d)
        print(row_str)

def print_map(map: list[list[str]]):
    for row in map:
        print(''.join(row))

def print_loop(map: list[list[str]], distance_map: list[list[int]]):
    for row in map:
        print(''.join(row).replace())
    # for i, row in enumerate(map):
    #     for j, char in enumerate(row):
    #         if distance_map[i][j] == sys.maxsize:
    #             print(char)
    #         else:
    #             # print("\033[91m {}\033[00m" .format(char))
    #             print('X')


file = open('example_input_simple.txt', 'r')
lines = [line.strip() for line in file.readlines()]

n_rows = len(lines)
n_cols = len(lines[0])

map = []
distance_map = []
graph = nx.Graph()
for i, line in enumerate(lines):
    chars = []
    distance_row = []
    for j, char in enumerate(line):
        if char != '.':
            graph.add_node((i, j))
        chars.append(char)
        distance_row.append(sys.maxsize)
    map.append(chars)
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

max_distance = -1
for row in distance_map:
    for d in row:
        if d != sys.maxsize and d > max_distance:
            max_distance = d

# print_map(map)
# print_distance_map(distance_map)
# print(graph)
# print_loop(map, distance_map)
print(max_distance)

# print_dist(dist)
# print(start)

# print(list(nx.cycles.simple_cycles(graph)))
print(list(graph.edges))