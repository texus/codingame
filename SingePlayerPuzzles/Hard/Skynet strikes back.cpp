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
    bool visited = false;
};

vector<Node> nodes;

vector<Node*> getGatewayLinks(Node* node)
{
    vector<Node*> nodes;
    for (auto& connection : node->connections)
    {
        if (connection->exitNode)
            nodes.push_back(connection);
    }
    
    return nodes;
}

pair<int, int> findBest(Node* start)
{
    for (auto& node : nodes)
        node.visited = false;

    bool firstFound = false;
    pair<int, int> backupPlan;
    
    queue<Node*> fringe;
    fringe.push(start);
    while (!fringe.empty())
    {
        Node* node = fringe.front();
        fringe.pop();
        
        node->visited = true;
        
        vector<Node*> gatewayLinks = getGatewayLinks(node);
        
        if (gatewayLinks.size() > 1)
        {
            return {node->id, gatewayLinks[0]->id};
        }
        else if (gatewayLinks.size() == 1)
        {
            if (!firstFound)
            {
                firstFound = true;
                backupPlan = {node->id, gatewayLinks[0]->id};
            }
            
            for (auto& neighbor : node->connections)
            {
                if (!neighbor->visited)
                    fringe.push(neighbor);
            }
        }
        else // gatewayLinks.size() == 0
        {
            if (!firstFound)
            {
                for (auto& neighbor : node->connections)
                {
                    if (!neighbor->visited)
                        fringe.push(neighbor);
                }
            }
        }
    }
    
    if (firstFound)
        return backupPlan;
    else
    {
        cerr << "ERROR, no immediate thread, we should probably pick some link though" << endl;
        return {0, 0};
    }
}

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

        pair<int, int> connection = findBest(&nodes[SI]);
        cout << connection.first << " " << connection.second << endl;
        
        // Remove the connection (so the algorithm doesn't try to destroy it twice)
        nodes[connection.first].connections.erase(find(nodes[connection.first].connections.begin(), nodes[connection.first].connections.end(), &nodes[connection.second]));
        nodes[connection.second].connections.erase(find(nodes[connection.second].connections.begin(), nodes[connection.second].connections.end(), &nodes[connection.first]));
    }
}
