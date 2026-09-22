#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node
{
    int data;
    int height;
    Node *left;
    Node *right;

    Node(int value)
    {
        data = value;
        height = 0;
        left = NULL;
        right = NULL;
    }
};

int getHeight(Node *root)
{
    if (root == NULL)
        return -1;
    return root->height;
}

void updateHeight(Node *root)
{
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
}

int getBalance(Node *root)
{
    if (root == NULL)
        return 0;
    return getHeight(root->left) - getHeight(root->right);
}

Node *rotateLeft(Node *root)
{
    Node *newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;

    updateHeight(root);
    updateHeight(newRoot);
    return newRoot;
}

Node *rotateRight(Node *root)
{
    Node *newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;

    updateHeight(root);
    updateHeight(newRoot);
    return newRoot;
}

Node *rebalance(Node *root)
{
    updateHeight(root);
    int balance = getBalance(root);

    if (balance > 1)
    {
        if (getBalance(root->left) < 0)
            root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1)
    {
        if (getBalance(root->right) > 0)
            root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

Node *insertNode(Node *root, int key)
{
    if (root == NULL)
        return new Node(key);

    if (key == root->data)
        return root;

    if (key < root->data)
        root->left = insertNode(root->left, key);
    else
        root->right = insertNode(root->right, key);

    return rebalance(root);
}

void collectAtDistance(Node *root, int dist, vector<int> &result)
{
    if (root == NULL || dist < 0)
        return;

    if (dist == 0)
    {
        result.push_back(root->data);
        return;
    }

    collectAtDistance(root->left, dist - 1, result);
    collectAtDistance(root->right, dist - 1, result);
}

int findTarget(Node *root, int target, int K, vector<int> &result)
{
    if (root == NULL)
        return -1;

    if (root->data == target)
    {
        collectAtDistance(root, K, result);
        return 0;
    }

    int fromLeft = findTarget(root->left, target, K, result);
    if (fromLeft != -1)
    {
        int dist = fromLeft + 1;
        if (dist == K)
            result.push_back(root->data);
        else
            collectAtDistance(root->right, K - dist - 1, result);
        return dist;
    }

    int fromRight = findTarget(root->right, target, K, result);
    if (fromRight != -1)
    {
        int dist = fromRight + 1;
        if (dist == K)
            result.push_back(root->data);
        else
            collectAtDistance(root->left, K - dist - 1, result);
        return dist;
    }

    return -1;
}

int main()
{
    int N;
    cin >> N;

    vector<int> values(N);
    for (int i = 0; i < N; i++)
    {
        cin >> values[i];
    }

    int target, K;
    cin >> target >> K;

    Node *root = NULL;
    for (int i = 0; i < N; i++)
    {
        root = insertNode(root, values[i]);
    }

    vector<int> result;
    findTarget(root, target, K, result);

    if (result.empty())
    {
        cout << "EMPTY" << endl;
        return 0;
    }

    sort(result.begin(), result.end());
    for (int i = 0; i < (int)result.size(); i++)
    {
        if (i > 0)
            cout << " ";
        cout << result[i];
    }
    cout << endl;

    return 0;
}