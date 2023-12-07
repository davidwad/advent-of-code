import re


def calculate_improved_rank(rank: int, n_jacks: int):
    if n_jacks == 0:
        return rank
    # High card
    if rank == 1:
        # Pair
        if n_jacks == 1:
            return 2
        else:
            raise ValueError
    # Pair
    elif rank == 2:
        # Three of a kind
        if n_jacks == 1:
            return 4
        # Three of a kind
        elif n_jacks == 2:
            return 4
        else:
            raise ValueError
    # Two pair
    elif rank == 3:
        # Full house
        if n_jacks == 1:
            return 5
        # Four of a kind
        elif n_jacks == 2:
            return 6
        else:
            raise ValueError
    # Three of a kind
    elif rank == 4:
        # Four of a kind
        if n_jacks == 1:
            return 6
        # Four of a kind
        elif n_jacks == 3:
            return 6
        else:
            raise ValueError
    # Full house or better
    else:
        return 7


class Hand:
    def __init__(self, cards: str, bid: int, char_map: dict) -> None:
        for key, value in char_map.items():
            cards = cards.replace(key, value)
        self.cards = cards
        self.bid = bid

    def calculate_score(self) -> int:
        cards = ''.join(sorted(self.cards))
        n_jacks = sum([1 for c in cards if c == '0'])
        if re.match(r'(.)\1{4}.*', self.cards):
            return calculate_improved_rank(7, n_jacks)
        elif re.match(r'.*(.)\1{3}.*', cards):
            return calculate_improved_rank(6, n_jacks)
        elif re.match(r'((.)\2{2}(.)\3{1}|(.)\4{1}(.)\5{2})', cards):
            return calculate_improved_rank(5, n_jacks)
        elif re.match(r'.*(.)\1{2}.*', cards):
            return calculate_improved_rank(4, n_jacks)
        elif re.match(r'.*(.)\1{1}.*(.)\2{1}.*', cards):
            return calculate_improved_rank(3, n_jacks)
        elif re.match(r'.*(.)\1{1}.*', cards):
            return calculate_improved_rank(2, n_jacks)
        else:
            return calculate_improved_rank(1, n_jacks)


char_map = {'A': 'Z', 'K': 'Y', 'Q': 'X', 'J': '0', 'T': 'U'}

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
