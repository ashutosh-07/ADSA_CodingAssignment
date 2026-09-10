#include <iostream>
using namespace std;
#include <queue>

// Structure of the node
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

    return root;
}

Node *deleteNode(Node *root, int key)
{

    Node *temp = root;

    while (temp != NULL)
    {
        if (temp->data == key)
        {
            // Need to find the sort of Node(leaf, Internal with 1 child, Internal with 2 child)
            if (temp->right == NULL && temp->left == NULL) //leaf
            {
                //if we are deleting the root node
                if (temp->parent == NULL)
                {
                    delete temp;
                    return NULL;
                }
                Node* parentNode = temp->parent;
                if(parentNode->left== temp)
                {
                    parentNode->left = NULL;
                }
                else{
                    parentNode->right = NULL;
                }
                delete temp;
                return root;
            }
            else if(temp->right != NULL && temp->left != NULL) //internal with 2 child
            {
                //When deleting replace it with inorder successor which is in right subtree
                Node* rightRoot = temp->right;

                while(rightRoot!=NULL && rightRoot->left != NULL)
                {
                    rightRoot = rightRoot->left;
                }
                temp->data = rightRoot->data;

                temp->right = deleteNode(temp->right, rightRoot->data);

            }
            else //internal node with 1 child
            {
                Node* childNode;
                if(temp->right==NULL)
                {
                    childNode = temp->left;
                }
                else
                {
                    childNode = temp->right;
                }

                //edge case when we are deleting the root node
                if (temp->parent == NULL)
                {
                    childNode->parent = NULL;
                    delete temp;
                    return childNode;
                }

                Node* parentNode = temp->parent;
                if(parentNode->left == temp)
                {
                    parentNode->left = childNode;
                }
                else{
                    parentNode->right = childNode;
                }
                childNode->parent = parentNode;

                delete temp;
                return root;
            }
        }
        else if (temp->data > key)
        {
            temp = temp->left;
        }
        else
        {
            temp = temp->right;
        }
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
    int S;
    cin >> S;
    for (int i = 0; i < S; i++)
    {
        int key;
        cin >> key;
        // call function to search this key
        cout << "SEARCH " << key << ": ";
        if(search(root, key)==NULL){
            cout << "Key not found" << endl;
        }
        else{
            cout << "Key found" << endl;
        }
    }

    // Insert
    int I;
    cin >> I;
    for (int i = 0; i < I; i++)
    {
        int key;
        cin >> key;
        // call function to Insert this key
        cout << "INSERT " << key << endl;
        if (search(root, key)==NULL)
        {
            root  = insert(root, key);
            printStructure(root);
            
        }
        else
        {
            cout << "Duplicate key" << endl;
        }
    }
    // Delete

    //Comment down for TC 1
    int D;
    cin >> D;

    for (int i = 0; i < D; i++)
    {
        int key;
        cin >> key;
        // call function to Insert this key
        cout << "DELETE " << key << endl;
        if (search(root, key)!=NULL)
        {
            root = deleteNode(root, key);
            printStructure(root);
        }
        else
        {
            cout << "Key not found" << endl;
        }
    }
}
