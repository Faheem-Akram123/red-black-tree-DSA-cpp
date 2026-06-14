#include "rbt.h"

class redBlackTree : public rbt
{
    Node *insertHelper(Node *root, int value);
    Node *balanceNodes(Node *node);
    Node *rotateRight(Node *node);
    Node *rotateLeft(Node *node);

    void INORDER(Node *root);
    void PREORDER(Node *root);
    void POSTORDER(Node *root);

    Node *deleteHelper(Node *rootNode, int value, bool &decreased);
    Node *balanceDeleteLeft(Node *rootNode, bool &decreased);
    Node *balanceDeleteRight(Node *rootNode, bool &decreased);

public:
    void insert(const int &value);
    void inorderDisplay();
    void postorderDisplay();
    void preorderDisplay();
    bool searchValue(const int &value);
    bool deleteValue(const int &value);
};

bool redBlackTree::searchValue(const int &value)
{
    if (root == nullptr)
    {
        cout << "Tree is empty " << endl;
        return false;
    }

    Node *p = root;
    while (true)
    {
        if (p == nullptr)
            return false;

        if (p->data == value)
            return true;

        if (value < p->data)
            p = p->leftChild;

        else
            p = p->rightChild;
    }
}

Node *redBlackTree::rotateLeft(Node *node)
{
    Node *p = node->rightChild;
    node->rightChild = p->leftChild;
    p->leftChild = node;

    return p;
}

Node *redBlackTree::rotateRight(Node *node)
{
    Node *p = node->leftChild;
    node->leftChild = p->rightChild;
    p->rightChild = node;

    return p;
}

Node *redBlackTree::balanceNodes(Node *node)
{
    // LL
    if (node->leftChild != nullptr && node->leftChild->colour == 'r' &&
        node->leftChild->leftChild != nullptr && node->leftChild->leftChild->colour == 'r')
    {
        if (node->rightChild != nullptr && node->rightChild->colour == 'r')
        {
            node->colour = 'r';
            node->leftChild->colour = 'b';
            node->rightChild->colour = 'b';
        }
        else
        {
            node = rotateRight(node);

            node->colour = 'b';
            node->rightChild->colour = 'r';
        }
    }
    // RR
    if (node->rightChild != nullptr && node->rightChild->colour == 'r' &&
        node->rightChild->rightChild != nullptr && node->rightChild->rightChild->colour == 'r')
    {
        if (node->leftChild != nullptr && node->leftChild->colour == 'r')
        {
            node->colour = 'r';
            node->leftChild->colour = 'b';
            node->rightChild->colour = 'b';
        }
        else
        {
            node = rotateLeft(node);

            node->colour = 'b';
            node->leftChild->colour = 'r';
        }
    }
    // LR
    if (node->leftChild != nullptr && node->leftChild->colour == 'r' &&
        node->leftChild->rightChild != nullptr && node->leftChild->rightChild->colour == 'r')
    {
        if (node->rightChild != nullptr && node->rightChild->colour == 'r')
        {
            node->colour = 'r';
            node->leftChild->colour = 'b';
            node->rightChild->colour = 'b';
        }
        else
        {
            node->leftChild = rotateLeft(node->leftChild);
            node = rotateRight(node);

            node->colour = 'b';
            node->rightChild->colour = 'r';
        }
    }
    // RL
    if (node->rightChild != nullptr && node->rightChild->colour == 'r' &&
        node->rightChild->leftChild != nullptr && node->rightChild->leftChild->colour == 'r')
    {
        if (node->leftChild != nullptr && node->leftChild->colour == 'r')
        {
            node->colour = 'r';
            node->leftChild->colour = 'b';
            node->rightChild->colour = 'b';
        }
        else
        {
            node->rightChild = rotateRight(node->rightChild);
            node = rotateLeft(node);

            node->colour = 'b';
            node->leftChild->colour = 'r';
        }
    }
    return node;
}

Node *redBlackTree::insertHelper(Node *root, int value)
{
    if (root == nullptr)
    {
        Node *nn = new Node;
        nn->data = value;
        nn->leftChild = nullptr;
        nn->rightChild = nullptr;
        nn->colour = 'r';
        nn->count = 1;

        return nn;
    }
    if (value == root->data)
        root->count++;

    if (value < root->data)
        root->leftChild = insertHelper(root->leftChild, value);
    else
        root->rightChild = insertHelper(root->rightChild, value);

    root = balanceNodes(root);

    return root;
}

