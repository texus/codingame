#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>
#include <map>

using namespace std;

struct Position
{
    int x;
    int y;
};

int calcDamage(vector<vector<char>>& grid, int x, int y)
{
    int damage = 0;
    for (int i = x-1; i >= max(0, x-3); --i)
    {
        if (grid[y][i] == '#')
            break;
        else if (grid[y][i] == '@')
            damage++;
    }
    for (int i = x+1; i <= min<int>(grid[0].size()-1, x+3); ++i)
    {
        if (grid[y][i] == '#')
            break;
        else if (grid[y][i] == '@')
            damage++;
    }
    for (int i = y-1; i >= max(0, y-3); --i)
    {
        if (grid[i][x] == '#')
            break;
        else if (grid[i][x] == '@')
            damage++;
    }
    for (int i = y+1; i <= min<int>(grid.size()-1, y+3); ++i)
    {
        if (grid[i][x] == '#')
            break;
        else if (grid[i][x] == '@')
            damage++;
    }

    return damage;
}

void destroy(vector<vector<char>>& grid, int x, int y)
{
    for (int i = x-1; i >= max(0, x-3); --i)
    {
        if (grid[y][i] == '#')
            break;
        else if (grid[y][i] == '@')
            grid[y][i] = '.';
    }
    for (int i = x+1; i <= min<int>(grid[0].size()-1, x+3); ++i)
    {
        if (grid[y][i] == '#')
            break;
        else if (grid[y][i] == '@')
            grid[y][i] = '.';
    }
    for (int i = y-1; i >= max(0, y-3); --i)
    {
        if (grid[i][x] == '#')
            break;
        else if (grid[i][x] == '@')
            grid[i][x] = '.';
    }
    for (int i = y+1; i <= min<int>(grid.size()-1, y+3); ++i)
    {
        if (grid[i][x] == '#')
            break;
        else if (grid[i][x] == '@')
            grid[i][x] = '.';
    }
}

int getRemainingTargets(vector<vector<char>>& grid)
{
    int remainingTargets = 0;
    for (int y = 0; y < grid.size(); ++y)
    {
        for (int x = 0; x < grid[y].size(); ++x)
        {
            if (grid[y][x] == '@')
                remainingTargets++;
        }
    }
    
    return remainingTargets;
}

bool canWeWin(vector<vector<char>> grid, int x, int y, int bombs)
{
    destroy(grid, x, y);

    // Where to place the bomb for maximum damage?
    int maxDamage = 0;
    for (int y = 0; y < grid.size(); ++y)
    {
        for (int x = 0; x < grid[y].size(); ++x)
        {
            if (grid[y][x] == '.')
            {
                int damage = calcDamage(grid, x, y);
                if ((damage > maxDamage)/* && canWeWin(grid, x, y, bombs-1)*/)
                    maxDamage = damage;
            }
        }
    }
    
    // If the maximum damage multiplied with bombs we have left is not enough to destroy
    // all targets, then we should look for a different place to put our initial bomb
    if (maxDamage * bombs >= getRemainingTargets(grid))
        return true;
    else
        return false;
}

int main()
{
    vector<vector<char>> grid;
    vector<vector<char>> resultGrid;
    map<pair<int, int>, int> tickingBombs;
    
    int width; // width of the firewall grid
    int height; // height of the firewall grid
    cin >> width >> height; cin.ignore();
    for (int i = 0; i < height; i++) {
        string mapRow; // one line of the firewall grid
        cin >> mapRow; cin.ignore();
        
        grid.push_back({});
        for (char c : mapRow)
            grid.back().push_back(c);
    }
    resultGrid = grid;

    // game loop
    while (1) {
        int rounds; // number of rounds left before the end of the game
        int bombs; // number of bombs left
        cin >> rounds >> bombs; cin.ignore();

        // Tick tack
        for(auto it = tickingBombs.begin(); it != tickingBombs.end();)
        {
            it->second--;
            if (it->second == 0)
            {
                destroy(grid, it->first.first, it->first.second);
                it = tickingBombs.erase(it);
            }
            else
                ++it;
        }

        // Where to place the bomb for maximum damage?
        int maxDamage = 0;
        Position bombPos;
        for (int x = 0; x < width; ++x)
        {
            for (int y = 0; y < height; ++y)
            {
                if (resultGrid[y][x] == '.')
                {
                    int damage = calcDamage(resultGrid, x, y);
                    if ((damage > maxDamage) && canWeWin(resultGrid, x, y, bombs-1))
                    {
                        maxDamage = damage;
                        bombPos = {x, y};
                    }
                }
            }
        }

        // At the end of the game, wait until last bomb explodes
        if (maxDamage == 0)
        {
            cout << "WAIT" << endl;
            continue;
        }
        
        // Place the bomb
        if ((grid[bombPos.y][bombPos.x] == '.')
         && (tickingBombs.find({bombPos.x, bombPos.y}) == tickingBombs.end()))
        {
            destroy(resultGrid, bombPos.x, bombPos.y);
            tickingBombs[{bombPos.x, bombPos.y}] = 3;
            cout << bombPos.x << " " << bombPos.y << endl;
        }
        else
            cout << "WAIT" << endl;
    }
}
