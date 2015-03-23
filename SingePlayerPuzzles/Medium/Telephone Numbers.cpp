#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

struct Node
{
    char value;
    vector<shared_ptr<Node>> children;
};

void insert(shared_ptr<Node> root, string telephone)
{
    if (telephone.empty())
        return;
    
    // Recursively pass it to our children if numbers have been seen before
    for (auto& child : root->children)
    {
        if (child->value == telephone[0])
        {
            insert(child, telephone.substr(1, telephone.length()-1));
            return;
        }
    }
    
    // A new number is found on this position, create a new branch
    shared_ptr<Node> child = make_shared<Node>();
    child->value = telephone[0];
    insert(child, telephone.substr(1, telephone.length()-1));
    root->children.push_back(child);
}

int count(shared_ptr<Node> root)
{
    int c = 1;
    for (auto& child : root->children)
        c += count(child);
    
    return c;
}

int main()
{
    shared_ptr<Node> root = make_shared<Node>();
    root->value = numeric_limits<char>::max(); // undefined (we don't need to use the root node, only to store our tree)

    int N;
    cin >> N; cin.ignore();
    for (int i = 0; i < N; i++) {
        string telephone;
        cin >> telephone; cin.ignore();
        
        insert(root, telephone);
    }

    cout << count(root)-1 << endl;
}