void redBlackTree::insert(const int &value)
{
    root = insertHelper(root, value);
    root->colour = 'b';
}

void redBlackTree::INORDER(Node *root)
{
    if (root == nullptr)
        return;

    INORDER(root->leftChild);
    cout << root->data << "(" << root->colour << ")" << " -> " << root->count << endl;
    INORDER(root->rightChild);
}

void redBlackTree::inorderDisplay()
{
    if (root == nullptr)
    {
        cout << "Tree is empty" << endl;
        return;
    }

    INORDER(root);
}

void redBlackTree::PREORDER(Node *root)
{
    if (root == nullptr)
        return;

    cout << root->data << "(" << root->colour << ")" << " -> " << root->count << endl;
    INORDER(root->leftChild);
    INORDER(root->rightChild);
}

void redBlackTree::preorderDisplay()
{
    if (root == nullptr)
    {
        cout << "Tree is empty" << endl;
        return;
    }

    PREORDER(root);
}

void redBlackTree::POSTORDER(Node *root)
{
    if (root == nullptr)
        return;

    INORDER(root->leftChild);
    INORDER(root->rightChild);
    cout << root->data << "(" << root->colour << ")" << " -> " << root->count << endl;
}

void redBlackTree::postorderDisplay()
{
    if (root == nullptr)
    {
        cout << "Tree is empty" << endl;
        return;
    }

    POSTORDER(root);
}

Node *redBlackTree::deleteHelper(Node *rootNode, int value, bool &decreased)
{
    if (rootNode == nullptr)
    {
        decreased = false;
        return nullptr;
    }
    if (value < rootNode->data)
    {
        rootNode->leftChild = deleteHelper(rootNode->leftChild, value, decreased);
        if (decreased)
        {
            rootNode = balanceDeleteLeft(rootNode, decreased);
        }
    }
    else if (value > rootNode->data)
    {
        rootNode->rightChild = deleteHelper(rootNode->rightChild, value, decreased);
        if (decreased)
        {
            rootNode = balanceDeleteRight(rootNode, decreased);
        }
    }
    else // value == rootNode->data (We found the node!)
    {
        // 1. Handle duplicate frequencies
        if (rootNode->count > 1)
        {
            rootNode->count--;
            cout << "Value " << value << " count decremented to: " << rootNode->count << endl;
            decreased = false;
            return rootNode;
        }
        Node *temp = nullptr;
        // 2. Case: 0 or 1 Child
        if (rootNode->leftChild == nullptr)
        {
            temp = rootNode->rightChild;
            if (rootNode->colour == 'b')
            {
                // If the single replacement child is RED, we color it BLACK to absorb the deficit
                if (temp != nullptr && temp->colour == 'r')
                {
                    temp->colour = 'b';
                    decreased = false;
                }
                else
                {
                    decreased = true; // Lost a black node with no replacement, deficit propagates
                }
            }
            else
            {
                decreased = false; // Deleting a red leaf doesn't alter black height
            }
            delete rootNode;
            return temp;
        }
        else if (rootNode->rightChild == nullptr)
        {
            temp = rootNode->leftChild;
            if (rootNode->colour == 'b')
            {
                if (temp != nullptr && temp->colour == 'r')
                {
                    temp->colour = 'b';
                    decreased = false;
                }
                else
                {
                    decreased = true;
                }
            }
            else
            {
                decreased = false;
            }
            delete rootNode;
            return temp;
        }
        else // 3. Case: 2 Children (Replace with In-order Successor)
        {
            Node *succ = rootNode->rightChild;
            while (succ->leftChild != nullptr)
            {
                succ = succ->leftChild;
            }
            // Copy successor value and counts to target
            rootNode->data = succ->data;
            rootNode->count = succ->count;
            // Force physical deletion of successor by temporarily marking successor's count as 1
            int original_succ_count = succ->count;
            succ->count = 1;
            rootNode->rightChild = deleteHelper(rootNode->rightChild, succ->data, decreased);
            if (decreased)
            {
                rootNode = balanceDeleteRight(rootNode, decreased);
            }
        }
    }
    return rootNode;
}
/**
 * balanceDeleteLeft handles restoration when the LEFT child's black-height has decreased.
 */
