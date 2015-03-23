#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

int count(int node, map<int, vector<int>>& edges)
{
    if (!edges[node].empty())
    {
        int maxCount = 1;
        for (int v : edges[node])
        {
            int c = count(v, edges);
            if (c > maxCount)
                maxCount = c;
        }
        
        return maxCount + 1;
    }
    else
        return 1;
}

int main()
{
    set<int> roots;
    map<int, vector<int>> edges;
    
    int n; // the number of relationships of influence
    cin >> n; cin.ignore();
    for (int i = 0; i < n; i++) {
        int x; // a relationship of influence between two people (x influences y)
        int y;
        cin >> x >> y; cin.ignore();
        
        // Add the relationship to the list
        edges[x].push_back(y);
        roots.insert(x);
    }
    
    // Find all the roots
    for (auto& vs : edges)
    {
        for (int v : vs.second)
            roots.erase(v);
    }
    
    // Start from all roots and count their influences
    int maxCount = 0;
    for (int v : roots)
    {
        int c = count(v, edges);
        if (c > maxCount)
            maxCount = c;
    }
    
    cout << maxCount << endl;
}
