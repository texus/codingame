#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

pair<int, int> findCenter(const vector<pair<int, int>>& giants)
{
    int centerX = 0;
    int centerY = 0;
    for (auto& giant : giants)
    {
        centerX += giant.first;
        centerY += giant.second;
    }
    
    centerX /= giants.size();
    centerY /= giants.size();
    
    return {centerX, centerY};
}

vector<pair<int, int>> findGiantsInRange(int TX, int TY, const vector<pair<int, int>>& giants)
{
    vector<pair<int, int>> closeGiants;
    for (auto& giant : giants)
    {
        if ((abs(giant.first - TX) <= 4) && (abs(giant.second - TY) <= 4))
            closeGiants.push_back(giant);
    }
    
    return closeGiants;
}

bool giantsTooClose(int TX, int TY, const vector<pair<int, int>>& giants)
{
    for (auto& giant : giants)
    {
        if ((abs(giant.first - TX) <= 1) && (abs(giant.second - TY) <= 1))
            return true;
    }
    
    return false;
}

string findMove(int& TX, int& TY, int CX, int CY)
{
    if (CX > TX)
    {
        if (CY > TY)
        {
            TX += 1;
            TY += 1;
            return "SE";
        }
        else if (CY < TY)
        {
            TX += 1;
            TY -= 1;
            return "NE";
        }
        else
        {
            TX += 1;
            return "E";
        }
    }
    else if (CX < TX)
    {
        if (CY > TY)
        {
            TX -= 1;
            TY += 1;
            return "SW";
        }
        else if (CY < TY)
        {
            TX -= 1;
            TY -= 1;
            return "NW";
        }
        else
        {
            TX -= 1;
            return "W";
        }
    }
    else
    {
        if (CY > TY)
        {
            TY += 1;
            return "S";
        }
        else if (CY < TY)
        {
            TY -= 1;
            return "N";
        }
        else
        {
            return "WAIT";
        }
    }
}

unsigned int dist(pair<int, int> first, pair<int, int> second)
{
    return abs(first.first - second.first) + abs(first.second - second.second);
}

string findBestMove(int& TX, int& TY, const vector<pair<int, int>>& giants)
{
    map<string, pair<int, pair<int, int>>> profit;
    
    auto center = findCenter(giants);

    // Move towards the center of the enemies when no enemy standing next to you
    if (!giantsTooClose(TX, TY, giants))
        return findMove(TX, TY, center.first, center.second);
    
    // Check in which direction we move best
    if (TX > 0)
    {
        int x = TX - 1;
        int y = TY;
        if (!giantsTooClose(x, y, giants))
            profit["W"] = {findGiantsInRange(x, y, giants).size(), {x, y}};
    }
    if (TY > 0)
    {
        int x = TX;
        int y = TY - 1;
        if (!giantsTooClose(x, y, giants))
            profit["N"] = {findGiantsInRange(x, y, giants).size(), {x, y}};
    }
    if (TX < 40)
    {
        int x = TX + 1;
        int y = TY;
        if (!giantsTooClose(x, y, giants))
            profit["E"] = {findGiantsInRange(x, y, giants).size(), {x, y}};
    }
    if (TY < 18)
    {
        int x = TX;
        int y = TY + 1;
        if (!giantsTooClose(x, y, giants))
            profit["S"] = {findGiantsInRange(x, y, giants).size(), {x, y}};
    }
    if ((TX > 0) && (TY > 0))
    {
        int x = TX - 1;
        int y = TY - 1;
        if (!giantsTooClose(x, y, giants))
            profit["NW"] = {findGiantsInRange(x, y, giants).size(), {x, y}};
    }
    if ((TX < 40) && (TY > 0))
    {
        int x = TX + 1;
        int y = TY - 1;
        if (!giantsTooClose(x, y, giants))
            profit["NE"] = {findGiantsInRange(x, y, giants).size(), {x, y}};
    }
    if ((TX > 0) && (TY > 0))
    {
        int x = TX - 1;
        int y = TY - 1;
        if (!giantsTooClose(x, y, giants))
            profit["SW"] = {findGiantsInRange(x, y, giants).size(), {x, y}};
    }
    if ((TX < 40) && (TY < 18))
    {
        int x = TX + 1;
        int y = TY + 1;
        if (!giantsTooClose(x, y, giants))
            profit["SE"] = {findGiantsInRange(x, y, giants).size(), {x, y}};
    }

    // Make the best move
    string move = "STRIKE";
    pair<int, pair<int, int>> bestOption = {};
    unsigned int bestDist = 0;
    for (auto& option : profit)
    {
        // Find the best option (move away from center when tie)
        if ((option.second.first > bestOption.first) ||
            ((option.second.first == bestOption.first) && (dist(option.second.second, center) > bestDist)))
        {
            bestOption = option.second;
            move = option.first;
            bestDist = dist(bestOption.second, center);
        }
    }
    
    if (move != "STRIKE")
    {
        TX = bestOption.second.first;
        TY = bestOption.second.second;
    }

    return move;
}

int main()
{
    int TX;
    int TY;
    cin >> TX >> TY; cin.ignore();
    
    vector<pair<int, int>> giants;

    // game loop
    while (1) {
        giants.clear();
        
        int H; // the remaining number of hammer strikes.
        int N; // the number of giants which are still present on the map.
        cin >> H >> N; cin.ignore();
        for (int i = 0; i < N; i++) {
            int X;
            int Y;
            cin >> X >> Y; cin.ignore();
            
            giants.push_back({X, Y});
        }

        //auto center = findCenter(giants);
        vector<pair<int, int>> closeEnemies = findGiantsInRange(TX, TY, giants);
        
        // Once we can kill all giants, do so
        if (giants.size() == closeEnemies.size())
        {
            cout << "STRIKE" << endl;
            continue;
        }

        int newTX = TX;
        int newTY = TY;
        string move = findBestMove(newTX, newTY, giants);

        cout << move << endl;
        TX = newTX;
        TY = newTY;
    }
}
