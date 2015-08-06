#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cassert>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int n;
    cin >> n; cin.ignore();
    string vs;
    getline(cin, vs);

    vector<int> values;
    stringstream ss(vs);
    for (int i = 0; i < n; ++i)
    {
        string temp;
        ss >> temp;
        values.push_back(stoi(temp));
    }
    
    assert(!values.empty());
    
    int loss = 0;
    int maxSeen = values[0];
    int minSeen = values[0];
    for (int i = 1; i < n; ++i)
    {
        if (values[i] > maxSeen)
            maxSeen = values[i];
        else if (values[i] < minSeen)
        {
            minSeen = values[i];
            loss = maxSeen - minSeen;
        }
    }
    
    cout << -loss << endl;
}
