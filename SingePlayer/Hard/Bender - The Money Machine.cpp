#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <set>
#include <map>

using namespace std;

int N;
unsigned int search(map<int, pair<int, vector<int>>>& grid)
{
    vector<int> money(N, 0);
    auto fringe = queue<pair<int, int>>{};
    fringe.push({0, 0});

    while (!fringe.empty())
    {
        pair<int, int> roomNr = fringe.front();
        fringe.pop();
        
        if (money[roomNr.second] < money[roomNr.first] + grid[roomNr.second].first)
        {
            money[roomNr.second] = money[roomNr.first] + grid[roomNr.second].first;
            
            for (auto& room : grid[roomNr.second].second)
            {
                if (room != -1)
                    fringe.push({roomNr.second, room});
            }
        }
    }
    
    return *max_element(money.begin(), money.end());
}

int main()
{
    map<int, pair<int, vector<int>>> grid;
    set<int> exits;
    
    cin >> N; cin.ignore();
    for (int i = 0; i < N; i++) {
        string room;
        getline(cin, room);
        
        string roomNr;
        string money;
        string exit1;
        string exit2;
        stringstream ss(room);
        ss >> roomNr;
        ss >> money;
        ss >> exit1;
        ss >> exit2;
        
        grid[stoi(roomNr)].first = stoi(money);
        
        if (exit1 != "E")
            grid[stoi(roomNr)].second.push_back(stoi(exit1));
        else
        {
            grid[stoi(roomNr)].second.push_back(-1);
            exits.insert(stoi(roomNr));
        }

        if (exit2 != "E")
            grid[stoi(roomNr)].second.push_back(stoi(exit2));
        else
        {
            grid[stoi(roomNr)].second.push_back(-1);
            exits.insert(stoi(roomNr));
        }
    }
    
    cout << search(grid) << endl;
}
