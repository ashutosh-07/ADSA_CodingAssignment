#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Node {
    int keys[3];
    int keyCount;
    bool isLeaf;
    struct Node* children[4];
    struct Node* parent;

    Node(bool leaf = true) {
        keyCount = 0;
        isLeaf = leaf;
        parent = nullptr;
        for (int i = 0; i < 3; ++i) keys[i] = 0;
        for (int i = 0; i < 4; ++i) children[i] = nullptr;
    }
};

Node* createNode(bool isLeaf = true) {
    return new Node(isLeaf);
}

Node* search(Node* root, int key) {
    if (!root) return nullptr;
    Node* curr = root;
    while (curr) {
        int i = 0;
        while (i < curr->keyCount && key > curr->keys[i]) {
            i++;
        }
        if (i < curr->keyCount && key == curr->keys[i]) {
            return curr;
        }
        if (curr->isLeaf) {
            return nullptr;
        }
        curr = curr->children[i];
    }
    return nullptr;
}

void getInorder(Node* root, vector<int>& keys) {
    if (!root) return;
    if (root->isLeaf) {
        for (int i = 0; i < root->keyCount; ++i) {
            keys.push_back(root->keys[i]);
        }
    } else {
        for (int i = 0; i < root->keyCount; ++i) {
            getInorder(root->children[i], keys);
            keys.push_back(root->keys[i]);
        }
        getInorder(root->children[root->keyCount], keys);
    }
}

void printInorder(Node* root) {
    vector<int> keys;
    getInorder(root, keys);
    cout << "INORDER:";
    for (size_t i = 0; i < keys.size(); ++i) {
        cout << " " << keys[i];
    }
    cout << "\n";
}

void printLevelOrder(Node* root) {
    cout << "LEVELORDER:\n";
    if (!root) return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; ++i) {
            Node* curr = q.front();
            q.pop();

            cout << "[";
            for (int k = 0; k < curr->keyCount; ++k) {
                cout << curr->keys[k];
                if (k < curr->keyCount - 1) cout << "|";
            }
            cout << "]";
            if (i < levelSize - 1) cout << " ";

            if (!curr->isLeaf) {
                for (int c = 0; c <= curr->keyCount; ++c) {
                    if (curr->children[c]) {
                        q.push(curr->children[c]);
                    }
                }
            }
        }
        cout << "\n";
    }
}

void splitChild(Node* parent, int idx, Node* fullChild) {
    Node* newNode = createNode(fullChild->isLeaf);
    newNode->parent = parent;

    int promotedKey = fullChild->keys[1];

    newNode->keys[0] = fullChild->keys[2];
    newNode->keyCount = 1;

    fullChild->keyCount = 1;

    if (!fullChild->isLeaf) {
        newNode->children[0] = fullChild->children[2];
        newNode->children[1] = fullChild->children[3];
        if (newNode->children[0]) newNode->children[0]->parent = newNode;
        if (newNode->children[1]) newNode->children[1]->parent = newNode;

        fullChild->children[2] = nullptr;
        fullChild->children[3] = nullptr;
    }

    for (int j = parent->keyCount; j > idx; --j) {
        parent->children[j + 1] = parent->children[j];
    }
    parent->children[idx + 1] = newNode;

    for (int j = parent->keyCount - 1; j >= idx; --j) {
        parent->keys[j + 1] = parent->keys[j];
    }
    parent->keys[idx] = promotedKey;
    parent->keyCount++;
}

Node* insert(Node* root, int key) {
    if (search(root, key) != nullptr) {
        cout << "Duplicate key\n";
        return root;
    }

    if (!root) {
        root = createNode(true);
        root->keys[0] = key;
        root->keyCount = 1;
        return root;
    }

    if (root->keyCount == 3) {
        Node* newRoot = createNode(false);
        newRoot->children[0] = root;
        root->parent = newRoot;
        splitChild(newRoot, 0, root);
        root = newRoot;
    }

    Node* curr = root;
    while (!curr->isLeaf) {
        int i = 0;
        while (i < curr->keyCount && key > curr->keys[i]) {
            i++;
        }

        if (curr->children[i]->keyCount == 3) {
            splitChild(curr, i, curr->children[i]);
            if (key > curr->keys[i]) {
                i++;
            }
        }
        curr = curr->children[i];
    }

    int i = curr->keyCount - 1;
    while (i >= 0 && curr->keys[i] > key) {
        curr->keys[i + 1] = curr->keys[i];
        i--;
    }
    curr->keys[i + 1] = key;
    curr->keyCount++;

    return root;
}

