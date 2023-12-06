file = open('input.txt', 'r')
lines = [line.strip() for line in file.readlines()]

times = lines[0].split(':')[1]
times = [int(s.strip()) for s in times.split(' ') if s.strip() != '']

distances = lines[1].split(':')[1]
distances = [int(s.strip()) for s in distances.split(' ') if s.strip() != '']

print(times)
print(distances)

prod = 1
for time, target_distance in zip(times, distances):
    possibilities = 0
    for pushing_duration in range(1, time):
        speed = pushing_duration
        moving_duration = time - pushing_duration
        distance = moving_duration * speed
        if distance > target_distance:
            possibilities += 1
    prod = prod * possibilities

print(prod)