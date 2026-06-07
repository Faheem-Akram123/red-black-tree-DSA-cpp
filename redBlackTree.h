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

    Node *getParent(Node *rootNode, Node *target);
    void transplant(Node *&rootNode, Node *u, Node *v);
    void fixDelete(Node *&rootNode, Node *x, Node *xParent, bool isLeft);

public:
    void insert(const int &value);
    void inorderDisplay();
    void postorderDisplay();
    void preorderDisplay();
    bool searchValue(const int &value);
    bool deleteValue(const int &value);
};

Node *redBlackTree::getParent(Node *rootNode, Node *target)
{
    if (rootNode == nullptr || target == nullptr || rootNode == target)
        return nullptr;

    Node *curr = rootNode;
    while (curr != nullptr)
    {
        if (curr->leftChild == target || curr->rightChild == target)
            return curr;

        if (target->data < curr->data)
            curr = curr->leftChild;
        else
            curr = curr->rightChild;
    }
    return nullptr;
}

void redBlackTree::transplant(Node *&rootNode, Node *u, Node *v)
{
    Node *uParent = getParent(rootNode, u);
    if (uParent == nullptr)
    {
        rootNode = v;
    }
    else if (u == uParent->leftChild)
    {
        uParent->leftChild = v;
    }
    else
    {
        uParent->rightChild = v;
    }
}

void redBlackTree::fixDelete(Node *&rootNode, Node *x, Node *xParent, bool isLeft)
{
    Node *currX = x;
    Node *currP = xParent;
    bool left = isLeft;

    while (currX != rootNode && (currX == nullptr || currX->colour == 'b'))
    {
        if (currP == nullptr)
            break;

        if (currX == nullptr)
        {
            left = isLeft;
        }
        else
        {
            if (currX == currP->leftChild)
            {
                left = true;
            }
            else
            {
                left = false;
            }
        }

        if (left == true)
        {
            Node *w = currP->rightChild;
            if (w == nullptr)
                break;

            if (w->colour == 'r')
            {
                w->colour = 'b';
                currP->colour = 'r';
                Node *rot = rotateLeft(currP);
                transplant(rootNode, currP, rot);
                w = currP->rightChild;
            }
            if (w == nullptr)
                break;

            if ((w->leftChild == nullptr || w->leftChild->colour == 'b') &&
                (w->rightChild == nullptr || w->rightChild->colour == 'b'))
            {
                w->colour = 'r';
                currX = currP;
                currP = getParent(rootNode, currX);
            }
            else
            {
                if (w->rightChild == nullptr || w->rightChild->colour == 'b')
                {
                    if (w->leftChild != nullptr)
                        w->leftChild->colour = 'b';
                    w->colour = 'r';
                    Node *rot = rotateRight(w);
                    transplant(rootNode, w, rot);
                    w = currP->rightChild;
                }
                if (w == nullptr)
                    break;

                w->colour = currP->colour;
                currP->colour = 'b';
                if (w->rightChild != nullptr)
                    w->rightChild->colour = 'b';
                Node *rot = rotateLeft(currP);
                transplant(rootNode, currP, rot);
                currX = rootNode;
            }
        }
        else
        {
            Node *w = currP->leftChild;
            if (w == nullptr)
                break;

            if (w->colour == 'r')
            {
                w->colour = 'b';
                currP->colour = 'r';
                Node *rot = rotateRight(currP);
                transplant(rootNode, currP, rot);
                w = currP->leftChild;
            }
            if (w == nullptr)
                break;

            if ((w->leftChild == nullptr || w->leftChild->colour == 'b') &&
                (w->rightChild == nullptr || w->rightChild->colour == 'b'))
            {
                w->colour = 'r';
                currX = currP;
                currP = getParent(rootNode, currX);
            }
            else
            {
                if (w->leftChild == nullptr || w->leftChild->colour == 'b')
                {
                    if (w->rightChild != nullptr)
                        w->rightChild->colour = 'b';
                    w->colour = 'r';
                    Node *rot = rotateLeft(w);
                    transplant(rootNode, w, rot);
                    w = currP->leftChild;
                }
                if (w == nullptr)
                    break;

                w->colour = currP->colour;
                currP->colour = 'b';
                if (w->leftChild != nullptr)
                    w->leftChild->colour = 'b';
                Node *rot = rotateRight(currP);
                transplant(rootNode, currP, rot);
                currX = rootNode;
            }
        }
    }
    if (currX != nullptr)
        currX->colour = 'b';
}

bool redBlackTree::deleteValue(const int &value)
{
    Node *z = root;
    while (z != nullptr && z->data != value)
    {
        if (value < z->data)
        {
            z = z->leftChild;
        }
        else
        {
            z = z->rightChild;
        }
    }

    if (z == nullptr)
    {
        cout << "Value " << value << " not found" << endl;
        return false;
    }

    if (z->count > 1)
    {
        z->count--;
        cout << "Value " << value << " count decremented to: " << z->count << endl;
        return true;
    }

    Node *y = z;
    char orig_color = y->colour;
    Node *x = nullptr;
    Node *x_parent = nullptr;
    bool is_left = false;

    if (z->leftChild == nullptr)
    {
        x = z->rightChild;
        x_parent = getParent(root, z);

        if (x_parent != nullptr)
        {
            if (z == x_parent->leftChild)
                is_left = true;
            else
                is_left = false;
        }

        transplant(root, z, z->rightChild);
    }
    else if (z->rightChild == nullptr)
    {
        x = z->leftChild;
        x_parent = getParent(root, z);
        if (x_parent != nullptr)
        {
            if (z == x_parent->leftChild)
                is_left = true;
            else
                is_left = false;
        }
        transplant(root, z, z->leftChild);
    }
    else
    {
        y = z->rightChild;
        while (y->leftChild != nullptr)
            y = y->leftChild;
        orig_color = y->colour;
        x = y->rightChild;

        Node *y_parent = getParent(root, y);
        if (y_parent == z)
        {
            x_parent = y;
            is_left = false;
        }
        else
        {
            x_parent = y_parent;
            if (y_parent != nullptr)
            {
                if (y == y_parent->leftChild)
                    is_left = true;
                else
                    is_left = false;
            }
        }

        if (y_parent != z)
        {
            transplant(root, y, y->rightChild);
            y->rightChild = z->rightChild;
        }
        transplant(root, z, y);
        y->leftChild = z->leftChild;
        y->colour = z->colour;
    }

    if (orig_color == 'b')
        fixDelete(root, x, x_parent, is_left);
    delete z;
    cout << "Value " << value << " successfully deleted." << endl;
    return true;
}

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
