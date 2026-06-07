#include "Node.h"
#include <iostream>
using namespace std;

class rbt
{
protected:
    Node *root = nullptr;

public:
    virtual void insert(const int &value) = 0;
    virtual void inorderDisplay() = 0;
    virtual void preorderDisplay() = 0;
    virtual void postorderDisplay() = 0;
    virtual bool searchValue(const int &value) = 0;
    virtual bool deleteValue(const int &value) = 0;
};