bool validateNode(Node* node, int minVal, int maxVal, int depth, int& leafDepth) {
    if (!node) return true;

    if (node->keyCount < 1 || node->keyCount > 3) return false;

    for (int i = 0; i < node->keyCount; ++i) {
        if (node->keys[i] <= minVal || node->keys[i] >= maxVal) return false;
        if (i > 0 && node->keys[i] <= node->keys[i - 1]) return false;
    }

    if (node->isLeaf) {
        if (leafDepth == -1) {
            leafDepth = depth;
        } else if (leafDepth != depth) {
            return false;
        }
    } else {
        for (int i = 0; i <= node->keyCount; ++i) {
            if (!node->children[i]) return false;
            if (node->children[i]->parent != node) return false;

            int low = (i == 0) ? minVal : node->keys[i - 1];
            int high = (i == node->keyCount) ? maxVal : node->keys[i];

            if (!validateNode(node->children[i], low, high, depth + 1, leafDepth)) {
                return false;
            }
        }
    }
    return true;
}

bool validate(Node* root) {
    if (!root) return true;
    int leafDepth = -1;
    return validateNode(root, INT_MIN, INT_MAX, 0, leafDepth);
}

void borrowFromLeft(Node* parent, int idx) {
    Node* child = parent->children[idx];
    Node* leftSibling = parent->children[idx - 1];

    for (int i = child->keyCount; i > 0; --i) {
        child->keys[i] = child->keys[i - 1];
    }
    child->keys[0] = parent->keys[idx - 1];

    if (!child->isLeaf) {
        for (int i = child->keyCount + 1; i > 0; --i) {
            child->children[i] = child->children[i - 1];
        }
        child->children[0] = leftSibling->children[leftSibling->keyCount];
        if (child->children[0]) child->children[0]->parent = child;
    }

    child->keyCount++;
    parent->keys[idx - 1] = leftSibling->keys[leftSibling->keyCount - 1];
    leftSibling->keyCount--;
}

void borrowFromRight(Node* parent, int idx) {
    Node* child = parent->children[idx];
    Node* rightSibling = parent->children[idx + 1];

    child->keys[child->keyCount] = parent->keys[idx];

    if (!child->isLeaf) {
        child->children[child->keyCount + 1] = rightSibling->children[0];
        if (child->children[child->keyCount + 1]) {
            child->children[child->keyCount + 1]->parent = child;
        }
    }
    child->keyCount++;

    parent->keys[idx] = rightSibling->keys[0];

    for (int i = 0; i < rightSibling->keyCount - 1; ++i) {
        rightSibling->keys[i] = rightSibling->keys[i + 1];
    }
    if (!rightSibling->isLeaf) {
        for (int i = 0; i < rightSibling->keyCount; ++i) {
            rightSibling->children[i] = rightSibling->children[i + 1];
        }
    }
    rightSibling->keyCount--;
}

void merge(Node* parent, int idx) {
    Node* leftChild = parent->children[idx];
    Node* rightChild = parent->children[idx + 1];

    leftChild->keys[leftChild->keyCount] = parent->keys[idx];
    leftChild->keyCount++;

    for (int i = 0; i < rightChild->keyCount; ++i) {
        leftChild->keys[leftChild->keyCount] = rightChild->keys[i];
        leftChild->keyCount++;
    }

    if (!leftChild->isLeaf) {
        for (int i = 0; i <= rightChild->keyCount; ++i) {
            leftChild->children[leftChild->keyCount - rightChild->keyCount + i] = rightChild->children[i];
            if (rightChild->children[i]) {
                rightChild->children[i]->parent = leftChild;
            }
        }
    }

    for (int i = idx; i < parent->keyCount - 1; ++i) {
        parent->keys[i] = parent->keys[i + 1];
    }
    for (int i = idx + 1; i < parent->keyCount; ++i) {
        parent->children[i] = parent->children[i + 1];
    }
    parent->keyCount--;
    delete rightChild;
}

