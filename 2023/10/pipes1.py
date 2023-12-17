# TODO: Seems like graph isnt constructed correctly. Not enough edges?
import sys
import networkx as nx


def can_go_left(i: int, j: int, map: list[list[str]]) -> bool:
    return j > 0 and (map[i][j-1] == '-' or map[i][j-1] == 'F' or map[i][j-1] == 'L')

def can_go_right(i: int, j: int, map: list[list[str]]) -> bool:
    return j < len(map[0]) - 1 and (map[i][j+1] == '-' or map[i][j+1] == '7' or map[i][j+1] == 'J')

def can_go_down(i: int, j: int, map: list[list[str]]) -> bool:
    return i < len(map) - 1 and (map[i+1][j] == '|' or map[i+1][j] == 'L' or map[i+1][j] == 'J')

def can_go_up(i: int, j: int, map: list[list[str]]) -> bool:
    return i > 0 and (map[i-1][j] == '|' or map[i-1][j] == '7' or map[i-1][j] == 'F')


def print_dist(dist: list[list[int]]):
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


file = open('example_input_simple.txt', 'r')
lines = [line.strip() for line in file.readlines()]

n_rows = len(lines)
n_cols = len(lines[0])

map = []
dist = []
graph = nx.Graph()
for i, line in enumerate(lines):
    chars = []
    dist_row = []
    for j, char in enumerate(line):
        graph.add_node((i, j))
        chars.append(char)
        dist_row.append(sys.maxsize)
    map.append(chars)
    dist.append(dist_row)

sum = 0
for i, line in enumerate(lines):

    for j, char in enumerate(line):
        if char == 'S':
            start = (i, j)
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

print(graph)

print_map(map)
print_dist(dist)
print(start)