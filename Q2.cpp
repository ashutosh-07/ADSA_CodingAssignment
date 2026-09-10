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

Node* checkBalance(Node* startNode, Node* root)
{
    Node* temp = startNode->parent;

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
            Node* rotationPairLeft = temp->left;
            int pairBalance = getBalance(rotationPairLeft);

            if(pairBalance >= 0) // LL
            {
                Node* leftEndNode = rotationPairLeft->left;

                Node* rotationPairLeftRightSubtree = rotationPairLeft->right;

                Node* parent = temp->parent;

                rotationPairLeft->right = temp;
                temp->parent = rotationPairLeft;

                temp->left = rotationPairLeftRightSubtree;
                if(rotationPairLeftRightSubtree)
                    rotationPairLeftRightSubtree->parent = temp;
                
                if(parent)
                {
                    if(parent->right == temp)
                    {
                        parent->right = rotationPairLeft;
                    }
                    else{
                        parent->left = rotationPairLeft;
                    }
                    rotationPairLeft->parent = parent;
                }
                else{
                    root = rotationPairLeft;
                    rotationPairLeft->parent=NULL;
                }
                
                //update heights
                temp->height = 1 + max(
                    temp->left ? temp->left->height : -1,
                    temp->right ? temp->right->height : -1
                );


                leftEndNode->height = 1 + max(
                    leftEndNode->left ? leftEndNode->left->height : -1,
                    leftEndNode->right ? leftEndNode->right->height : -1
                );


                rotationPairLeft->height = 1 + max(
                    rotationPairLeft->left ? rotationPairLeft->left->height : -1,
                    rotationPairLeft->right ? rotationPairLeft->right->height : -1
                );


                temp= rotationPairLeft;
            }
            else // LR
            {
                Node* midToBeNode = rotationPairLeft->right;

                Node* midToBeNodeLeftSubtree = midToBeNode->left;
                Node* midToBeNodeRightSubtree = midToBeNode->right;

                Node* parent = temp->parent;


                midToBeNode->right = temp;
                temp->parent = midToBeNode;

                midToBeNode->left = rotationPairLeft;
                rotationPairLeft->parent = midToBeNode;

                rotationPairLeft->right = midToBeNodeLeftSubtree;
                if(midToBeNodeLeftSubtree)
                    midToBeNodeLeftSubtree->parent = rotationPairLeft;
            
                temp->left = midToBeNodeRightSubtree;
                if(midToBeNodeRightSubtree)
                    midToBeNodeRightSubtree->parent = temp;

                if(parent)
                {
                    if(parent->right == temp)
                    {
                        parent->right = midToBeNode;
                    }
                    else{
                        parent->left = midToBeNode;
                    }
                    midToBeNode->parent = parent;
                }
                else{
                    root = midToBeNode;
                    midToBeNode->parent=NULL;
                }

                //Update heights as well ->first child then parent
                temp->height = 1 + max(
                    temp->left ? temp->left->height : -1,
                    temp->right ? temp->right->height : -1
                );

                rotationPairLeft->height = 1 + max(
                    rotationPairLeft->left ? rotationPairLeft->left->height : -1,
                    rotationPairLeft->right ? rotationPairLeft->right->height : -1
                );

                midToBeNode->height = 1 + max(
                    midToBeNode->left ? midToBeNode->left->height : -1,
                    midToBeNode->right ? midToBeNode->right->height : -1
                );

                temp = midToBeNode; // Move temp to new root of rotated tree
            }
        }
        else if(balance < -1)
        {
            // right heavy
            Node* rotationPairRight = temp->right;

            int pairBalance = getBalance(rotationPairRight);

            if(pairBalance <= 0) // RR
            {
                Node* rightEndNode = rotationPairRight->right;

                Node* rotationPairRightLeftSubtree = rotationPairRight->left;

                Node* parent = temp->parent;

                rotationPairRight->left = temp;
                temp->parent = rotationPairRight;

                temp->right = rotationPairRightLeftSubtree;
                if(rotationPairRightLeftSubtree)
                    rotationPairRightLeftSubtree->parent = temp;
                
                if(parent)
                {
                    if(parent->right == temp)
                    {
                        parent->right = rotationPairRight;
                    }
                    else{
                        parent->left = rotationPairRight;
                    }
                    rotationPairRight->parent = parent;
                }
                else{
                    root = rotationPairRight;
                    rotationPairRight->parent=NULL;
                }
                
                //update heights
                temp->height = 1 + max(
                    temp->left ? temp->left->height : -1,
                    temp->right ? temp->right->height : -1
                );


                rightEndNode->height = 1 + max(
                    rightEndNode->left ? rightEndNode->left->height : -1,
                    rightEndNode->right ? rightEndNode->right->height : -1
                );


                rotationPairRight->height = 1 + max(
                    rotationPairRight->left ? rotationPairRight->left->height : -1,
                    rotationPairRight->right ? rotationPairRight->right->height : -1
                );


                temp= rotationPairRight;
            }
            else // RL
            {

                Node* midToBeNode = rotationPairRight->left;

                Node* midToBeNodeLeftSubtree = midToBeNode->left;
                Node* midToBeNodeRightSubtree = midToBeNode->right;

                Node* parent = temp->parent;


                midToBeNode->left = temp;
                temp->parent = midToBeNode;
                midToBeNode->right = rotationPairRight;
                rotationPairRight->parent = midToBeNode;

                rotationPairRight->left = midToBeNodeRightSubtree;
                if(midToBeNodeRightSubtree)
                    midToBeNodeRightSubtree->parent = rotationPairRight;
            
                temp->right = midToBeNodeLeftSubtree;
                if(midToBeNodeLeftSubtree)
                    midToBeNodeLeftSubtree->parent = temp;

                if(parent)
                {
                    if(parent->right == temp)
                    {
                        parent->right = midToBeNode;
                    }
                    else{
                        parent->left = midToBeNode;
                    }
                    midToBeNode->parent = parent;
                }
                else{
                    root = midToBeNode;
                    midToBeNode->parent=NULL;
                }

                //Update heights as well ->first child then parent
                temp->height = 1 + max(
                    temp->left ? temp->left->height : -1,
                    temp->right ? temp->right->height : -1
                );

                rotationPairRight->height = 1 + max(
                    rotationPairRight->left ? rotationPairRight->left->height : -1,
                    rotationPairRight->right ? rotationPairRight->right->height : -1
                );

                midToBeNode->height = 1 + max(
                    midToBeNode->left ? midToBeNode->left->height : -1,
                    midToBeNode->right ? midToBeNode->right->height : -1
                );

                temp = midToBeNode; // Move temp to new root of rotated tree
            }
        }

        temp = temp->parent;
    }
    return root;
}

Node *insert(Node *root, int key)
{

    if (root == NULL)
    {
        root = new Node(key);
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
    Node* newNode = new Node(key);

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

    root = checkBalance(newNode, root);

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
                root = checkBalance(temp, root);
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
                return checkBalance(temp, root);

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

                root = checkBalance(temp, root);
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
    //Added comment inside main
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

    //Search
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
            root = insert(root, key);
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
            root  = deleteNode(root, key);
            printStructure(root);
        }
        else
        {
            cout << "Key not found" << endl;
        }
    }
}