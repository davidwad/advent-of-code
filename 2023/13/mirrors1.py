def is_line_of_reflection(idx: int, characters: list[str]) -> bool:
    if idx == len(characters) - 1:
        return False
    for i1, i2 in zip(range(idx, -1, -1), range(idx + 1, len(characters))):
        if characters[i1] != characters[i2]:
            return False
    return True


file = open('2023/13/input.txt', 'r')
lines = [line.strip() for line in file.readlines()]

sum = 0
rows: list[str] = []
for line_idx, line in enumerate(lines):
    if len(line) == 0 or line_idx == len(lines) - 1:
        n_rows = len(rows)
        n_cols = len(rows[0])
        columns: list[str] = [''] * n_cols
        for i in range(n_cols):
            for row in rows:
                columns[i] += row[i]
        reflections = []
        for idx in range(n_rows):
            if is_line_of_reflection(idx, rows):
                sum += (idx + 1) * 100
                reflections.append(('row', idx))
        for idx in range(n_cols):
            if is_line_of_reflection(idx, columns):
                sum += idx + 1
                reflections.append(('column', idx))
        assert len(reflections) == 1, f'{line_idx}: {reflections}'
        rows: list[str] = []
    else:
        rows.append(line)

print(sum)
