#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cassert>
#include <unistd.h>

struct State
{
    int x;
    int y;
    bool inverted = false;
    bool breakerMode = false;
    std::string direction = "SOUTH";

    bool operator== (const State& state) const
    {
        return ((x == state.x)
             && (y == state.y)
             && (inverted == state.inverted)
             && (breakerMode == state.breakerMode)
             && (direction == state.direction));
    }
};

std::map<std::pair<int, int>, std::vector<State>> visited;

std::string directionToString(int x, int y)
{
    if (x == 0)
    {
        if (y == 1)
            return "SOUTH";
        else
            return "NORTH";
    }
    else
    {
        if (x == 1)
            return "EAST";
        else
            return "WEST";
    }
}

std::string move(std::vector<std::vector<char>>& map, State& currentState)
{
    std::vector<std::pair<int, int>> directions;
    if (currentState.inverted)
        directions = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
    else
        directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    
    for (auto& direction : directions)
    {
        if ((map[currentState.y + direction.second][currentState.x + direction.first] != 'X')
         && (map[currentState.y + direction.second][currentState.x + direction.first] != '#'))
        {
            currentState.x += direction.first;
            currentState.y += direction.second;
            currentState.direction = directionToString(direction.first, direction.second);
            return currentState.direction;
        }
    }
}

std::string makeMovement(int x, int y, std::vector<std::vector<char>>& map, State& currentState)
{
    if (map[currentState.y+y][currentState.x+x] == 'X')
    {
        if (currentState.breakerMode)
        {
            map[currentState.y+y][currentState.x+x] = ' ';
            visited.clear();
        }
        else
            return move(map, currentState);
    }
    else if (map[currentState.y+y][currentState.x+x] == '#')
        return move(map, currentState);

    currentState.x += x;
    currentState.y += y;
    return directionToString(x, y);
}

int main()
{
    std::vector<std::vector<char>> map;
    std::vector<std::string> moves;
    std::vector<std::pair<int, int>> teleporters;
    State currentState;
    
    int L;
    int C;
    std::cin >> L >> C; std::cin.ignore();
    for (int i = 0; i < L; i++) {
        std::string row;
        std::getline(std::cin, row);
        
        map.push_back({});
        for (int j = 0; j < C; ++j)
        {
            map.back().push_back(row[j]);
            
            if (row[j] == '@')
            {
                currentState.x = j;
                currentState.y = i;
            }
            else if (row[j] == 'T')
            {
                teleporters.push_back({j, i});
            }
        }
    }
    
    assert(teleporters.size() == 0 || teleporters.size() == 2);

    while (map[currentState.y][currentState.x] != '$')
    {
        // If we were already here that we are in an endless loop
        if (visited.find({currentState.x, currentState.y}) != visited.end())
        {
            if (std::find(visited[{currentState.x, currentState.y}].begin(),
                          visited[{currentState.x, currentState.y}].end(),
                          currentState) != visited[{currentState.x, currentState.y}].end())
            {
                std::cout << "LOOP" << std::endl;
                return 0;
            }
        }
        
        // Store the current state (to detect looping)
        visited[{currentState.x, currentState.y}].push_back(currentState);
        
        // Check if we have to do something special
        switch (map[currentState.y][currentState.x])
        {
            case 'N':
                currentState.direction = "NORTH";
                break;

            case 'E':
                currentState.direction = "EAST";
                break;

            case 'S':
                currentState.direction = "SOUTH";
                break;

            case 'W':
                currentState.direction = "WEST";
                break;
                
            case 'I':
                currentState.inverted = !currentState.inverted;
                break;
            
            case 'B':
                currentState.breakerMode = !currentState.breakerMode;
                break;
            
            case 'T':
            {
                if ((currentState.x == teleporters[0].first) && (currentState.y == teleporters[0].second))
                {
                    currentState.x = teleporters[1].first;
                    currentState.y = teleporters[1].second;
                }
                else
                {
                    currentState.x = teleporters[0].first;
                    currentState.y = teleporters[0].second;
                }
                break;
            }
        };

        // Make our move
        if (currentState.direction == "NORTH")
            moves.push_back(makeMovement(0, -1, map, currentState));
        else if (currentState.direction == "EAST")
            moves.push_back(makeMovement(1, 0, map, currentState));
        else if (currentState.direction == "SOUTH")
            moves.push_back(makeMovement(0, 1, map, currentState));
        else if (currentState.direction == "WEST")
            moves.push_back(makeMovement(-1, 0, map, currentState));
    }

    for (std::string move : moves)
        std::cout << move << std::endl;
    
    return 0;
}
