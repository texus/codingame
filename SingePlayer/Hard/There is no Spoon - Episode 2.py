import sys
import copy
from collections import defaultdict

# Global variables that are initialized at the beginning
nodes = []
conflictingEdges = defaultdict(list)

# Global variables that contain the current state and are regularly changed
nodeValues = {}
edgeValues = {}
lockedEdges = set()

class Node:
    def __init__(self, x, y, number):
        self.x = x
        self.y = y
        self.number = number
        self.edges = []

class Edge:
    def __init__(self, node1, node2):
        self.node1 = node1
        self.node2 = node2
        edgeValues[self] = 0

def isSolved():
    for node in nodes:
        nrConnectedEdges = sum(edgeValues[edge] for edge in node.edges)
        if nrConnectedEdges != node.number:
            return False

    # Check that all nodes form a single connected group
    reachableNodes = set()
    reachableNodesToExamine = set()
    reachableNodesToExamine.add(nodes[0])
    while reachableNodesToExamine:
        node = reachableNodesToExamine.pop()
        reachableNodes.add(node)
        for edge in node.edges:
            if edgeValues[edge] == 0:
                continue
            if edge.node1 not in reachableNodes:
                reachableNodesToExamine.add(edge.node1)
            if edge.node2 not in reachableNodes:
                reachableNodesToExamine.add(edge.node2)

    if len(reachableNodes) != len(nodes):
        return False

    return True

def wouldBeOverlapping(edge):
    assert(edgeValues[edge] == 0)
    return any(edgeValues[otherEdge] > 0 for otherEdge in conflictingEdges[edge])

def getOtherNode(edge, node):
    assert(edge.node1 == node or edge.node2 == node)
    return edge.node2 if edge.node1 == node else edge.node1

def getAvailableEdgesAtNode(node):
    return [edge for edge in node.edges \
            if edge not in lockedEdges \
            and ((edgeValues[edge] == 0 and not wouldBeOverlapping(edge)) \
                 or (edgeValues[edge] == 1 and nodeValues[getOtherNode(edge, node)] > 0))]
        
def setEdgeValue(edge, value):
    assert(value > edgeValues[edge])
    nodeValues[edge.node1] -= (value - edgeValues[edge])
    nodeValues[edge.node2] -= (value - edgeValues[edge])
    edgeValues[edge] = value
    return nodeValues[edge.node1] >= 0 and nodeValues[edge.node2] >= 0

def markEdgeForReprocessing(edge, nodesToProcess):
    nodesToProcess.add(edge.node1)
    nodesToProcess.add(edge.node2)
    for conflictingEdge in conflictingEdges[edge]:
        nodesToProcess.add(conflictingEdge.node1)
        nodesToProcess.add(conflictingEdge.node2)

def setGuaranteedEdges(addedEdge):
    if addedEdge:
        nodesToProcess = set()
        markEdgeForReprocessing(addedEdge, nodesToProcess)
    else:
        nodesToProcess = set(n for n in nodes)

    while nodesToProcess:
        node = nodesToProcess.pop()
        nrConnectedEdges = sum(edgeValues[edge] for edge in node.edges)

        # Skip if this node is already solved
        if nrConnectedEdges == node.number:
            continue
        
        availableEdges = getAvailableEdgesAtNode(node)

        # If there are no available edges left then we must have made a wrong decision earlier
        if not availableEdges:
            return False

        # If there is only one neighbor left then it must be connected with all available edges
        if len(availableEdges) == 1:
            remainingNodeNumber = nodeValues[node]
            if remainingNodeNumber != 1 and remainingNodeNumber != 2:
                # This is an invalid case, we must have made a wrong decision earlier
                return False

            edge = availableEdges[0]
            if edgeValues[edge] != remainingNodeNumber:
                if not setEdgeValue(edge, remainingNodeNumber):
                    return False
                markEdgeForReprocessing(edge, nodesToProcess)
            continue

        # If all remaining sides can only be given 2 edges then we can do so
        if nodeValues[node] == 2 * len(availableEdges):
            for edge in availableEdges:
                if edgeValues[edge] != 2:
                    if not setEdgeValue(edge, 2):
                        return False
                    markEdgeForReprocessing(edge, nodesToProcess)
            continue

        # If there is only one remaining option to distribute the edges then do so
        maxPossibleEdges = 0
        for edge in availableEdges:
            maxPossibleEdges += min(2, nodeValues[node], nodeValues[getOtherNode(edge, node)] + edgeValues[edge]) - edgeValues[edge]
        if maxPossibleEdges == nodeValues[node]:
            for edge in availableEdges:
                edgeValue = min(2, nodeValues[node], nodeValues[getOtherNode(edge, node)] + edgeValues[edge])
                if edgeValue == 0:
                    continue
                if not setEdgeValue(edge, edgeValue):
                    return False
                markEdgeForReprocessing(edge, nodesToProcess)
            continue

    return True

