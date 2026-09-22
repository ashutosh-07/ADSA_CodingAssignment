#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

const long long BASE = 1000000000;

struct Node
{
    int data;
    Node *left;
    Node *right;

    Node(int value)
    {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

Node *insertNode(Node *root, int key)
{
    if (root == nullptr)
        return new Node(key);

    Node *cur = root;
    while (true)
    {
        if (key < cur->data)
        {
            if (cur->left == nullptr)
            {
                cur->left = new Node(key);
                break;
            }
            cur = cur->left;
        }
        else
        {
            if (cur->right == nullptr)
            {
                cur->right = new Node(key);
                break;
            }
            cur = cur->right;
        }
    }
    return root;
}

int collectSizes(Node *root, vector<int> &sizes)
{
    if (root == nullptr)
        return 0;

    int total = 1 + collectSizes(root->left, sizes) + collectSizes(root->right, sizes);
    sizes.push_back(total);
    return total;
}

void multiplySmall(vector<long long> &num, int x)
{
    long long carry = 0;
    for (size_t i = 0; i < num.size(); i++)
    {
        long long cur = num[i] * x + carry;
        num[i] = cur % BASE;
        carry = cur / BASE;
    }
    while (carry > 0)
    {
        num.push_back(carry % BASE);
        carry /= BASE;
    }
}

void divideSmall(vector<long long> &num, int x)
{
    long long rem = 0;
    for (int i = (int)num.size() - 1; i >= 0; i--)
    {
        long long cur = num[i] + rem * BASE;
        num[i] = cur / x;
        rem = cur % x;
    }
    while (num.size() > 1 && num.back() == 0)
        num.pop_back();
}

void subtractOne(vector<long long> &num)
{
    size_t i = 0;
    while (num[i] == 0)
    {
        num[i] = BASE - 1;
        i++;
    }
    num[i]--;
    while (num.size() > 1 && num.back() == 0)
        num.pop_back();
}

int main()
{
    int n;
    cin >> n;

    Node *root = nullptr;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        root = insertNode(root, x);
    }

    vector<int> sizes;
    collectSizes(root, sizes);

    vector<long long> num(1, 1);
    for (int i = 2; i <= n; i++)
    {
        multiplySmall(num, i);
    }

    for (size_t i = 0; i < sizes.size(); i++)
    {
        divideSmall(num, sizes[i]);
    }

    subtractOne(num);

    printf("%lld", num.back());
    for (int i = (int)num.size() - 2; i >= 0; i--)
    {
        printf("%09lld", num[i]);
    }
    printf("\n");

    return 0;
}