#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cassert>
#include <stack>

using namespace std;

int R; // number of rows.
int C; // number of columns.
int A; // number of rounds between the time the alarm countdown is activated and the time the alarm goes off.

struct Position
{
    int x;
    int y;
};

vector<Position> getNeighbors(vector<vector<char>>& graph, Position target)
{
    if (graph[target.y][target.x] == '?')
        return {};
    else
    {
        vector<Position> neighbors;
        
        if (graph[target.y][target.x-1] != '#')
            neighbors.push_back({target.x-1, target.y});
        if (graph[target.y][target.x+1] != '#')
            neighbors.push_back({target.x+1, target.y});
        if (graph[target.y-1][target.x] != '#')
            neighbors.push_back({target.x, target.y-1});
        if (graph[target.y+1][target.x] != '#')
            neighbors.push_back({target.x, target.y+1});
        
        return neighbors;
    }
}

vector<Position> dijkstra(vector<vector<char>>& graph, Position source, char goal)
{
    auto dist = vector<vector<int>>(R, vector<int>(C, numeric_limits<int>::max()));
    auto prev = vector<vector<Position>>(R, vector<Position>(C, {numeric_limits<int>::max(), numeric_limits<int>::max()}));
    vector<Position> unvisited;

    // Initialization
    dist[source.y][source.x] = 0;
    for (int y = 0; y < R; ++y)
    {
        for (int x = 0; x < C; ++x)
            unvisited.push_back({x, y});
    }

    while (!unvisited.empty())
    {
        // Find node with smallest distance
        vector<Position>::iterator minIt = unvisited.begin();
        int minDist = numeric_limits<int>::max();
        for (auto it = unvisited.begin(); it != unvisited.end(); ++it)
        {
            if (dist[it->y][it->x] < minDist)
            {
                minDist = dist[it->y][it->x];
                minIt = it;
            }
        }
        
        // Return an empty list when there is no way to get to the goal
        if (minDist == numeric_limits<int>::max())
            return {};
            
        // Remove and return best vertex
        Position target = *minIt;
        unvisited.erase(minIt);

        // Check if goal node
        if (graph[target.y][target.x] == goal)
        {
            stack<Position> pathStack;
            Position node = target;
            while (prev[node.y][node.x].x != numeric_limits<int>::max() && prev[node.y][node.x].y != numeric_limits<int>::max())
            {
                pathStack.push(node);
                node = prev[node.y][node.x];
            }

            vector<Position> path;
            while (!pathStack.empty())
            {
                path.push_back(pathStack.top());
                pathStack.pop();
            }

            return path;
        }
        
        vector<Position> neighbors = getNeighbors(graph, target);
        for (Position& neighbor : neighbors)
        {
            int alt = dist[target.y][target.x] + 1;
            if (alt < dist[neighbor.y][neighbor.x])
            {
                dist[neighbor.y][neighbor.x] = alt;
                prev[neighbor.y][neighbor.x] = target;
            }
        }
    }

    return {};
}

int main()
{
    cin >> R >> C >> A; cin.ignore();
    
    bool controlFound = false;
    bool controlVisited = false;

    // game loop
    while (1) {
        vector<vector<char>> grid;
        
        int KR; // row where Kirk is located.
        int KC; // column where Kirk is located.
        cin >> KR >> KC; cin.ignore();
        for (int i = 0; i < R; i++) {
            string ROW; // C of the characters in '#.TC?' (i.e. one line of the ASCII maze).
            cin >> ROW; cin.ignore();
            
            grid.push_back({});
            for (char c : ROW)
                grid.back().push_back(c);
        }

        if (grid[KR][KC] == 'C')
            controlVisited = true;
        
        vector<Position> path;
        if (controlVisited)
        {
            path = dijkstra(grid, {KC, KR}, 'T');
        }
        else
        {
            path = dijkstra(grid, {KC, KR}, 'C');
            if (path.empty())
                path = dijkstra(grid, {KC, KR}, '?');
        }
        assert(!path.empty());
        
        if (path[0].x > KC)
            cout << "RIGHT" << endl;
        else if (path[0].x < KC)
            cout << "LEFT" << endl;
        else if (path[0].y > KR)
            cout << "DOWN" << endl;
        else
            cout << "UP" << endl;
    }
}
