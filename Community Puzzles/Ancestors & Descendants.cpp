#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    std::vector<std::string> descendants;
    
    int count;
    cin >> count; cin.ignore();
    for (int i = 0; i < count; i++) {
        string line;
        getline(cin, line);
        
        auto dots = line.rfind('.');
        if (dots == std::string::npos)
            dots = 0;
        else
            dots++;
        std::cerr << line << std::endl;
        if (descendants.size() <= dots)
        {
            descendants.push_back(line.substr(dots));
        }
        else
        {
            if (!descendants.empty())
            {
                std::cout << descendants[0];
                for (unsigned int j = 1; j < descendants.size(); ++j)
                    std::cout << " > " << descendants[j];
                
                std::cout << std::endl;
            }
            
            descendants.erase(descendants.begin()+dots, descendants.end());
            descendants.push_back(line.substr(dots));
        }
    }
    
    if (!descendants.empty())
    {
        std::cout << descendants[0];
        for (unsigned int j = 1; j < descendants.size(); ++j)
            std::cout << " > " << descendants[j];
        
        std::cout << std::endl;
    }
}
