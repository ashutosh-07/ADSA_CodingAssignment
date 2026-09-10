#include <iostream>
using namespace std;
#include <queue>

// Structure of the node
struct Node
{
    int data;
    int height;
    struct Node *left;
    struct Node *right;
    struct Node *parent;

    Node(int value)
    {
        data = value;
        height = 0;
        left = NULL;
        right = NULL;
        parent = NULL;
    }
};


Node *search(Node *root, int key)
{

    while (root != NULL)
    {
        if (root->data == key)
        {
            
            return root;
            // found the key
        }
        else if (root->data > key)
        {
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }
    return NULL;
}

Node *insert(Node *root, int key)
{

    if (root == NULL)
    {
        Node *root = new Node(key);
        return root;
    }
    Node *temp = root;
    Node *prev = NULL;
    while (temp != NULL)
    {
        prev = temp;
        if (temp->data > key)
        {
            // cout<<"root is greater going left"<<endl;
            temp = temp->left;
        }
        else if (temp->data < key)
        {
            // cout<<"root is smaller going right"<<endl;
            temp = temp->right;
        }
        else
        {
            cout << "Duplicate key";
            return root;
        }
    }
    Node *newNode = new Node(key);

    if (key > prev->data)
    {
        prev->right = newNode;
        newNode->parent = prev;
    }
    else
    {
        prev->left = newNode;
        newNode->parent = prev;
    }

    //Need to add logic for checking balancing

    return root;
}

int getBalance(Node* node)
{
    if (node == NULL)
        return 0;

    int leftHeight = -1;
    int rightHeight = -1;

    if (node->left)
        leftHeight = node->left->height;

    if (node->right)
        rightHeight = node->right->height;

    return leftHeight - rightHeight;
}

void checkBalance(Node* insertedNode, Node* root)
{
    Node* temp = insertedNode->parent;

    while(temp != NULL)
    {
        int leftHeight = -1;
        int rightHeight = -1;

        if(temp->left)
        {
            leftHeight = temp->left->height;
        }
        if(temp->right)
        {
            rightHeight = temp->right->height;
        }
        temp->height = 1 + max(leftHeight, rightHeight);

        int balance = leftHeight - rightHeight;

        if(balance > 1)
        {
            // left heavy
            Node* rotationPair = temp->left;
            int pairBalance = getBalance(rotationPair);

            if(pairBalance >= 0)
            {
                // LL
            }
            else
            {
                // LR
            }
        }
        else if(balance < -1)
        {
            // right heavy
            Node* rotationPair = temp->right;

            int pairBalance = getBalance(rotationPair);

            if(pairBalance <= 0)
            {
                // RR
            }
            else
            {
                // RL
            }
        }

        temp = temp->parent;
    }
}

void printInOrder(Node *root)
{
    if (root == NULL)
        return;

    printInOrder(root->left);

    cout << root->data << " ";

    printInOrder(root->right);
}
void printPreOrder(Node *root)
{
    if (root == NULL)
        return;

    cout << root->data << " ";

    printPreOrder(root->left);
    printPreOrder(root->right);
}
void printLevelOrder(Node *root)
{
    queue<vector<Node *>> q;

    vector<Node *> v;
    v.push_back(root);
    q.push(v);

    while (!q.empty())
    {
        vector<Node *> v = q.front();
        vector<Node *> res;
        q.pop();
        for (int i = 0; i < v.size(); i++)
        {
            Node *temp = v[i];

            cout << temp->data << " ";
            if (temp->left != NULL)
            {
                res.push_back(temp->left);
            }
            if (temp->right != NULL)
            {
                res.push_back(temp->right);
            }
        }

        if (res.size() > 0)
        {
            q.push(res);
        }
        cout << endl;
    }
}
void printStructure(Node *root)
{
    cout << "INORDER: ";
    printInOrder(root);
    cout << endl;
    cout << "PREORDER: ";
    printPreOrder(root);
    cout << endl;
    cout << "LEVELORDER: " << endl;
    printLevelOrder(root);
    cout << "END" << endl;
}


int main()
{
    Node *root;

    // Build Initial_BST
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        int key;
        cin >> key;
        // call function to insert this key
        if (i == 0)
        {
            root = insert(NULL, key);
        }
        else
        {
            root = insert(root, key);
        }
    }

    cout << "INITIAL TREE" << endl;
    printStructure(root);

    // Search
    // int S;
    // cin >> S;
    // for (int i = 0; i < S; i++)
    // {
    //     int key;
    //     cin >> key;
    //     // call function to search this key
    //     cout << "SEARCH " << key << ": ";
    //     if(search(root, key)==NULL){
    //         cout << "Key not found" << endl;
    //     }
    //     else{
    //         cout << "Key found" << endl;
    //     }
    // }

    // Insert
    // int I;
    // cin >> I;
    // for (int i = 0; i < I; i++)
    // {
    //     int key;
    //     cin >> key;
    //     // call function to Insert this key
    //     cout << "INSERT " << key << endl;
    //     if (search(root, key)==NULL)
    //     {
    //         insert(root, key);
    //         printStructure(root);
            
    //     }
    //     else
    //     {
    //         cout << "Duplicate key" << endl;
    //     }
    // }
    // Delete

    //Comment down for TC 1
    // int D;
    // cin >> D;

    // for (int i = 0; i < D; i++)
    // {
    //     int key;
    //     cin >> key;
    //     // call function to Insert this key
    //     cout << "DELETE " << key << endl;
    //     if (search(root, key)!=NULL)
    //     {
    //         deleteNode(root, key);
    //         printStructure(root);
    //     }
    //     else
    //     {
    //         cout << "Key not found" << endl;
    //     }
    // }
}