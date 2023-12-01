sum = 0
with open('input.txt', 'r') as file:
    for line in file:
        chars = []
        for idx, char in enumerate(line):
            if char.isnumeric():
                chars.append(char)
            elif idx < len(line) - 3 and line[idx:idx+3] == 'one':
                chars.append('1')
            elif idx < len(line) - 3 and line[idx:idx+3] == 'two':
                chars.append('2')
            elif idx < len(line) - 5 and line[idx:idx+5] == 'three':
                chars.append('3')
            elif idx < len(line) - 4 and line[idx:idx+4] == 'four':
                chars.append('4')
            elif idx < len(line) - 4 and line[idx:idx+4] == 'five':
                chars.append('5')
            elif idx < len(line) - 3 and line[idx:idx+3] == 'six':
                chars.append('6')
            elif idx < len(line) - 5 and line[idx:idx+5] == 'seven':
                chars.append('7')
            elif idx < len(line) - 5 and line[idx:idx+5] == 'eight':
                chars.append('8')
            elif idx < len(line) - 4 and line[idx:idx+4] == 'nine':
                chars.append('9')
        chars = chars[0] + chars[-1]
        sum += int(chars)
    print(sum)
