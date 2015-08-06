#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <memory>
#include <queue>

using namespace std;

struct Node
{
    int id;
    vector<Node*> connections;
    bool exitNode = false;
};

vector<Node> nodes;

pair<int, int> findShortestPath(int nodeId, vector<int> visited)
{
    if (nodes[nodeId].exitNode)
        return {0, nodeId};
    else
    {
        pair<int, int> bestSolution(numeric_limits<int>::max(), nodeId);
        for (auto& connection : nodes[nodeId].connections)
        {
            bool found = false;
            for (auto& visitedId : visited)
            {
                if (connection->id == visitedId)
                    found = true;
            }
            
            if (!found)
            {
                visited.push_back(connection->id);
                auto result = findShortestPath(connection->id, visited);
                if (result.first < bestSolution.first)
                {
                    bestSolution.first = result.first + 1;
                    bestSolution.second = connection->id;
                }
            }
        }
        
        return bestSolution;
    }
}


/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int N; // the total number of nodes in the level, including the gateways
    int L; // the number of links
    int E; // the number of exit gateways
    cin >> N >> L >> E; cin.ignore();

    assert(N > 0);
    nodes.resize(N);
    for (int i = 0; i < N; ++i)
        nodes[i].id = i;
    
    for (int i = 0; i < L; i++) {
        int N1; // N1 and N2 defines a link between these nodes
        int N2;
        cin >> N1 >> N2; cin.ignore();
        
        nodes[N1].connections.push_back(&nodes[N2]);
        nodes[N2].connections.push_back(&nodes[N1]);
    }
    for (int i = 0; i < E; i++) {
        int EI; // the index of a gateway node
        cin >> EI; cin.ignore();
        
        nodes[EI].exitNode = true;
    }
    
    // game loop
    while (1) {
        int SI; // The index of the node on which the Skynet agent is positioned this turn
        cin >> SI; cin.ignore();
        
        int TI = findShortestPath(SI, {SI}).second;
        nodes[SI].connections.erase(std::find(nodes[SI].connections.begin(), nodes[SI].connections.end(), &nodes[TI]));
        nodes[TI].connections.erase(std::find(nodes[TI].connections.begin(), nodes[TI].connections.end(), &nodes[SI]));
        cout << SI << " " << TI << endl;
    }
}
