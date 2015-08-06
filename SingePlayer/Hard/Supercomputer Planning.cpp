#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main()
{
    map<int, int> tasks;

    int N;
    cin >> N; cin.ignore();
    for (int i = 0; i < N; i++) {
        int J;
        int D;
        cin >> J >> D; cin.ignore();
        
        // When two tasks start at the same moment, forget about the larger task
        if ((tasks.find(J) == tasks.end()) || (tasks[J] > D))
            tasks[J] = D;
    }

    if (tasks.empty())
        cout << 0 << endl;
    else
    {
        unsigned int nrOfTasks = 0;
        unsigned int taskEnd = 0;
        for (auto& task : tasks)
        {
            // If we can just take this task then do so
            if (task.first >= taskEnd)
            {
                nrOfTasks++;
                taskEnd = task.first + task.second;
            }
            else // Overlap
            {
                // If the next task ends before the old one then use it instead
                if (task.first + task.second < taskEnd)
                    taskEnd = task.first + task.second;
            }
        }
        
        cout << nrOfTasks << endl;
    }
}
