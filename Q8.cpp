#include <iostream>
#include <algorithm>
using namespace std;

namespace avl
{
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

    int getBalance(Node *node)
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

    Node *checkBalance(Node *startNode, Node *root)
    {
        Node *temp = startNode->parent;

        while (temp != NULL)
        {
            int leftHeight = -1;
            int rightHeight = -1;

            if (temp->left)
            {
                leftHeight = temp->left->height;
            }
            if (temp->right)
            {
                rightHeight = temp->right->height;
            }
            temp->height = 1 + max(leftHeight, rightHeight);

            int balance = leftHeight - rightHeight;

            if (balance > 1)
            {
                // left heavy
                Node *rotationPairLeft = temp->left;
                int pairBalance = getBalance(rotationPairLeft);

                if (pairBalance >= 0) // LL
                {
                    Node *leftEndNode = rotationPairLeft->left;

                    Node *rotationPairLeftRightSubtree = rotationPairLeft->right;

                    Node *parent = temp->parent;

                    rotationPairLeft->right = temp;
                    temp->parent = rotationPairLeft;

                    temp->left = rotationPairLeftRightSubtree;
                    if (rotationPairLeftRightSubtree)
                        rotationPairLeftRightSubtree->parent = temp;

                    if (parent)
                    {
                        if (parent->right == temp)
                        {
                            parent->right = rotationPairLeft;
                        }
                        else
                        {
                            parent->left = rotationPairLeft;
                        }
                        rotationPairLeft->parent = parent;
                    }
                    else
                    {
                        root = rotationPairLeft;
                        rotationPairLeft->parent = NULL;
                    }

                    // update heights
                    temp->height = 1 + max(
                                           temp->left ? temp->left->height : -1,
                                           temp->right ? temp->right->height : -1);

                    leftEndNode->height = 1 + max(
                                                  leftEndNode->left ? leftEndNode->left->height : -1,
                                                  leftEndNode->right ? leftEndNode->right->height : -1);

                    rotationPairLeft->height = 1 + max(
                                                       rotationPairLeft->left ? rotationPairLeft->left->height : -1,
                                                       rotationPairLeft->right ? rotationPairLeft->right->height : -1);

                    temp = rotationPairLeft;
                }
                else // LR
                {
                    Node *midToBeNode = rotationPairLeft->right;

                    Node *midToBeNodeLeftSubtree = midToBeNode->left;
                    Node *midToBeNodeRightSubtree = midToBeNode->right;

                    Node *parent = temp->parent;

                    midToBeNode->right = temp;
                    temp->parent = midToBeNode;

                    midToBeNode->left = rotationPairLeft;
                    rotationPairLeft->parent = midToBeNode;

                    rotationPairLeft->right = midToBeNodeLeftSubtree;
                    if (midToBeNodeLeftSubtree)
                        midToBeNodeLeftSubtree->parent = rotationPairLeft;

                    temp->left = midToBeNodeRightSubtree;
                    if (midToBeNodeRightSubtree)
                        midToBeNodeRightSubtree->parent = temp;

                    if (parent)
                    {
                        if (parent->right == temp)
                        {
                            parent->right = midToBeNode;
                        }
                        else
                        {
                            parent->left = midToBeNode;
                        }
                        midToBeNode->parent = parent;
                    }
                    else
                    {
                        root = midToBeNode;
                        midToBeNode->parent = NULL;
                    }

                    // Update heights as well ->first child then parent
                    temp->height = 1 + max(
                                           temp->left ? temp->left->height : -1,
                                           temp->right ? temp->right->height : -1);

                    rotationPairLeft->height = 1 + max(
                                                       rotationPairLeft->left ? rotationPairLeft->left->height : -1,
                                                       rotationPairLeft->right ? rotationPairLeft->right->height : -1);

                    midToBeNode->height = 1 + max(
                                                  midToBeNode->left ? midToBeNode->left->height : -1,
                                                  midToBeNode->right ? midToBeNode->right->height : -1);

                    temp = midToBeNode; // Move temp to new root of rotated tree
                }
            }
            else if (balance < -1)
            {
                // right heavy
                Node *rotationPairRight = temp->right;

                int pairBalance = getBalance(rotationPairRight);

                if (pairBalance <= 0) // RR
                {
                    Node *rightEndNode = rotationPairRight->right;

                    Node *rotationPairRightLeftSubtree = rotationPairRight->left;

                    Node *parent = temp->parent;

                    rotationPairRight->left = temp;
                    temp->parent = rotationPairRight;

                    temp->right = rotationPairRightLeftSubtree;
                    if (rotationPairRightLeftSubtree)
                        rotationPairRightLeftSubtree->parent = temp;

                    if (parent)
                    {
                        if (parent->right == temp)
                        {
                            parent->right = rotationPairRight;
                        }
                        else
                        {
                            parent->left = rotationPairRight;
                        }
                        rotationPairRight->parent = parent;
                    }
                    else
                    {
                        root = rotationPairRight;
                        rotationPairRight->parent = NULL;
                    }

                    // update heights
                    temp->height = 1 + max(
                                           temp->left ? temp->left->height : -1,
                                           temp->right ? temp->right->height : -1);

                    rightEndNode->height = 1 + max(
                                                   rightEndNode->left ? rightEndNode->left->height : -1,
                                                   rightEndNode->right ? rightEndNode->right->height : -1);

                    rotationPairRight->height = 1 + max(
                                                        rotationPairRight->left ? rotationPairRight->left->height : -1,
                                                        rotationPairRight->right ? rotationPairRight->right->height : -1);

                    temp = rotationPairRight;
                }
                else // RL
                {

                    Node *midToBeNode = rotationPairRight->left;

                    Node *midToBeNodeLeftSubtree = midToBeNode->left;
                    Node *midToBeNodeRightSubtree = midToBeNode->right;

                    Node *parent = temp->parent;

                    midToBeNode->left = temp;
                    temp->parent = midToBeNode;
                    midToBeNode->right = rotationPairRight;
                    rotationPairRight->parent = midToBeNode;

                    rotationPairRight->left = midToBeNodeRightSubtree;
                    if (midToBeNodeRightSubtree)
                        midToBeNodeRightSubtree->parent = rotationPairRight;

                    temp->right = midToBeNodeLeftSubtree;
                    if (midToBeNodeLeftSubtree)
                        midToBeNodeLeftSubtree->parent = temp;

                    if (parent)
                    {
                        if (parent->right == temp)
                        {
                            parent->right = midToBeNode;
                        }
                        else
                        {
                            parent->left = midToBeNode;
                        }
                        midToBeNode->parent = parent;
                    }
                    else
                    {
                        root = midToBeNode;
                        midToBeNode->parent = NULL;
                    }

                    // Update heights as well ->first child then parent
                    temp->height = 1 + max(
                                           temp->left ? temp->left->height : -1,
                                           temp->right ? temp->right->height : -1);

                    rotationPairRight->height = 1 + max(
                                                        rotationPairRight->left ? rotationPairRight->left->height : -1,
                                                        rotationPairRight->right ? rotationPairRight->right->height : -1);

                    midToBeNode->height = 1 + max(
                                                  midToBeNode->left ? midToBeNode->left->height : -1,
                                                  midToBeNode->right ? midToBeNode->right->height : -1);

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

        // Need to add logic for checking balancing

        root = checkBalance(newNode, root);

        return root;
    }

    Node *deleteNode(Node *root, int key)
    {
        Node *temp = search(root, key);
        if (temp == NULL)
            return root;

        // two children: copy the inorder successor's key, then remove the successor node instead
        if (temp->left != NULL && temp->right != NULL)
        {
            Node *successor = temp->right;
            while (successor->left != NULL)
                successor = successor->left;
            temp->data = successor->data;
            temp = successor;
        }

        // temp now has at most one child
        Node *childNode = (temp->left != NULL) ? temp->left : temp->right;
        Node *parentNode = temp->parent;

        if (childNode != NULL)
            childNode->parent = parentNode;

        if (parentNode == NULL)
            root = childNode;
        else if (parentNode->left == temp)
            parentNode->left = childNode;
        else
            parentNode->right = childNode;

        if (parentNode != NULL)
            root = checkBalance(temp, root); // walks up from temp->parent

        delete temp;
        return root;
    }
}

namespace rb
{
    struct Node
    {
        int data;
        bool color;
        struct Node *left;
        struct Node *right;
        struct Node *parent;

        Node(int value)
        {
            color = 1; // 1 for red 0 for black
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

    Node *fixInsert(Node *root, Node *newNode)
    {

        while (newNode->parent != NULL && newNode->parent->color == 1) // red parent
        {
            Node *parent = newNode->parent;
            if (parent->color == 0) // parent is black so we are fine
            {
                return root;
            }
            else
            { // parent is red need to check uncle as well now

                Node *grandParent = parent->parent;
                Node *uncle;
                if (grandParent->left == parent)
                {
                    uncle = grandParent->right;
                }
                else
                {
                    uncle = grandParent->left;
                }

                if (uncle && uncle->color == 1) // uncle color is red
                {
                    uncle->color = 0;
                    parent->color = 0;
                    grandParent->color = 1;
                    newNode = grandParent;
                }
                else
                { // either uncle is not present or uncle is black

                    // use avl code for LL, RR, LR, RL rotation followed by recoration
                    // RR rotation
                    if (grandParent->right == parent && parent->right == newNode)
                    {
                        Node *parentLeft = parent->left;
                        Node *greatGrandParent = grandParent->parent;
                        if (greatGrandParent == NULL)
                        {
                            root = parent;
                            parent->parent = NULL;
                        }
                        else
                        {
                            if (greatGrandParent->right == grandParent)
                                greatGrandParent->right = parent;
                            else
                                greatGrandParent->left = parent;

                            parent->parent = greatGrandParent;
                        }

                        grandParent->parent = parent;
                        parent->left = grandParent;
                        grandParent->right = parentLeft;

                        if (parentLeft)
                        {
                            parentLeft->parent = grandParent;
                        }
                        parent->color = 0;
                        grandParent->color = 1;
                        return root;
                    }
                    // LL
                    else if (grandParent->left == parent && parent->left == newNode)
                    {
                        Node *parentRight = parent->right;
                        Node *greatGrandParent = grandParent->parent;
                        if (greatGrandParent == NULL)
                        {
                            root = parent;
                            parent->parent = NULL;
                        }
                        else
                        {
                            if (greatGrandParent->right == grandParent)
                                greatGrandParent->right = parent;
                            else
                                greatGrandParent->left = parent;

                            parent->parent = greatGrandParent;
                        }

                        grandParent->parent = parent;
                        parent->right = grandParent;
                        grandParent->left = parentRight;

                        if (parentRight)
                        {
                            parentRight->parent = grandParent;
                        }
                        parent->color = 0;
                        grandParent->color = 1;
                        return root;
                    }
                    // LR
                    else if (grandParent->left == parent && parent->right == newNode)
                    {
                        Node *newNodeLeft = newNode->left;
                        Node *newNodeRight = newNode->right;
                        Node *greatGrandParent = grandParent->parent;
                        if (greatGrandParent == NULL)
                        {
                            root = newNode;
                            newNode->parent = NULL;
                        }
                        else
                        {
                            if (greatGrandParent->right == grandParent)
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
                        if (newNodeLeft)
                            newNodeLeft->parent = parent;

                        if (newNodeRight)
                            newNodeRight->parent = grandParent;
                        newNode->color = 0;
                        grandParent->color = 1;
                        parent->color = 1;
                        return root;
                    }
                    // RL
                    else
                    {
                        Node *newNodeLeft = newNode->left;
                        Node *newNodeRight = newNode->right;
                        Node *greatGrandParent = grandParent->parent;
                        if (greatGrandParent == NULL)
                        {
                            root = newNode;
                            newNode->parent = NULL;
                        }
                        else
                        {
                            if (greatGrandParent->right == grandParent)
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
                        if (newNodeLeft)
                            newNodeLeft->parent = grandParent;

                        if (newNodeRight)
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
            Node *newNode = new Node(key);
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

    Node *fixDelete(Node *root, Node *x)
    {
        while (x != root)
        {
            Node *parent = x->parent;
            Node *grandParent = parent->parent;
            Node *sibling;
            Node *nearChild;
            Node *farChild;

            if (parent->left == x)
            {
                // ---------- x is the LEFT child ----------
                sibling = parent->right;

                // Case 1: sibling is red -> rotate left at parent, swap colors, get a black sibling
                if (sibling->color == 1)
                {
                    nearChild = sibling->left;

                    if (grandParent == NULL)
                    {
                        root = sibling;
                        sibling->parent = NULL;
                    }
                    else
                    {
                        if (grandParent->left == parent)
                            grandParent->left = sibling;
                        else
                            grandParent->right = sibling;
                        sibling->parent = grandParent;
                    }

                    sibling->left = parent;
                    parent->parent = sibling;
                    parent->right = nearChild;
                    if (nearChild)
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
                if (!nearRed && !farRed)
                {
                    sibling->color = 1;
                    if (parent->color == 1)
                    {
                        parent->color = 0;
                        return root;
                    }
                    x = parent; // deficit moves up
                }
                else
                {
                    // Case 3: near red, far black -> rotate right at sibling, becomes case 4
                    if (!farRed)
                    {
                        Node *nearChildRight = nearChild->right;

                        parent->right = nearChild;
                        nearChild->parent = parent;
                        nearChild->right = sibling;
                        sibling->parent = nearChild;
                        sibling->left = nearChildRight;
                        if (nearChildRight)
                            nearChildRight->parent = sibling;

                        nearChild->color = 0;
                        sibling->color = 1;

                        sibling = nearChild;
                        farChild = sibling->right; // the old sibling, red
                    }

                    // Case 4: far red -> rotate left at parent
                    Node *siblingLeft = sibling->left;

                    if (grandParent == NULL)
                    {
                        root = sibling;
                        sibling->parent = NULL;
                    }
                    else
                    {
                        if (grandParent->left == parent)
                            grandParent->left = sibling;
                        else
                            grandParent->right = sibling;
                        sibling->parent = grandParent;
                    }

                    sibling->left = parent;
                    parent->parent = sibling;
                    parent->right = siblingLeft;
                    if (siblingLeft)
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
                if (sibling->color == 1)
                {
                    nearChild = sibling->right;

                    if (grandParent == NULL)
                    {
                        root = sibling;
                        sibling->parent = NULL;
                    }
                    else
                    {
                        if (grandParent->left == parent)
                            grandParent->left = sibling;
                        else
                            grandParent->right = sibling;
                        sibling->parent = grandParent;
                    }

                    sibling->right = parent;
                    parent->parent = sibling;
                    parent->left = nearChild;
                    if (nearChild)
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
                if (!nearRed && !farRed)
                {
                    sibling->color = 1;
                    if (parent->color == 1)
                    {
                        parent->color = 0;
                        return root;
                    }
                    x = parent;
                }
                else
                {
                    // Case 3: near red, far black -> rotate left at sibling
                    if (!farRed)
                    {
                        Node *nearChildLeft = nearChild->left;

                        parent->left = nearChild;
                        nearChild->parent = parent;
                        nearChild->left = sibling;
                        sibling->parent = nearChild;
                        sibling->right = nearChildLeft;
                        if (nearChildLeft)
                            nearChildLeft->parent = sibling;

                        nearChild->color = 0;
                        sibling->color = 1;

                        sibling = nearChild;
                        farChild = sibling->left; // the old sibling, red
                    }

                    // Case 4: far red -> rotate right at parent
                    Node *siblingRight = sibling->right;

                    if (grandParent == NULL)
                    {
                        root = sibling;
                        sibling->parent = NULL;
                    }
                    else
                    {
                        if (grandParent->left == parent)
                            grandParent->left = sibling;
                        else
                            grandParent->right = sibling;
                        sibling->parent = grandParent;
                    }

                    sibling->right = parent;
                    parent->parent = sibling;
                    parent->left = siblingRight;
                    if (siblingRight)
                        siblingRight->parent = parent;

                    sibling->color = parent->color;
                    parent->color = 0;
                    farChild->color = 0;
                    return root;
                }
            }
        }
        return root;
    }

    Node *deleteNode(Node *root, int key)
    {
        Node *temp = root;
        while (temp != NULL && temp->data != key)
        {
            if (temp->data > key)
                temp = temp->left;
            else
                temp = temp->right;
        }
        if (temp == NULL)
            return root;

        if (temp->left != NULL && temp->right != NULL)
        {
            Node *successor = temp->right;
            while (successor->left != NULL)
                successor = successor->left;
            temp->data = successor->data;
            temp = successor;
        }

        if (temp->left == NULL && temp->right == NULL) // leaf
        {
            if (temp->parent == NULL)
            {
                delete temp;
                return NULL;
            }

            if (temp->color == 0)
            {
                root = fixDelete(root, temp);
            }

            Node *parentNode = temp->parent;
            if (parentNode->left == temp)
                parentNode->left = NULL;
            else
                parentNode->right = NULL;
        }
        else
        {
            Node *childNode;
            if (temp->left != NULL)
                childNode = temp->left;
            else
                childNode = temp->right;

            Node *parentNode = temp->parent;
            childNode->parent = parentNode;
            if (parentNode == NULL)
                root = childNode;
            else if (parentNode->left == temp)
                parentNode->left = childNode;
            else
                parentNode->right = childNode;

            childNode->color = 0;
        }

        delete temp;
        return root;
    }
}

long long ignoredCount;
bool sameStructure;

void compareTrees(avl::Node *a, rb::Node *b)
{
    if (a == NULL)
    {
        if (b != NULL)
            sameStructure = false;
        return;
    }

    if (b == NULL || a->data != b->data)
    {
        ignoredCount++;
        sameStructure = false;
    }

    compareTrees(a->left, b ? b->left : NULL);
    compareTrees(a->right, b ? b->right : NULL);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int Q;
    cin >> Q;

    avl::Node *avlRoot = NULL;
    rb::Node *rbRoot = NULL;

    for (int i = 0; i < Q; i++)
    {
        char op;
        int x;
        cin >> op >> x;

        if (op == 'I')
        {
            if (avl::search(avlRoot, x) == NULL)
                avlRoot = avl::insert(avlRoot, x);
            if (rb::search(rbRoot, x) == NULL)
                rbRoot = rb::insert(rbRoot, x);
        }
        else
        {
            if (avl::search(avlRoot, x) != NULL)
                avlRoot = avl::deleteNode(avlRoot, x);
            if (rb::search(rbRoot, x) != NULL)
                rbRoot = rb::deleteNode(rbRoot, x);
        }

        ignoredCount = 0;
        sameStructure = true;
        compareTrees(avlRoot, rbRoot);

        cout << (sameStructure ? "MATCH " : "NO MATCH ") << ignoredCount << " ";

        if (avlRoot == NULL)
            cout << "EMPTY";
        else
            cout << avlRoot->data;
        cout << " ";
        if (rbRoot == NULL)
            cout << "EMPTY";
        else
            cout << rbRoot->data;
        cout << "\n";
    }

    return 0;
}