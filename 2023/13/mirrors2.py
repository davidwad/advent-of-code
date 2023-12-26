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
                reflections.append(('row', idx))
        for idx in range(n_cols):
            if is_line_of_reflection(idx, columns):
                reflections.append(('column', idx))
        assert len(reflections) == 1, f'{line_idx}: {reflections}'
        for i in range(n_rows):
            for j in range(n_cols):
                rows_copy = list(rows)
                columns_copy = list(columns)
                c = rows_copy[i][j]
                row_list = list(rows_copy[i])
                column_list = list(columns_copy[j])
                if c == '.':
                    row_list[j] = '#'
                    column_list[i] = '#'
                else:
                    row_list[j] = '.'
                    column_list[i] = '.'
                rows_copy[i] = ''.join(row_list)
                columns_copy[j] = ''.join(column_list)
                for idx in range(n_rows):
                    if is_line_of_reflection(idx, rows_copy):
                        if ('row', idx) != reflections[0]:
                            new_reflection = ('row', idx)
                            break
                for idx in range(n_cols):
                    if is_line_of_reflection(idx, columns_copy):
                        if ('column', idx) != reflections[0]:
                            new_reflection = ('column', idx)
                            break
        if new_reflection[0] == 'row':
            sum += (new_reflection[1] + 1) * 100
        else:
            sum += new_reflection[1] + 1
        rows: list[str] = []
    else:
        rows.append(line)

print(sum)
