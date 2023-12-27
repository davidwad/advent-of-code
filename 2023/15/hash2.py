class Lens:
    def __init__(self, label: str, focal_length: int) -> None:
        self.label = label
        self.focal_length = focal_length
    
    def __eq__(self, other: object) -> bool:
        return isinstance(other, Lens) and self.label == other.label

    def __str__(self) -> str:
        return f'{self.label} {self.focal_length}'


def hash(label: str) -> int:
    value = 0
    for char in label:
        value += ord(char)
        value = value * 17
        value = value % 256
    return value


file = open('2023/15/input.txt', 'r')
line = file.readlines()[0]
steps = line.strip().split(',')

boxes: dict[int, list[Lens]] = {}
for i in range(256):
    boxes[i] = []
for step in steps:
    if '=' in step:
        label = step[:-2]
        focal_length = int(step[-1])
        lens = Lens(label, focal_length)
        current_lenses = boxes.get((hash(label)))
        if lens in current_lenses:
            current_lenses[current_lenses.index(lens)] = lens
        else:
            current_lenses.append(lens) 
    else:
        label = step[:-1]
        current_lenses = boxes.get((hash(label)))
        lens = Lens(label, 0)
        if lens in current_lenses:
            current_lenses.remove(Lens(label, 0))

sum = 0
for box in range(256):
    lenses = boxes[box]
    for idx, lens in enumerate(lenses):
        sum += (box + 1) * (idx + 1) * lens.focal_length

print(sum)
