file = open('input.txt', 'r')
lines = [line.strip() for line in file.readlines()]

copies = {i: 1 for i in range(len(lines))}
sum = 0

for idx, line in enumerate(lines):
    split = line.split('|')
    left = split[0].split(':')
    winners = left[1].split(' ')
    winners = [int(n.strip()) for n in winners if n != '']
    mine = split[1].split(' ')
    mine = [int(n.strip()) for n in mine if n != '']

    n_winners = 0
    for m in mine:
        if m in winners:
            n_winners += 1

    for i in range(n_winners):
        copies[idx + i + 1] += copies[idx]

for _, value in copies.items():
    sum += value

print(sum)
