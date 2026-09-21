#include <iostream>
using namespace std;
#include <queue>

// Structure of the node
struct Node
{
    int data;
    bool color;
    struct Node *left;
    struct Node *right;
    struct Node *parent;

    Node(int value)
    {
        color = 1; //1 for red 0 for black
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

Node* fixInsert(Node *root, Node* newNode)
{
    
    while(newNode->parent != NULL && newNode->parent->color == 1)//red parent
    {
        Node *parent = newNode->parent;
        if(parent->color == 0) //parent is black so we are fine
        {
            return root;
        }
        else{//parent is red need to check uncle as well now

            Node* grandParent = parent->parent;
            Node* uncle;
            if(grandParent->left== parent)
            {
                uncle  = grandParent->right;
            }
            else{
                uncle = grandParent->left;
            }

            if(uncle && uncle->color== 1)// uncle color is red
            {
                uncle->color = 0;
                parent->color = 0;
                grandParent->color = 1;
                newNode  = grandParent;

            }
            else{ //either uncle is not present or uncle is black

                // use avl code for LL, RR, LR, RL rotation followed by recoration
                //RR rotation
                if(grandParent->right == parent && parent->right == newNode)
                {
                    Node* parentLeft =  parent->left;
                    Node* greatGrandParent = grandParent->parent;
                    if(greatGrandParent == NULL)
                    {
                        root = parent;
                        parent->parent = NULL;
                    }
                    else
                    {
                        if(greatGrandParent->right == grandParent)
                            greatGrandParent->right = parent;
                        else
                            greatGrandParent->left = parent;

                        parent->parent = greatGrandParent;
                    }

                    grandParent->parent = parent;
                    parent->left = grandParent;
                    grandParent->right = parentLeft;

                    if(parentLeft)
                    {
                        parentLeft->parent = grandParent;
                    }
                    parent->color = 0;
                    grandParent->color = 1;
                    return root;
                }
                //LL
                else if(grandParent->left == parent && parent->left == newNode)
                {
                    Node* parentRight =  parent->right;
                    Node* greatGrandParent = grandParent->parent;
                    if(greatGrandParent == NULL)
                    {
                        root = parent;
                        parent->parent = NULL;
                    }
                    else
                    {
                        if(greatGrandParent->right == grandParent)
                            greatGrandParent->right = parent;
                        else
                            greatGrandParent->left = parent;

                        parent->parent = greatGrandParent;
                    }

                    grandParent->parent = parent;
                    parent->right = grandParent;
                    grandParent->left = parentRight;

                    if(parentRight)
                    {
                        parentRight->parent = grandParent;
                    }
                    parent->color = 0;
                    grandParent->color = 1;
                    return root;
                }
                //LR
                else if(grandParent->left == parent && parent->right == newNode)
                {
                    Node* newNodeLeft = newNode->left;
                    Node* newNodeRight = newNode->right;
                    Node* greatGrandParent = grandParent->parent;
                    if(greatGrandParent == NULL)
                    {
                        root = newNode;
                        newNode->parent = NULL;
                    }
                    else
                    {
                        if(greatGrandParent->right == grandParent)
                            greatGrandParent->right = newNode;
                        else
                            greatGrandParent->left = newNode;

                        newNode->parent = greatGrandParent;
                    }

                    grandParent->parent = newNode;
                    newNode->right = grandParent;
                    parent->parent = newNode;
                    newNode->left = parent;

                    parent->right = newNodeLeft;
                    grandParent->left = newNodeRight;
                    if(newNodeLeft)
                        newNodeLeft->parent = parent;

                    if(newNodeRight)
                        newNodeRight->parent = grandParent;
                    newNode->color = 0;
                    grandParent->color = 1;
                    parent->color = 1;
                    return root;
                }
                //RL
                else{
                    Node* newNodeLeft = newNode->left;
                    Node* newNodeRight = newNode->right;
                    Node* greatGrandParent = grandParent->parent;
                    if(greatGrandParent == NULL)
                    {
                        root = newNode;
                        newNode->parent = NULL;
                    }
                    else
                    {
                        if(greatGrandParent->right == grandParent)
                            greatGrandParent->right = newNode;
                        else
                            greatGrandParent->left = newNode;

                        newNode->parent = greatGrandParent;
                    }
                    grandParent->parent = newNode;
                    newNode->left = grandParent;
                    parent->parent = newNode;
                    newNode->right = parent;

                    parent->left = newNodeRight;
                    grandParent->right = newNodeLeft;
                    if(newNodeLeft)
                        newNodeLeft->parent = grandParent;

                    if(newNodeRight)
                        newNodeRight->parent = parent;
                    newNode->color = 0;
                    grandParent->color = 1;
                    parent->color = 1;
                    return root;

                }
            }
        }
    }
    root->color = 0;
    return root;
    
}

Node *insert(Node *root, int key)
{

    if (root == NULL)
    {
        Node* newNode = new Node(key);
        newNode->color = 0;
        return newNode;
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

    root = fixInsert(root, newNode);

    return root;
}


// x is a BLACK leaf that is about to be deleted. It is still attached to the tree
// and acts as the "double black" node. Fixes black heights, returns the (possibly new) root.
Node* fixDelete(Node* root, Node* x)
{
    while(x != root)
    {
        Node* parent = x->parent;
        Node* grandParent = parent->parent;
        Node* sibling;
        Node* nearChild;
        Node* farChild;
 
        if(parent->left == x)
        {
            // ---------- x is the LEFT child ----------
            sibling = parent->right;
 
            // Case 1: sibling is red -> rotate left at parent, swap colors, get a black sibling
            if(sibling->color == 1)
            {
                nearChild = sibling->left;
 
                if(grandParent == NULL)
                {
                    root = sibling;
                    sibling->parent = NULL;
                }
                else
                {
                    if(grandParent->left == parent)
                        grandParent->left = sibling;
                    else
                        grandParent->right = sibling;
                    sibling->parent = grandParent;
                }
 
                sibling->left = parent;
                parent->parent = sibling;
                parent->right = nearChild;
                if(nearChild)
                    nearChild->parent = parent;
 
                sibling->color = 0;
                parent->color = 1;
 
                // x's new sibling is the old near child (black), grandParent changed too
                sibling = parent->right;
                grandParent = parent->parent;
            }
 
            nearChild = sibling->left;
            farChild = sibling->right;
 
            bool nearRed = (nearChild != NULL && nearChild->color == 1);
            bool farRed = (farChild != NULL && farChild->color == 1);
 
            // Case 2: sibling black, both nephews black
            if(!nearRed && !farRed)
            {
                sibling->color = 1;
                if(parent->color == 1)
                {
                    parent->color = 0;
                    return root;
                }
                x = parent; // deficit moves up
            }
            else
            {
                // Case 3: near red, far black -> rotate right at sibling, becomes case 4
                if(!farRed)
                {
                    Node* nearChildRight = nearChild->right;
 
                    parent->right = nearChild;
                    nearChild->parent = parent;
                    nearChild->right = sibling;
                    sibling->parent = nearChild;
                    sibling->left = nearChildRight;
                    if(nearChildRight)
                        nearChildRight->parent = sibling;
 
                    nearChild->color = 0;
                    sibling->color = 1;
 
                    sibling = nearChild;
                    farChild = sibling->right; // the old sibling, red
                }
 
                // Case 4: far red -> rotate left at parent
                Node* siblingLeft = sibling->left;
 
                if(grandParent == NULL)
                {
                    root = sibling;
                    sibling->parent = NULL;
                }
                else
                {
                    if(grandParent->left == parent)
                        grandParent->left = sibling;
                    else
                        grandParent->right = sibling;
                    sibling->parent = grandParent;
                }
 
                sibling->left = parent;
                parent->parent = sibling;
                parent->right = siblingLeft;
                if(siblingLeft)
                    siblingLeft->parent = parent;
 
                sibling->color = parent->color;
                parent->color = 0;
                farChild->color = 0;
                return root;
            }
        }
        else
        {
            // ---------- x is the RIGHT child (mirror) ----------
            sibling = parent->left;
 
            // Case 1: sibling is red -> rotate right at parent
            if(sibling->color == 1)
            {
                nearChild = sibling->right;
 
                if(grandParent == NULL)
                {
                    root = sibling;
                    sibling->parent = NULL;
                }
                else
                {
                    if(grandParent->left == parent)
                        grandParent->left = sibling;
                    else
                        grandParent->right = sibling;
                    sibling->parent = grandParent;
                }
 
                sibling->right = parent;
                parent->parent = sibling;
                parent->left = nearChild;
                if(nearChild)
                    nearChild->parent = parent;
 
                sibling->color = 0;
                parent->color = 1;
 
                sibling = parent->left;
                grandParent = parent->parent;
            }
 
            nearChild = sibling->right;
            farChild = sibling->left;
 
            bool nearRed = (nearChild != NULL && nearChild->color == 1);
            bool farRed = (farChild != NULL && farChild->color == 1);
 
            // Case 2
            if(!nearRed && !farRed)
            {
                sibling->color = 1;
                if(parent->color == 1)
                {
                    parent->color = 0;
                    return root;
                }
                x = parent;
            }
            else
            {
                // Case 3: near red, far black -> rotate left at sibling
                if(!farRed)
                {
                    Node* nearChildLeft = nearChild->left;
 
                    parent->left = nearChild;
                    nearChild->parent = parent;
                    nearChild->left = sibling;
                    sibling->parent = nearChild;
                    sibling->right = nearChildLeft;
                    if(nearChildLeft)
                        nearChildLeft->parent = sibling;
 
                    nearChild->color = 0;
                    sibling->color = 1;
 
                    sibling = nearChild;
                    farChild = sibling->left; // the old sibling, red
                }
 
                // Case 4: far red -> rotate right at parent
                Node* siblingRight = sibling->right;
 
                if(grandParent == NULL)
                {
                    root = sibling;
                    sibling->parent = NULL;
                }
                else
                {
                    if(grandParent->left == parent)
                        grandParent->left = sibling;
                    else
                        grandParent->right = sibling;
                    sibling->parent = grandParent;
                }
 
                sibling->right = parent;
                parent->parent = sibling;
                parent->left = siblingRight;
                if(siblingRight)
                    siblingRight->parent = parent;
 
                sibling->color = parent->color;
                parent->color = 0;
                farChild->color = 0;
                return root;
            }
        }
    }
    return root; // x reached the root, extra black just disappears
}
 
Node *deleteNode(Node *root, int key)
{
    // find the node
    Node *temp = root;
    while(temp != NULL && temp->data != key)
    {
        if(temp->data > key)
            temp = temp->left;
        else
            temp = temp->right;
    }
    if(temp == NULL)
        return root;
 
    // two children: copy inorder successor's data, then remove the successor node
    if(temp->left != NULL && temp->right != NULL)
    {
        Node* successor = temp->right;
        while(successor->left != NULL)
            successor = successor->left;
        temp->data = successor->data;
        temp = successor; // temp is now the node that physically leaves the tree
    }
 
    // temp has at most one child now
    if(temp->left == NULL && temp->right == NULL) // leaf
    {
        if(temp->parent == NULL) // only node in the tree
        {
            delete temp;
            return NULL;
        }
 
        if(temp->color == 0) // black leaf: fix black heights while it is still attached
        {
            root = fixDelete(root, temp);
        }
 
        Node* parentNode = temp->parent; // x always stays a child of the same parent during the fix
        if(parentNode->left == temp)
            parentNode->left = NULL;
        else
            parentNode->right = NULL;
    }
    else // one child: temp is black and the child is red
    {
        Node* childNode;
        if(temp->left != NULL)
            childNode = temp->left;
        else
            childNode = temp->right;
 
        Node* parentNode = temp->parent;
        childNode->parent = parentNode;
        if(parentNode == NULL)
            root = childNode;
        else if(parentNode->left == temp)
            parentNode->left = childNode;
        else
            parentNode->right = childNode;
 
        childNode->color = 0;
    }
 
    delete temp;
    return root;
}

void printInOrder(Node *root)
{
    if (root == NULL)
        return;

    printInOrder(root->left);

    cout << root->data;
    if(root->color)
    {
        cout<<"(R)"<<" ";
    }
    else{
        cout<<"(B)"<<" ";
    }

    printInOrder(root->right);
}
void printPreOrder(Node *root)
{
    if (root == NULL)
        return;

    cout << root->data;
    if(root->color)
    {
        cout<<"(R)"<<" ";
    }
    else{
        cout<<"(B)"<<" ";
    }

    printPreOrder(root->left);
    printPreOrder(root->right);
}
void printLevelOrder(Node *root)
{
    if(root == NULL)
        return;
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

            cout << temp->data;
            if(temp->color)
            {
                cout<<"(R)"<<" ";
            }
            else{
                cout<<"(B)"<<" ";
            }

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
       //printLevelOrder(root);
        //cout<<endl;
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

    //Insert
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