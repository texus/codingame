import math
import heapq

# nb_floors: number of floors
# width: width of the area
# nb_rounds: maximum number of rounds
# exit_floor: floor on which the exit is found
# exit_pos: position of the exit on its floor
# nb_total_clones: number of generated clones
# nb_additional_elevators: number of additional elevators that you can build
# nb_elevators: number of elevators
nb_floors, width, nb_rounds, exit_floor, exit_pos, nb_total_clones, nb_additional_elevators, nb_elevators = [int(i) for i in input().split()]
elevators = set()
for i in range(nb_elevators):
    # elevator_floor: floor on which this elevator is found
    # elevator_pos: position of the elevator on its floor
    elevator_floor, elevator_pos = [int(j) for j in input().split()]
    elevators.add((elevator_floor, elevator_pos))

def calcHeuristicsMap():
    # We create a 3-dimensional heuristics map.
    # Two dimensions are for the grid, and on dimension for the remaining elevators.
    # Each position thus has a different heuristic depending on how many elevators are yet to be placed.
    heuristics = [[[math.inf for z in range(nb_additional_elevators+1)] for x in range(width)] for y in range(nb_floors)]

    # The exit has a zero cost
    for i in range(nb_additional_elevators+1):
        heuristics[exit_floor][exit_pos][i] = 0

    # Calculate the heuristic cost to the exit by going down row by row
    for y in range(exit_floor, -1, -1):
        # Process every position on this row
        posToProcessInRow = set(range(0,width))
        while posToProcessInRow:
            x = posToProcessInRow.pop()
            valueUpdated = False

            if (y,x) not in elevators:
                # Compare our cost with the left neightbor
                if x > 0:
                    for z in range(nb_additional_elevators+1):
                        if heuristics[y][x][z] > heuristics[y][x-1][z] + 1:
                            heuristics[y][x][z] = heuristics[y][x-1][z] + 1
                            valueUpdated = True

                # Compare our cost with the right neighbor
                if x+1 < width:
                    for z in range(nb_additional_elevators+1):
                        if heuristics[y][x][z] > heuristics[y][x+1][z] + 1:
                            heuristics[y][x][z] = heuristics[y][x+1][z] + 1
                            valueUpdated = True

            # Cost with more remaining elevators left to be placed can never be higher
            # than reaching the same position with less elevators left.
            for z in range(1, nb_additional_elevators+1):
                if heuristics[y][x][z] > heuristics[y][x][z-1]:
                    heuristics[y][x][z] = heuristics[y][x][z-1]
                    valueUpdated = True

            # If we updated our cost then we also need to recheck our neighbors
            if valueUpdated:
                if x > 0:
                    posToProcessInRow.add(x-1)
                if x+1 < width:
                    posToProcessInRow.add(x+1)

        # Now that we have processed the row, we will copy the value to the row
        # below it. All costs are increased by one, but if there is no elevator
        # then we copy our values to a different z value as we needed to build
        # an elevator on the row below us in order to make this transition.
        if y > 0:
            for x in range(width):
                if (y-1, x) in elevators:
                    for z in range(nb_additional_elevators+1):
                        heuristics[y-1][x][z] = heuristics[y][x][z] + 1
                else:
                    for z in range(1, nb_additional_elevators+1):
                        heuristics[y-1][x][z] = heuristics[y][x][z-1] + 1

    return heuristics


