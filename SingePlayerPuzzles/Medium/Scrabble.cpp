
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int charVal(char c)
{
    switch (c)
    {
        case 'e':
        case 'a':
        case 'i':
        case 'o':
        case 'n':
        case 'r':
        case 't':
        case 'l':
        case 's':
        case 'u':
            return 1;
        
        case 'd':
        case 'g':
            return 2;
        
        case 'b':
        case 'c':
        case 'm':
        case 'p':
            return 3;
            
        case 'f':
        case 'h':
        case 'v':
        case 'w':
        case 'y':
            return 4;
        
        case 'k':
            return 5;
        
        case 'j':
        case 'x':
            return 8;
        
        case 'q':
        case 'z':
            return 10;
    };
}

int main()
{
    vector<string> words;
    
    int N;
    cin >> N; cin.ignore();
    for (int i = 0; i < N; i++) {
        string W;
        getline(cin, W);
        
        if (W.length() <= 7)
            words.push_back(W);
    }
    string LETTERS;
    getline(cin, LETTERS);
    
    // Find all possible words that can be made with the 7 letters
    vector<string> possibleWords;
    for (const string& word : words)
    {
        string sortedWord = word;
        sort(LETTERS.begin(), LETTERS.end());
        sort(sortedWord.begin(), sortedWord.end());
        if (includes(LETTERS.begin(), LETTERS.end(), sortedWord.begin(), sortedWord.end()))
            possibleWords.push_back(word);
    }
    
    // Find the word that gives us the most letters
    int maxVal = 0;
    string bestWord;
    for (const string& word : possibleWords)
    {
        int val = 0;
        for (char c : word)
            val += charVal(c);
        
        if (val > maxVal)
        {
            maxVal = val;
            bestWord = word;
        }
    }
    
    cout << bestWord << endl;
}