Node *redBlackTree::balanceDeleteLeft(Node *rootNode, bool &decreased)
{
    Node *w = rootNode->rightChild; // Sibling of left child
    // Case 1: Sibling is RED
    if (w->colour == 'r')
    {
        w->colour = 'b';
        rootNode->colour = 'r';
        rootNode = rotateLeft(rootNode);

        // After rotation, original parent shifts left. Recursively balance Left child again.
        rootNode->leftChild = balanceDeleteLeft(rootNode->leftChild, decreased);
        return rootNode;
    }
    // Now Sibling is guaranteed to be BLACK
    if ((w->leftChild == nullptr || w->leftChild->colour == 'b') &&
        (w->rightChild == nullptr || w->rightChild->colour == 'b'))
    {
        // Case 2: Sibling and both sibling's children are BLACK (Double Black)
        w->colour = 'r';
        if (rootNode->colour == 'r')
        {
            rootNode->colour = 'b';
            decreased = false; // Deficit absorbed by red parent turning black
        }
        else
        {
            decreased = true; // Deficit continues to propagate up to rootNode's parent
        }
    }
    else
    {
        // Case 3: Sibling is BLACK, near child (left) is RED, far child (right) is BLACK
        if (w->rightChild == nullptr || w->rightChild->colour == 'b')
        {
            if (w->leftChild != nullptr)
                w->leftChild->colour = 'b';
            w->colour = 'r';
            rootNode->rightChild = rotateRight(w);
            w = rootNode->rightChild; // Update sibling to new right child
        }
        // Case 4: Sibling is BLACK, far child (right) is RED
        w->colour = rootNode->colour;
        rootNode->colour = 'b';
        if (w->rightChild != nullptr)
            w->rightChild->colour = 'b';
        rootNode = rotateLeft(rootNode);
        decreased = false; // Deficit fully resolved
    }
    return rootNode;
}
/**
 * balanceDeleteRight handles restoration when the RIGHT child's black-height has decreased.
 */
Node *redBlackTree::balanceDeleteRight(Node *rootNode, bool &decreased)
{
    Node *w = rootNode->leftChild; // Sibling of right child
    // Case 1: Sibling is RED
    if (w->colour == 'r')
    {
        w->colour = 'b';
        rootNode->colour = 'r';
        rootNode = rotateRight(rootNode);
        rootNode->rightChild = balanceDeleteRight(rootNode->rightChild, decreased);
        return rootNode;
    }
    // Now Sibling is guaranteed to be BLACK
    if ((w->leftChild == nullptr || w->leftChild->colour == 'b') &&
        (w->rightChild == nullptr || w->rightChild->colour == 'b'))
    {
        // Case 2: Sibling and both child subtrees are BLACK (Double Black)
        w->colour = 'r';
        if (rootNode->colour == 'r')
        {
            rootNode->colour = 'b';
            decreased = false;
        }
        else
        {
            decreased = true;
        }
    }
    else
    {
        // Case 3: Sibling is BLACK, near child (right) is RED, far child (left) is BLACK
        if (w->leftChild == nullptr || w->leftChild->colour == 'b')
        {
            if (w->rightChild != nullptr)
                w->rightChild->colour = 'b';
            w->colour = 'r';
            rootNode->leftChild = rotateLeft(w);
            w = rootNode->leftChild;
        }
        // Case 4: Sibling is BLACK, far child (left) is RED
        w->colour = rootNode->colour;
        rootNode->colour = 'b';
        if (w->leftChild != nullptr)
            w->leftChild->colour = 'b';
        rootNode = rotateRight(rootNode);
        decreased = false; // Deficit fully resolved
    }
    return rootNode;
}

bool redBlackTree::deleteValue(const int &value)
{
    if (root == nullptr)
    {
        cout << "Tree is empty" << endl;
        return false;
    }
    bool decreased = false;

    // First, verify value exists so we can print "not found"
    if (!searchValue(value))
    {
        cout << "Value " << value << " not found" << endl;
        return false;
    }
    root = deleteHelper(root, value, decreased);
    if (root != nullptr)
    {
        root->colour = 'b'; // Root must remain black
    }
    cout << "Value " << value << " successfully deleted." << endl;
    return true;
}