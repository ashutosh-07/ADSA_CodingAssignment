#include <iostream>
using namespace std;
#include <queue>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
    struct Node *parent;

    Node(int value)
    {
        data = value;
        left = NULL;
        right = NULL;
        parent = NULL;
    }
};

struct SubtreeInfo {
    bool isBST;
    long long minVal;
    long long maxVal;
    long long sum;
};
Node* buildTree(vector<string>& arr)
{
    if (arr.empty() || arr[0] == "null")
        return NULL;

    Node* root = new Node(stoi(arr[0]));

    queue<Node*> q;
    q.push(root);

    int i = 1;

    while (!q.empty() && i < arr.size())
    {
        Node* current = q.front();
        q.pop();

        // Left child
        if (i < arr.size() && arr[i] != "null")
        {
            current->left = new Node(stoi(arr[i]));
            current->left->parent= current;
            q.push(current->left);
        }

        i++;

        // Right child
        if (i < arr.size() && arr[i] != "null")
        {
            current->right = new Node(stoi(arr[i]));
            current->right->parent = current;
            q.push(current->right);
        }

        i++;
    }

    return root;
}

long long maxContribution = 0;

SubtreeInfo validateAndSumBST(Node* root) {
    if (!root) {
        return {true, INT_MAX, INT_MIN, 0};
    }

    SubtreeInfo left = validateAndSumBST(root->left);
    SubtreeInfo right = validateAndSumBST(root->right);

    if (left.isBST && right.isBST && 
    (root->left == nullptr || left.maxVal < root->data) && 
    (root->right == nullptr || right.minVal > root->data)) {
        
        long long currentSum = root->data + left.sum + right.sum;
        maxContribution = max(maxContribution, currentSum);

        long long currentMin = (root->left) ? left.minVal : root->data;
        long long currentMax = (root->right) ? right.maxVal : root->data;

        if(root->left)
        {
            currentMin = left.minVal;
        }
        else{
            currentMin = root->data;
        }

        if(root->right)
        {
            currentMax = right.maxVal;
        }
        else{
            currentMax = root->data;
        }

        return {true, currentMin, currentMax, currentSum};
    }

    return {false, 0, 0, 0};
}
int main()
{
    int M;
    cin >> M;

    vector<string> arr(M);

    for (int i = 0; i < M; i++)
    {
        cin >> arr[i];
    }

    Node* root = buildTree(arr);

    validateAndSumBST(root);

    cout << maxContribution << endl;
    return 0;
}