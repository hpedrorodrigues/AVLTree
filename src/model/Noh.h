#ifndef AVLTREE_NOH_H
#define AVLTREE_NOH_H

#include <stddef.h>

class Noh {

private:
    Noh *left, *right, *father;

public:
    int data;

    Noh(int data, Noh *left = NULL, Noh *right = NULL, Noh *father = NULL);

    ~Noh();

    int getData();

    void setData(int data);

    Noh *getLeft();

    void setLeft(Noh *left);

    Noh *getRight();

    void setRight(Noh *right);

    Noh *getFather();

    void setFather(Noh *father);
};

#endif