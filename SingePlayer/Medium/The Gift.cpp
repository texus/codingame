#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int totalBudget = 0;
    vector<int> budget;
    
    int N;
    cin >> N; cin.ignore();
    int C;
    cin >> C; cin.ignore();
    for (int i = 0; i < N; i++) {
        int B;
        cin >> B; cin.ignore();
        
        budget.push_back(B);
        totalBudget += B;
    }
    
    sort(budget.begin(), budget.end());

    if (C > totalBudget)
        cout << "IMPOSSIBLE" << endl;
    else
    {
        int remainingOods = N;
        int remainingCost = C;
        
        while (remainingOods > 0)
        {
            bool averagePossible = true;
            int average = remainingCost / remainingOods;
            int remainder = remainingCost % remainingOods;
            for (int i = N - remainingOods; i < N; ++i)
            {
                if (budget[i] <= average)
                {
                    cout << budget[i] << endl;
                    remainingCost -= budget[i];
                    remainingOods--;
                    averagePossible = false;
                }
                else
                {
                    if (averagePossible)
                    {
                        for (int j = i; j < N - remainder; ++j)
                            cout << average << endl;
                        
                        for (int j = N - remainder; j < N; ++j)
                            cout << average+1 << endl;
                        
                        remainingOods = 0;
                        break;
                    }
                    else // A new average should be calculated
                        break;
                }
            }
        }
    }
}
