import sys

x = 0
y = 0
direction = (1,0)
stringMode = False
skipChar = False
grid = []
stack = []

n = int(input())
for i in range(n):
    line = input()
    grid.append([])
    for c in line:
        grid[-1].append(c)

    # All lines must have equal length
    maxLineLen = len(max(grid, key=len))
    for row in grid:
        for k in range(maxLineLen - len(row)):
            row.append(' ')

cell = grid[y][x]
while True:
    if skipChar:
        skipChar = False
    elif stringMode:
        if cell != '"':
            stack.append(ord(cell))
        else:
            stringMode = False
    elif cell >= '0' and cell <= '9':
        stack.append(int(cell))
    elif cell == '+':
        val1 = stack.pop()
        val2 = stack.pop()
        stack.append((val1 + val2) % 256)
    elif cell == '-':
        val1 = stack.pop()
        val2 = stack.pop()
        stack.append((val2 - val1) % 256)
    elif cell == '*':
        val1 = stack.pop()
        val2 = stack.pop()
        stack.append((val1 * val2) % 256)
    elif cell == '>':
        direction = (1,0)
    elif cell == '<':
        direction = (-1,0)
    elif cell == 'v':
        direction = (0,1)
    elif cell == '^':
        direction = (0,-1)
    elif cell == 'S':
        skipChar = True
    elif cell == '"':
        stringMode = True
    elif cell == 'I':
        print(stack.pop(), end='')
    elif cell == 'C':
        print(chr(stack.pop()), end='')
    elif cell == 'P':
        stack.pop()
    elif cell == 'X':
        val1 = stack.pop()
        val2 = stack.pop()
        stack.append(val1)
        stack.append(val2)
    elif cell == 'D':
        val = stack.pop()
        stack.append(val)
        stack.append(val)
    elif cell == '_':
        if stack.pop() == 0:
            direction = (1,0)
        else:
            direction = (-1,0)
    elif cell == '|':
        if stack.pop() == 0:
            direction = (0,1)
        else:
            direction = (0,-1)
    elif cell == 'E':
        break

    x += direction[0]
    y += direction[1]
    cell = grid[y][x]
