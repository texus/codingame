#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

vector<vector<int>> cache;

int getLakeSize(const vector<vector<bool>>& grid, int x, int y)
{
    if (cache[y][x] != 0)
        return cache[y][x];
    
    int waterCount = 0;
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
    
    vector<pair<int, int>> visitedCells;

    queue<pair<int, int>> fringe;
    fringe.push({x, y});
    while (!fringe.empty())
    {
        pair<int, int> cell = fringe.front();
        fringe.pop();

        if (!visited[cell.second][cell.first])
        {
            visited[cell.second][cell.first] = true;
            if (grid[cell.second][cell.first])
            {
                visitedCells.push_back({cell.first, cell.second});
                waterCount += 1;
                
                if (cell.first > 0)
                {
                    if (!visited[cell.second][cell.first-1])
                        fringe.push({cell.first-1, cell.second});
                }
                if (cell.second > 0)
                {
                    if (!visited[cell.second-1][cell.first])
                        fringe.push({cell.first, cell.second-1});
                }
                if (cell.first < grid[0].size()-1)
                {
                    if (!visited[cell.second][cell.first+1])
                        fringe.push({cell.first+1, cell.second});
                }
                if (cell.second < grid.size()-1)
                {
                    if (!visited[cell.second+1][cell.first])
                        fringe.push({cell.first, cell.second+1});
                }
            }
        }
    }
    
    for (auto& cell : visitedCells)
        cache[cell.second][cell.first] = waterCount;

    return waterCount;
}

int main()
{
    vector<int> answers;
    vector<vector<bool>> grid;
    
    int L;
    cin >> L; cin.ignore();
    int H;
    cin >> H; cin.ignore();
    for (int i = 0; i < H; i++) {
        string row;
        cin >> row; cin.ignore();
        
        grid.push_back({});
        for (char c : row)
        {
            if (c == '#')
                grid.back().push_back(false);
            else
                grid.back().push_back(true);
        }
    }
    
    cache.resize(grid.size(), vector<int>(grid[0].size(), 0));
    
    int N;
    cin >> N; cin.ignore();
    for (int i = 0; i < N; i++) {
        int X;
        int Y;
        cin >> X >> Y; cin.ignore();
        
        answers.push_back(getLakeSize(grid, X, Y));
    }
    for (int i = 0; i < N; i++) {
        cout << answers[i] << endl;
    }
}
