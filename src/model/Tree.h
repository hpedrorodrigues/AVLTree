#ifndef AVLTREE_TREE_H
#define AVLTREE_TREE_H

#include "Noh.h"
#include "Constants.h"
#include <iostream>

using namespace std;

class Tree {

private:

    Noh *root;

    int heightRec(Noh *noh);

    void preOrderRec(Noh *noh);

    void inOrderRec(Noh *noh);

    void posOrderRec(Noh *noh);

    Noh *moreLeft(Noh *noh);

    Noh *moreRight(Noh *noh);

    bool isEmpty();

    int max(int a, int b);

    int getBalanceFactor(Noh *noh);

    Noh *insert(int data, Noh *noh);

    void showSubTreeRec(Noh *noh, string separator);

public:

    Tree();

    ~Tree();

    int getHeight();

    bool insert(int data);

    void remove(int data);

    Noh *balance(Noh *noh);

    Noh *rotRight(Noh *noh);

    Noh *rotLeft(Noh *noh);

    Noh *rotLeftRight(Noh *noh);

    Noh *rotRightLeft(Noh *noh);

    Noh *searchFather(int data);

    void showTree();

    void preOrder();

    void inOrder();

    void posOrder();
};

#endif