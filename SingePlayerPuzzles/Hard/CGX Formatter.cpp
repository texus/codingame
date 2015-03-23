#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int spaces = 0;
bool newLine = true;

void printSpaces(int spaces)
{
    for (int i = 0; i < spaces; ++i)
        cout << ' ';
}

void printNewLine()
{
    cout << endl;
    newLine = true;
}

void print(char c)
{
    if (newLine)
    {
        printSpaces(spaces);
        newLine = false;
    }
    
    cout << c;
}

int main()
{
    
    int N;
    cin >> N; cin.ignore();
    for (int i = 0; i < N; i++) {
        string CGXLine;
        getline(cin, CGXLine);
        
        bool readingString = false;
        for (char c : CGXLine)
        {
            if (readingString)
            {
                print(c);
                
                if (c == '\'')
                    readingString = false;
            }
            else
            {
                switch (c)
                {
                    case ' ':
                    case '\t':
                        break;
                    
                    case '(':
                        if (!newLine)
                            printNewLine();
                        print('(');
                        printNewLine();
                        spaces += 4;
                        break;
                    
                    case ')':
                        spaces -= 4;
                        if (!newLine)
                            printNewLine();
                        print(')');
                        break;
                    
                    case '\'':
                        readingString = !readingString;
                        print('\'');
                        break;
                    
                    case ';':
                        print(';');
                        printNewLine();
                        break;
                    
                    default:
                        print(c);
                        break;
                };
            }
        }
    }
}