Node* deleteKey(Node* root, int key) {
    if (!search(root, key)) {
        cout << "Key not found\n";
        return root;
    }

    Node* curr = root;

    while (curr) {

        int kIdx = -1;
        for (int i = 0; i < curr->keyCount; ++i) {
            if (curr->keys[i] == key) {
                kIdx = i;
                break;
            }
        }

        if (kIdx != -1) {
            if (curr->isLeaf) {
                for (int i = kIdx; i < curr->keyCount - 1; ++i) {
                    curr->keys[i] = curr->keys[i + 1];
                }
                curr->keyCount--;
                break;
            } else {
                Node* leftChild = curr->children[kIdx];
                Node* rightChild = curr->children[kIdx + 1];

                if (leftChild->keyCount >= 2) {
                    Node* predNode = leftChild;
                    while (!predNode->isLeaf) {
                        if (predNode->children[predNode->keyCount]->keyCount == 1) {
                            int idx = predNode->keyCount;
                            Node* lSib = (idx > 0) ? predNode->children[idx - 1] : nullptr;
                            Node* rSib = nullptr;
                            if (lSib && lSib->keyCount >= 2) borrowFromLeft(predNode, idx);
                            else merge(predNode, idx - 1);
                        } else {
                            predNode = predNode->children[predNode->keyCount];
                        }
                    }
                    int predKey = predNode->keys[predNode->keyCount - 1];
                    curr->keys[kIdx] = predKey;
                    key = predKey;
                    curr = leftChild;
                } else if (rightChild->keyCount >= 2) {
                    Node* succNode = rightChild;
                    while (!succNode->isLeaf) {
                        if (succNode->children[0]->keyCount == 1) {
                            int idx = 0;
                            Node* rSib = (idx < succNode->keyCount) ? succNode->children[idx + 1] : nullptr;
                            if (rSib && rSib->keyCount >= 2) borrowFromRight(succNode, idx);
                            else merge(succNode, idx);
                        } else {
                            succNode = succNode->children[0];
                        }
                    }
                    int succKey = succNode->keys[0];
                    curr->keys[kIdx] = succKey;
                    key = succKey;
                    curr = rightChild;
                } else {
                    merge(curr, kIdx);
                    if (curr == root && curr->keyCount == 0) {
                        root = curr->children[0];
                        if (root) root->parent = nullptr;
                        delete curr;
                        curr = root;
                    } else {
                        curr = leftChild;
                    }
                }
            }
        } else {
            int childIdx = 0;
            while (childIdx < curr->keyCount && key > curr->keys[childIdx]) {
                childIdx++;
            }
            Node* child = curr->children[childIdx];

            if (child->keyCount == 1) {
                Node* leftSib = (childIdx > 0) ? curr->children[childIdx - 1] : nullptr;
                Node* rightSib = (childIdx < curr->keyCount) ? curr->children[childIdx + 1] : nullptr;

                if (leftSib && leftSib->keyCount >= 2) {
                    borrowFromLeft(curr, childIdx);
                } else if (rightSib && rightSib->keyCount >= 2) {
                    borrowFromRight(curr, childIdx);
                } else if (rightSib) {
                    merge(curr, childIdx);
                } else if (leftSib) {
                    merge(curr, childIdx - 1);
                }

                if (curr == root && curr->keyCount == 0) {
                    root = curr->children[0];
                    if (root) root->parent = nullptr;
                    delete curr;
                    curr = root;
                }
            } else {
                curr = child;
            }
        }
    }

    if (root && root->keyCount == 0) {
        Node* oldRoot = root;
        root = root->children[0];
        if (root) root->parent = nullptr;
        delete oldRoot;
    }

    return root;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Node* root = nullptr;

    int N;
    if (!(cin >> N)) return 0;
    for (int i = 0; i < N; ++i) {
        int key;
        cin >> key;
        root = insert(root, key);
    }

    cout << "INITIAL TREE\n";
    printInorder(root);
    printLevelOrder(root);
    cout << "END\n";

    int S;
    cin >> S;
    for (int i = 0; i < S; ++i) {
        int key;
        cin >> key;
        cout << "SEARCH " << key << ": ";
        if (search(root, key)) {
            cout << "Key found\n";
        } else {
            cout << "Key not found\n";
        }
    }

    int I;
    cin >> I;
    for (int i = 0; i < I; ++i) {
        int key;
        cin >> key;
        cout << "INSERT " << key << "\n";
        if (search(root, key)) {
            cout << "Duplicate key\n";
        } else {
            root = insert(root, key);
            printInorder(root);
            printLevelOrder(root);
            if (validate(root)) {
                cout << "VALID\n";
            } else {
                cout << "INVALID\n";
            }
            cout << "END\n";
        }
    }

    int D;
    cin >> D;
    for (int i = 0; i < D; ++i) {
        int key;
        cin >> key;
        cout << "DELETE " << key << "\n";
        if (!search(root, key)) {
            cout << "Key not found\n";
        } else {
            root = deleteKey(root, key);
            printInorder(root);
            printLevelOrder(root);
            if (validate(root)) {
                cout << "VALID\n";
            } else {
                cout << "INVALID\n";
            }
            cout << "END\n";
        }
    }

    return 0;
}