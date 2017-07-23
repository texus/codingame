import sys
import math

u, v = [int(i) for i in input().split()]

pos = (0,u)
dir = (1,-1)

length = 0

while True:
    if dir == (1,-1):
        if v - pos[0] < pos[1]:
            dist = v - pos[0]
            pos = (pos[0] + dist, pos[1] - dist)
            dir = (-1,-1)
        elif v - pos[0] > pos[1]:
            dist = pos[1]
            pos = (pos[0] + dist, pos[1] - dist)
            dir = (1,1)
        else:
            length += pos[1]
            print('B ' + str(length))
            break
    elif dir == (-1,-1):
        if pos[0] < pos[1]:
            dist = pos[0]
            pos = (pos[0] - dist, pos[1] - dist)
            dir = (1,-1)
        elif pos[0] > pos[1]:
            dist = pos[1]
            pos = (pos[0] - dist, pos[1] - dist)
            dir = (-1,1)
        else:
            length += pos[1]
            print('A ' + str(length))
            break
    elif dir == (1,1):
        if v - pos[0] < u - pos[1]:
            dist = v - pos[0]
            pos = (pos[0] + dist, pos[1] + dist)
            dir = (-1,1)
        elif v - pos[0] > u - pos[1]:
            dist = u - pos[1]
            pos = (pos[0] + dist, pos[1] + dist)
            dir = (1,-1)
        else:
            length += u - pos[1]
            print('C ' + str(length))
            break
    elif dir == (-1,1):
        if pos[0] < u - pos[1]:
            dist = pos[0]
            pos = (pos[0] - dist, pos[1] + dist)
            dir = (1,1)
        elif pos[0] > u - pos[1]:
            dist = u - pos[1]
            pos = (pos[0] - dist, pos[1] + dist)
            dir = (-1,-1)
        else:
            length += pos[0]
            print('S ' + str(length))
            break

    length += dist
