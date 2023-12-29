def move(origin: tuple[int, int], destination: tuple[int, int], map: list[list[str]], visited: list[list[list[str]]]):
    i_o = origin[0]
    j_o = origin[1]
    i_d = destination[0]
    j_d = destination[1]

    if i_d < 0 or i_d >= len(map) or j_d < 0 or j_d >= len(map[0]):
        return

    c = map[i_d][j_d]

    # Up
    if i_o > i_d:
        if 'u' in visited[i_d][j_d]:
            return
        visited[i_d][j_d].append('u')
        while c != '-' and c != '/' and c != '\\':
            if i_d == 0:
                return
            else:
                i_d -= 1
                if 'u' in visited[i_d][j_d]:
                    return
                visited[i_d][j_d].append('u')
                c = map[i_d][j_d]
        if c == '-':
            move((i_d, j_d), (i_d, j_d - 1), map, visited)
            move((i_d, j_d), (i_d, j_d + 1), map, visited)
        elif c == '/':
            move((i_d, j_d), (i_d, j_d + 1), map, visited)
        elif c == '\\':
            move((i_d, j_d), (i_d, j_d - 1), map, visited)
        else:
            move((i_d, j_d), (i_d, j_d), map, visited)
    # Right
    elif j_d > j_o:
        if 'r' in visited[i_d][j_d]:
            return
        visited[i_d][j_d].append('r')
        while c != '|' and c != '/' and c != '\\':
            if j_d == len(map[0]) - 1:
                return
            else:
                j_d += 1
                if 'r' in visited[i_d][j_d]:
                    return
                visited[i_d][j_d].append('r')
                c = map[i_d][j_d]
        if c == '|':
            move((i_d, j_d), (i_d - 1, j_d), map, visited)
            move((i_d, j_d), (i_d + 1, j_d), map, visited)
        elif c == '/':
            move((i_d, j_d), (i_d - 1, j_d), map, visited)
        elif c == '\\':
            move((i_d, j_d), (i_d + 1, j_d), map, visited)
        else:
            move((i_d, j_d), (i_d, j_d + 1), map, visited)
    # Down
    elif i_d > i_o:
        if 'd' in visited[i_d][j_d]:
            return
        visited[i_d][j_d].append('d')
        while c != '-' and c != '/' and c != '\\':
            if i_d == len(map) - 1:
                return
            else:
                i_d += 1
                if 'd' in visited[i_d][j_d]:
                    return
                visited[i_d][j_d].append('d')
                c = map[i_d][j_d]
        if c == '-':
            move((i_d, j_d), (i_d, j_d - 1), map, visited)
            move((i_d, j_d), (i_d, j_d + 1), map, visited)
        elif c == '/':
            move((i_d, j_d), (i_d, j_d - 1), map, visited)
        elif c == '\\':
            move((i_d, j_d), (i_d, j_d + 1), map, visited)
        else:
            move((i_d, j_d), (i_d + 1, j_d), map, visited)
    # Left
    elif j_o > j_d:
        if 'l' in visited[i_d][j_d]:
            return
        visited[i_d][j_d].append('l')
        while c != '|' and c != '/' and c != '\\':
            if j_d == 0:
                return
            else:
                j_d -= 1
                if 'l' in visited[i_d][j_d]:
                    return
                visited[i_d][j_d].append('l')
                c = map[i_d][j_d]
        if c == '|':
            move((i_d, j_d), (i_d - 1, j_d), map, visited)
            move((i_d, j_d), (i_d + 1, j_d), map, visited)
        elif c == '/':
            move((i_d, j_d), (i_d + 1, j_d), map, visited)
        elif c == '\\':
            move((i_d, j_d), (i_d - 1, j_d), map, visited)
        else:
            move((i_d, j_d), (i_d, j_d - 1), map, visited)


def count_energized(visited: list[list[list[str]]]):
    n_energized = 0
    for row in visited:
        for l in row:
            if l:
                n_energized += 1
    return n_energized


def print_visited(visited: list[list[str]]):
    for row in visited:
        row_str = ''
        for r in row:
            if r:
                row_str += '#'
            else:
                row_str += '.'
        print(row_str)


file = open('2023/16/input.txt', 'r')
lines: list[list[str]] = [list(line.strip()) for line in file.readlines()]
n_rows = len(lines)
n_cols = len(lines[0])

visited: list[list[list[str]]] = [[[] for _ in range(n_cols)] for _ in range(n_rows)]
energies = []

# Top row
for j in range(len(lines[0])):
    move((-1, j), (0, j), lines, visited)
    energies.append(count_energized(visited))
    visited: list[list[list[str]]] = [[[] for _ in range(n_cols)] for _ in range(n_rows)]

# Right column
for i in range(len(lines)):
    move((i, len(lines[0])), (i, len(lines[0]) - 1), lines, visited)
    energies.append(count_energized(visited))
    visited: list[list[list[str]]] = [[[] for _ in range(n_cols)] for _ in range(n_rows)]

# Bottom row
for j in range(len(lines[0])):
    move((len(lines), j), (len(lines) - 1, j), lines, visited)
    energies.append(count_energized(visited))
    visited: list[list[list[str]]] = [[[] for _ in range(n_cols)] for _ in range(n_rows)]

# Left column
for i in range(len(lines)):
    move((i, -1), (i, 0), lines, visited)
    energies.append(count_energized(visited))
    visited: list[list[list[str]]] = [[[] for _ in range(n_cols)] for _ in range(n_rows)]

print(max(energies))