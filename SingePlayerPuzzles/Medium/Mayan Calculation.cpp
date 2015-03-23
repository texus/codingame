#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    vector<string> numbers(20);
    string num1, num2;
    
    int L;
    int H;
    cin >> L >> H; cin.ignore();
    for (int i = 0; i < H; i++) {
        string numeral;
        cin >> numeral; cin.ignore();
        
        for (int j = 0; j < 20; ++j)
            numbers[j].append(numeral.substr(j*L, L));
    }
    int S1;
    cin >> S1; cin.ignore();
    for (int i = 0; i < S1; i++) {
        string num1Line;
        cin >> num1Line; cin.ignore();
        num1.append(num1Line);
    }
    int S2;
    cin >> S2; cin.ignore();
    for (int i = 0; i < S2; i++) {
        string num2Line;
        cin >> num2Line; cin.ignore();
        num2.append(num2Line);
    }

    string operation;
    cin >> operation; cin.ignore();
    
    long long num1Value = 0;
    for (int j = 0; j < num1.size() / (H*L); ++j)
    {
        for (int i = 0; i < numbers.size(); ++i)
        {
            if (numbers[i] == num1.substr(j*H*L, H*L))
                num1Value += i * pow(20, (num1.size() / (H*L)) - j - 1);
        }
    }

    long long num2Value = 0;
    for (int j = 0; j < num2.size() / (H*L); ++j)
    {
        for (int i = 0; i < numbers.size(); ++i)
        {
            if (numbers[i] == num2.substr(j*H*L, H*L))
                num2Value += i * pow(20, (num2.size() / (H*L)) - j - 1);
        }
    }

    long long result;
    if (operation == "+")
        result = num1Value + num2Value;
    else if (operation == "-")
        result = num1Value - num2Value;
    if (operation == "*")
        result = num1Value * num2Value;
    if (operation == "/")
        result = num1Value / num2Value;
    
    deque<long long> resultingNumbers = {result};
    while (result > 20)
    {
        resultingNumbers.pop_front();
        resultingNumbers.push_front(result % 20);
        resultingNumbers.push_front(result / 20);
        result /= 20;
    }

    for (long long num : resultingNumbers)
    {
        for (int i = 0; i < H; ++i)
            cout << numbers[num].substr(i*L, L) << endl;
    }
}
