#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct TreeNode
{
    TreeNode* dotChild = NULL;
    TreeNode* dashChild = NULL;
    long long valid = 0;
};

string encode(string input)
{
    string result;
    for (auto& c : input)
    {
        switch (c)
        {
            case 'A': result += ".-"; break;
            case 'B': result += "-..."; break;
            case 'C': result += "-.-."; break;
            case 'D': result += "-.."; break;
            case 'E': result += "."; break;
            case 'F': result += "..-."; break;
            case 'G': result += "--."; break;
            case 'H': result += "...."; break;
            case 'I': result += ".."; break;
            case 'J': result += ".---"; break;
            case 'K': result += "-.-"; break;
            case 'L': result += ".-.."; break;
            case 'M': result += "--"; break;
            case 'N': result += "-."; break;
            case 'O': result += "---"; break;
            case 'P': result += ".--."; break;
            case 'Q': result += "--.-"; break;
            case 'R': result += ".-."; break;
            case 'S': result += "..."; break;
            case 'T': result += "-"; break;
            case 'U': result += "..-"; break;
            case 'V': result += "...-"; break;
            case 'W': result += ".--"; break;
            case 'X': result += "-..-"; break;
            case 'Y': result += "-.--"; break;
            case 'Z': result += "--.."; break;
            default: throw runtime_error("ERROR");
        }
    }
    
    return result;
}

void insert(TreeNode* node, string dictWord, long long pos = 0)
{
    while (pos < dictWord.size()) {
        if (dictWord[pos] == '.') {
            if (node->dotChild == NULL)
                node->dotChild = new TreeNode();
            
            node = node->dotChild;
        }
        else {
            if (node->dashChild == NULL)
                node->dashChild = new TreeNode();
            
            node = node->dashChild;
        }
        
        pos += 1;
    }
    
    node->valid += 1;
}

void deleteTree(TreeNode* node)
{
    if (node->dotChild != NULL)
        deleteTree(node->dotChild);

    if (node->dashChild != NULL)
        deleteTree(node->dashChild);
    
    delete node;
}

string L;
TreeNode* root = new TreeNode();
map<long long, long long> cache;

long long solve(long long pos)
{
    TreeNode* node = root;
    long long solutions = 0;
    while (pos < L.size()) {
        if ((L[pos] == '.') && (node->dotChild != NULL))
            node = node->dotChild;
        else if ((L[pos] == '-') && (node->dashChild != NULL))
            node = node->dashChild;
        else
            break;
        
        if (node->valid > 0) {
            if (pos == L.size()-1)
                solutions += node->valid;
            else {
                if (cache.find(pos+1) != cache.end()) {
                    solutions += node->valid *  cache[pos+1];
                }
                else {
                    long long res = solve(pos+1);
                    if (res > 0) {
                        solutions += node->valid * res;
                        cache[pos+1] = res;
                    }
                }
            }
        }
        
        ++pos;
    }

    return solutions;
}

int main()
{
    cin >> L; cin.ignore();
    int N;
    cin >> N; cin.ignore();
    for (int i = 0; i < N; i++) {
        string W;
        cin >> W; cin.ignore();
        insert(root, encode(W));
    }

    cout << solve(0) << endl;

    deleteTree(root);
}
