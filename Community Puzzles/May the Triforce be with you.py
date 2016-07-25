n = int(input())

piramidWidth = 1 + 2*(n-1)
totalWidth = 2*piramidWidth + 1

print('.' + ' '*(2*(n-1)) + '*')
for i in range(1, n):
    starsInRow = 1 + 2*i
    spacesBeforeFirstPiramid = (totalWidth - starsInRow) // 2
    print(' '*spacesBeforeFirstPiramid + '*'*starsInRow)

for i in range(n):
    starsInRow = 1 + 2*i
    spacesBeforeFirstPiramid = (piramidWidth - starsInRow) // 2
    spacesBetweenPiramids = 2*spacesBeforeFirstPiramid + 1
    print(' '*spacesBeforeFirstPiramid + '*'*starsInRow + ' '*spacesBetweenPiramids + '*'*starsInRow)