def findShortestPath(cloneFloor, clonePos, initialMovingLeft, initialRemainingElevators):
    heuristics = calcHeuristicsMap()

    costs = [[[math.inf, math.inf] for x in range(width)] for y in range(nb_floors)]
    parents = {}

    statesToProcess = []
    heapq.heappush(statesToProcess, (0, (cloneFloor, clonePos, initialMovingLeft, initialRemainingElevators)))

    while statesToProcess:
        cost, state = heapq.heappop(statesToProcess)
        floor, pos, movingLeft, nrRemainingElevators = state
        if floor == exit_floor and pos == exit_pos:
            reversedPath = [(floor, pos, movingLeft)]
            while reversedPath[-1] != (cloneFloor, clonePos, initialMovingLeft):
                reversedPath.append(parents[reversedPath[-1]])
            return list(reversed(reversedPath))

        posContainsElevator = (floor, pos) in elevators
        neighborStates = []

        if pos > 0 and not posContainsElevator:
            if movingLeft:
                costLeft = heuristics[floor][pos-1][nrRemainingElevators]
                neighborStates.append((1, costLeft, floor, pos-1, True, nrRemainingElevators))
            else:
                costSwitchDir = heuristics[floor][pos][nrRemainingElevators]
                neighborStates.append((3, costSwitchDir, floor, pos, True, nrRemainingElevators))

        if pos+1 < width and not posContainsElevator:
            if movingLeft:
                costSwitchDir = heuristics[floor][pos][nrRemainingElevators]
                neighborStates.append((3, costSwitchDir, floor, pos, False, nrRemainingElevators))
            else:
                costRight = heuristics[floor][pos+1][nrRemainingElevators]
                neighborStates.append((1, costRight, floor, pos+1, False, nrRemainingElevators))

        if floor+1 < nb_floors:
            if posContainsElevator:
                costUp = heuristics[floor+1][pos][nrRemainingElevators]
                neighborStates.append((1, costUp, floor+1, pos, movingLeft, nrRemainingElevators))
            elif nrRemainingElevators > 0:
                costUp = heuristics[floor+1][pos][nrRemainingElevators-1]
                neighborStates.append((1, costUp, floor+1, pos, movingLeft, nrRemainingElevators-1))

        for neighborState in neighborStates:
            moveCost, heuristicCost, newFloor, newPos, newMovingLeft, newNrRemainingElevators = neighborState
            if cost == math.inf:
                continue

            newCost = cost + moveCost
            if (newFloor, newPos, newMovingLeft) not in parents or newCost + heuristicCost < costs[newFloor][newPos][newMovingLeft]:
                costs[newFloor][newPos][newMovingLeft] = newCost + heuristicCost
                parents[(newFloor, newPos, newMovingLeft)] = (floor, pos, movingLeft)
                heapq.heappush(statesToProcess, (newCost, (newFloor, newPos, newMovingLeft, newNrRemainingElevators)))

    # If we reach here then we didn't find a path. Which shouldn't be possible.
    assert(False)


nrRemainingElevators = nb_additional_elevators
blockedPositions = set()
firstIteration = True
pathToFollow = []

# game loop
while True:
    inputs = input().split()
    clone_floor = int(inputs[0])  # floor of the leading clone
    clone_pos = int(inputs[1])  # position of the leading clone on its floor
    direction = inputs[2]  # direction of the leading clone: LEFT or RIGHT

    if clone_floor == -1 and clone_pos == -1:
        print('WAIT')
        continue

    if clone_floor == exit_floor and clone_pos == exit_pos:
        print('WAIT')
        continue

    if (clone_floor, clone_pos) in elevators or (clone_floor, clone_pos) in blockedPositions:
        print('WAIT')
        continue

    # Calculate the entire path at the first iteration
    if firstIteration:
        pathToFollow = findShortestPath(clone_floor, clone_pos, direction == 'LEFT', nrRemainingElevators)
        firstIteration = False

    # Figure out where we are on the path and what our next step is
    idx = pathToFollow.index((clone_floor, clone_pos, direction == 'LEFT'))
    nextFloor, nextPos, movingLeft = pathToFollow[idx + 1]

    # Execute the next step in our planned path
    if nextFloor > clone_floor:
        print('ELEVATOR')
        elevators.add((clone_floor, clone_pos))
        nrRemainingElevators -= 1
    elif (direction == 'LEFT') != movingLeft:
        print('BLOCK')
        blockedPositions.add((clone_floor, clone_pos))
    else:
        print('WAIT')
