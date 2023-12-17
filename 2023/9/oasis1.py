def predict_sequence(sequence: list[int]) -> int:
    if all([k == 0 for k in sequence]):
        return 0
    diffed_sequence = [j-i for i, j in zip(sequence[:-1], sequence[1:])]
    return sequence[-1] + predict_sequence(diffed_sequence)


file = open('input.txt', 'r')
lines = [line.strip() for line in file.readlines()]

sum = 0
for line in lines:
    sequence = [int(s) for s in line.split(' ')]
    prediction = predict_sequence(sequence)
    sum += prediction

print(sum)
