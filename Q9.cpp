#include <iostream>
using namespace std;

struct Node
{
    int key;
    int subtreeSize;
    struct Node *left;
    struct Node *right;
};

Node *newNode(int key)
{
    Node *node = new Node;
    node->key = key;
    node->subtreeSize = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

bool contains(Node *root, int key)
{
    while (root != NULL)
    {
        if (root->key == key)
            return true;
        root = (key < root->key) ? root->left : root->right;
    }
    return false;
}

Node *insertKey(Node *root, int key)
{
    if (contains(root, key))
        return root;

    Node *added = newNode(key);
    if (root == NULL)
        return added;

    Node *cur = root;
    while (true)
    {
        cur->subtreeSize++;
        if (key < cur->key)
        {
            if (cur->left == NULL)
            {
                cur->left = added;
                break;
            }
            cur = cur->left;
        }
        else
        {
            if (cur->right == NULL)
            {
                cur->right = added;
                break;
            }
            cur = cur->right;
        }
    }
    return root;
}

Node *deleteKey(Node *root, int key)
{
    if (!contains(root, key))
        return root;

    Node **link = &root;
    while ((*link)->key != key)
    {
        (*link)->subtreeSize--;
        if (key < (*link)->key)
            link = &(*link)->left;
        else
            link = &(*link)->right;
    }

    Node *target = *link;

    if (target->left != NULL && target->right != NULL)
    {
        Node **succLink = &target->right;
        while ((*succLink)->left != NULL)
        {
            (*succLink)->subtreeSize--;
            succLink = &(*succLink)->left;
        }

        Node *successor = *succLink;
        target->key = successor->key;
        target->subtreeSize--;
        *succLink = successor->right;
        delete successor;
    }
    else
    {
        *link = (target->left != NULL) ? target->left : target->right;
        delete target;
    }

    return root;
}

bool kthSmallest(Node *root, int k, int &answer)
{
    if (root == NULL || k > root->subtreeSize)
        return false;

    Node *cur = root;
    while (cur != NULL)
    {
        int leftSize = (cur->left != NULL) ? cur->left->subtreeSize : 0;
        if (k <= leftSize)
        {
            cur = cur->left;
        }
        else if (k == leftSize + 1)
        {
            answer = cur->key;
            return true;
        }
        else
        {
            k -= leftSize + 1;
            cur = cur->right;
        }
    }
    return false;
}

int main()
{
    int Q;
    cin >> Q;

    Node *root = NULL;

    for (int i = 0; i < Q; i++)
    {
        char op;
        int x;
        cin >> op >> x;

        if (op == 'I')
        {
            root = insertKey(root, x);
        }
        else if (op == 'D')
        {
            root = deleteKey(root, x);
        }
        else
        {
            int answer;
            if (kthSmallest(root, x, answer))
                cout << answer << "\n";
            else
                cout << "INVALID\n";
        }
    }

    return 0;
}