#ifndef AVLTREE_CONSTANTS_H
#define AVLTREE_CONSTANTS_H

#include <iostream>

using namespace std;

class Constants {

public:

    class Option {

    public:

        static const int INSERT_NODE = 1;
        static const int REMOVE_NODE = 2;
        static const int CLEAR_TREE = 3;
        static const int SHOW_TREE_BY_LEVEL = 4;
        static const int SHOW_TREE_PRE_ORDER = 5;
        static const int SHOW_TREE_IN_ORDER = 6;
        static const int SHOW_TREE_POS_ORDER = 7;
        static const int EXIT = 8;
    };

    class System {

    public:

        static const string SEPARATOR;
    };

};

#endif