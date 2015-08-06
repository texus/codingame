#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <stack>

using namespace std;

int dfs(map<int, vector<int>>& graph, int start)
{
    stack<tuple<int, int, int>> fringe;
    fringe.push(tuple<int, int, int>{start, start, 0});

    int maxDistance = 0;
    while (!fringe.empty())
    {
        int nextVertex = get<0>(fringe.top());
        int parent = get<1>(fringe.top());
        int distance = get<2>(fringe.top());
        fringe.pop();
        
        if (distance > maxDistance)
            maxDistance = distance;

        for (int vertex : graph[nextVertex])
        {
            if (vertex != parent)
                fringe.push(tuple<int, int, int>{vertex, nextVertex, distance+1});
        }
    }
    
    return maxDistance + 1;
}

int main()
{
    map<int, vector<int>> graph;
    
    int n; // the number of adjacency relations
    cin >> n; cin.ignore();
    for (int i = 0; i < n; i++) {
        int xi; // the ID of a person which is adjacent to yi
        int yi; // the ID of a person which is adjacent to xi
        cin >> xi >> yi; cin.ignore();
        
        graph[xi].push_back(yi);
        graph[yi].push_back(xi);
    }

    // Find a leaf node
    int leafVertex;
    for (auto& vertex : graph)
    {
        if (vertex.second.size() == 1)
        {
            leafVertex = vertex.first;
            break;
        }
    }
    
    // Distance between furthest node and leaf node divided by 2 is what we need
    int distance = dfs(graph, leafVertex);
    cout << (distance / 2) << endl;
}