def attemptEdge():
    global nodeValues
    global edgeValues

    reachableNodes = set()
    reachableNodesToExamine = set()
    reachableNodesToExamine.add(nodes[0])
    while reachableNodesToExamine:
        node = reachableNodesToExamine.pop()
        reachableNodes.add(node)
        for edge in node.edges:
            if edgeValues[edge] == 0:
                continue
            if edge.node1 not in reachableNodes:
                reachableNodesToExamine.add(edge.node1)
            if edge.node2 not in reachableNodes:
                reachableNodesToExamine.add(edge.node2)

    for node in reachableNodes:
        availableEdges = getAvailableEdgesAtNode(node)
        for edge in availableEdges:
            if edgeValues[edge] == 0 and wouldBeOverlapping(edge):
                continue
            minEdges = edgeValues[edge] + 1
            maxEdges = 2 - edgeValues[edge]
            for i in range(maxEdges, minEdges-1, -1):
                assert(i == 1 or i == 2)
                if nodeValues[edge.node1] < i or nodeValues[edge.node2] < i:
                    continue
                if edge.node1.number == i and edge.node2.number == i: # Don't connect two '2' nodes with two edges
                    continue

                oldNodeValues = copy.copy(nodeValues)
                oldEdgeValues = copy.copy(edgeValues)
                lockedEdges.add(edge)

                if setEdgeValue(edge, i):
                    setGuaranteedEdges(edge)
                    if isSolved() or attemptEdge():
                        return True

                lockedEdges.remove(edge)
                nodeValues = oldNodeValues
                edgeValues = oldEdgeValues

    
    # We tried all remaining options and couldn't find a working one, we need to backtrack
    return False


nodeByPos = {}

width = int(input())  # the number of cells on the X axis
height = int(input())  # the number of cells on the Y axis
for i in range(height):
    line = input()  # width characters, each either a number or a '.'
    for j in range(len(line)):
      if line[j] != '.':
        node = Node(j, i, int(line[j]))
        nodes.append(node)
        nodeByPos[(j,i)] = node
        nodeValues[node] = int(line[j])

for node1 in nodes:
  for x in range(node1.x + 1, width):
    if (x, node1.y) in nodeByPos:
        node2 = nodeByPos[(x, node1.y)]
        edge = Edge(node1, node2)
        node1.edges.append(edge)
        node2.edges.append(edge)
        break
  for y in range(node1.y + 1, height):
    if (node1.x, y) in nodeByPos:
        node2 = nodeByPos[(node1.x, y)]
        edge = Edge(node1, node2)
        node1.edges.append(edge)
        node2.edges.append(edge)
        break

for edge1 in edgeValues:
    for edge2 in edgeValues:
        if edge1.node1.x == edge1.node2.x and edge2.node1.y == edge2.node2.y:
            if min(edge2.node1.x, edge2.node2.x) < edge1.node1.x and max(edge2.node1.x, edge2.node2.x) > edge1.node1.x \
            and min(edge1.node1.y, edge1.node2.y) < edge2.node1.y and max(edge1.node1.y, edge1.node2.y) > edge2.node1.y:
                conflictingEdges[edge1].append(edge2)
        if edge1.node1.y == edge1.node2.y and edge2.node1.x == edge2.node2.x:
            if min(edge1.node1.x, edge1.node2.x) < edge2.node1.x and max(edge1.node1.x, edge1.node2.x) > edge2.node1.x \
            and min(edge2.node1.y, edge2.node2.y) < edge1.node1.y and max(edge2.node1.y, edge2.node2.y) > edge1.node1.y:
                conflictingEdges[edge1].append(edge2)

setGuaranteedEdges(None)
if not isSolved():
    attemptEdge()

allEdges = set()
for node in nodes:
    allEdges.update(node.edges)

for edge in allEdges:
    if edgeValues[edge] > 0:
        print(edge.node1.x, edge.node1.y, edge.node2.x, edge.node2.y, edgeValues[edge])
