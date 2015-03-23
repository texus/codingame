#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int R;
    cin >> R; cin.ignore();
    int L;
    cin >> L; cin.ignore();

    vector<vector<int>> lines(2, vector<int>(1, R));
    for (int l = 2; l <= L; ++l)
    {
        assert(!lines[l-1].empty());
        int last = numeric_limits<int>::max();
        vector<pair<int, int>> count;
        for (int i = 0; i < lines[l-1].size(); ++i)
        {
            if (lines[l-1][i] == last)
            {
                count.back().second++;
            }
            else
            {
                last = lines[l-1][i];
                count.push_back({lines[l-1][i], 1});
            }
        }
        
        lines.push_back({});
        for (int i = 0; i < count.size(); ++i)
        {
            lines[l].push_back(count[i].second);
            lines[l].push_back(count[i].first);
        }
    }
    
    for (int i = 0; i < lines.back().size(); ++i)
    {
        if (i+1 == lines.back().size())
            cout << lines.back()[i] << endl;
        else
            cout << lines.back()[i] << " ";
    }
}
