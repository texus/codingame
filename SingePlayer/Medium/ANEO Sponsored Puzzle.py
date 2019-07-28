import sys
import math

lights = []
speed = int(input())
light_count = int(input())
for i in range(light_count):
    distance, duration = [int(j) for j in input().split()]
    lights.append((distance, duration))

while speed > 0:
    speedMps = speed / 3.6
    speedFound = True
    for light in lights:
        timeToLight = round(light[0] / speedMps, 2)
        if (timeToLight // light[1]) % 2 != 0:
            speedFound = False
            break

    if speedFound:
        break
    else:
        speed -= 1

print(speed)
