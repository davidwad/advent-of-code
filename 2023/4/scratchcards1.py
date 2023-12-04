file = open('input.txt', 'r')
lines = [line.strip() for line in file.readlines()]
sum = 0

for line in lines:
    split = line.split('|')
    left = split[0].split(':')
    winners = left[1].split(' ')
    winners = [int(n.strip()) for n in winners if n != '']
    mine = split[1].split(' ')
    mine = [int(n.strip()) for n in mine if n != '']
    prod = 0

    for m in mine:
        if m in winners:
            if prod == 0:
                prod = 1
            else:
                prod = prod * 2
    sum += prod

print(sum)
