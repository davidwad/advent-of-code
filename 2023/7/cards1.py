import re


class Hand:
    def __init__(self, cards: str, bid: int, char_map: dict) -> None:
        for key, value in char_map.items():
            cards = cards.replace(key, value)
        self.cards = cards
        self.bid = bid

    def calculate_score(self) -> int:
        cards = ''.join(sorted(self.cards))
        if re.match(r'(.)\1{4}.*', self.cards):
            return 7
        elif re.match(r'.*(.)\1{3}.*', cards):
            return 6
        elif re.match(r'((.)\2{2}(.)\3{1}|(.)\4{1}(.)\5{2})', cards):
            return 5
        elif re.match(r'.*(.)\1{2}.*', cards):
            return 4
        elif re.match(r'.*(.)\1{1}.*(.)\2{1}.*', cards):
            return 3
        elif re.match(r'.*(.)\1{1}.*', cards):
            return 2
        else:
            return 1


char_map = {'A': 'Z', 'K': 'Y', 'Q': 'X', 'J': 'V', 'T': 'U'}

file = open('input.txt', 'r')
lines = [line.strip() for line in file.readlines()]

groups = {i: [] for i in range(1, 8)}
for line in lines:
    split = line.split(' ')
    hand = Hand(split[0], int(split[1]), char_map)
    groups[hand.calculate_score()].append(hand)

hands = []
for i in range(1, 8):
    group_hands = groups[i]
    s = sorted(group_hands, key=lambda hand: hand.cards)
    hands.extend(s)

sum = 0
for i, hand in enumerate(hands):
    sum += (i + 1) * hand.bid

print(sum)
