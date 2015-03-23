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
    string MESSAGE;
    getline(cin, MESSAGE);
    
    // Generate the binary representation of the message
    string bitMessage;
    for (char c : MESSAGE)
    {
        for (int i = 0; i < 7; ++i)
        {
            c = c << 1;
            bitMessage += ((c >> 7) & 1) + '0';
        }
    }

    // Encode the message
    int i = 0;
    while (i < bitMessage.size())
    {
        if (bitMessage[i] == '0')
        {
            cout << "00 ";
            for (; i < bitMessage.size() && bitMessage[i] == '0'; ++i)
                cout << "0";
            
            if (i < bitMessage.size())
                cout << " ";
        }
        else
        {
            cout << "0 ";
            for (; i < bitMessage.size() && bitMessage[i] == '1'; ++i)
                cout << "0";
            
            if (i < bitMessage.size())
                cout << " ";
        }
    }
    
    cout << endl;
}
