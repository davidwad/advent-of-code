import re


pattern_text = r'(\d [a-z]{3,5})'
pattern = re.compile(pattern_text)
max_counts = {'red': 12, 'green': 13, 'blue': 14}

sum = 0
file = open('input.txt', 'r')
for line in file.readlines():
    game_id = int(re.match(r'Game (?P<game_id>\d+)', line).groups()[0])
    matches = re.findall(r'(\d+ [a-z]{3,5})', line)

    possible = True
    for match in matches:
        count_str, color = re.match(r'(?P<count>[\d]{1,2}) (?P<color>[a-z]{3,5})', match).groups()
        count = int(count_str)

        if count > max_counts[color]:
            possible = False
            break
    if possible:
        sum += game_id

print(sum)
