import sys
import math

grid = []

w, h = [int(i) for i in raw_input().split()]
for i in xrange(h):
    grid.append(raw_input())

def addMove(moves, pos):
    if grid[pos[1]][pos[0]] != '#':
        moves.append(pos)

def getLegalMoves(pos):
    moves = []
    if pos[0] >= 2:
        if pos[1] >= 1:
            addMove(moves, (pos[0]-2, pos[1]-1))
        if pos[1] < h-1:
            addMove(moves, (pos[0]-2, pos[1]+1))
    if pos[0] < w-2:
        if pos[1] >= 1:
            addMove(moves, (pos[0]+2, pos[1]-1))
        if pos[1] < h-1:
            addMove(moves, (pos[0]+2, pos[1]+1))
    if pos[1] >= 2:
        if pos[0] >= 1:
            addMove(moves, (pos[0]-1, pos[1]-2))
        if pos[0] < w-1:
            addMove(moves, (pos[0]+1, pos[1]-2))
    if pos[1] < h-2:
        if pos[0] >= 1:
            addMove(moves, (pos[0]-1, pos[1]+2))
        if pos[0] < w-1:
            addMove(moves, (pos[0]+1, pos[1]+2))
    return moves

startPos = (0,0)
for r in range(h):
    for c in range(w):
        if grid[r][c] == 'B':
            startPos = (c,r)

visited = []
fringe = [] # queue
fringe.append((startPos, 0))
while len(fringe) > 0:
    node = fringe.pop(0)

    if node[0] in visited:
        continue

    visited += [node[0]]

    if grid[node[0][1]][node[0][0]] == 'E':
        print node[1]
        quit()
    else:
        successors = getLegalMoves(node[0])
        for successor in successors:
            fringe.append((successor, node[1]+1))

print "Impossible"
