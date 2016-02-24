#include "Noh.h"

Noh::Noh(int data, Noh *left, Noh *right, Noh *father) {
    this->data = data;
    this->left = left;
    this->right = right;
    this->father = father;
}

Noh::~Noh() {
    if (this->father != NULL) {
        if (this->father->left == this) {
            this->father->left = NULL;
        } else {
            this->father->right = NULL;
        }
    }
}

int Noh::getData() {
    return this->data;
}

void Noh::setData(int data) {
    this->data = data;
}

Noh *Noh::getLeft() {
    return this->left;
}

void Noh::setLeft(Noh *left) {
    this->left = left;
}

Noh *Noh::getRight() {
    return this->right;
}

void Noh::setRight(Noh *right) {
    this->right = right;
}

Noh *Noh::getFather() {
    return this->father;
}

void Noh::setFather(Noh *father) {
    this->father = father;
}