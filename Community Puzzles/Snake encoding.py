import sys
square = []

n = int(input())
x = int(input())

for i in range(n):
    line = input()
    square.append([])
    for c in line:
        square[-1].append(c)

def encode():
    x = 0
    y = n-1
    up = True
    tmp = square[y][x]

    while True:
        if up:
            if y == 0:
                if x+1 == n:
                    square[n-1][0] = tmp
                    return
                else:
                    tmp,square[y][x+1] = square[y][x+1],tmp
                    x += 1
                    up = False
            else:
                tmp,square[y-1][x] = square[y-1][x],tmp
                y -= 1
        else:
            if y == n-1:
                if x+1 == n:
                    square[n-1][0] = tmp
                    return
                else:
                    tmp,square[y][x+1] = square[y][x+1],tmp
                    x += 1
                    up = True
            else:
                tmp,square[y+1][x] = square[y+1][x],tmp
                y += 1

    


for i in range(x):
    encode()

for r in range(n):
    for c in range(n):
        print(square[r][c], end='')
    print('')

