#include "Runner.h"

void Runner::run() {
    Tree *tree = new Tree();

    int option = 0;
    int data;

    do {

        this->showOptions();
        cin >> option;

        switch (option) {

            case Constants::Option::INSERT_NODE:
                cout << endl << "Type a value to insert: ";
                cin >> data;

                this->clearConsole();

                tree->insert(data);

                tree->showTree();

                this->breakLines();
                break;

            case Constants::Option::REMOVE_NODE:
                cout << endl << "Type a value to remove: ";
                cin >> data;

                this->clearConsole();

                tree->remove(data);

                tree->showTree();

                this->breakLines();
                break;

            case Constants::Option::CLEAR_TREE:
                this->clearConsole();

                delete tree;

                tree = new Tree();

                this->breakLines();
                break;

            case Constants::Option::SHOW_TREE_BY_LEVEL:
                this->clearConsole();

                tree->showTree();

                this->breakLines();
                break;

            case Constants::Option::SHOW_TREE_PRE_ORDER:
                this->clearConsole();

                cout << endl << "Pre order: ";

                tree->preOrder();

                this->breakLines();
                break;

            case Constants::Option::SHOW_TREE_IN_ORDER:
                this->clearConsole();

                cout << endl << "In order: ";

                tree->inOrder();

                this->breakLines();
                break;

            case Constants::Option::SHOW_TREE_POS_ORDER:
                this->clearConsole();

                cout << endl << "Pos order: ";

                tree->posOrder();

                this->breakLines();
                break;

            case Constants::Option::SHOW_TREE_HEIGHT:
                cout << endl << "Tree height: " << tree->getHeight() << endl;
                break;

            case Constants::Option::EXIT:
                cout << endl << "Exiting..." << endl << "Thx :) ->";
                break;

            default:
                cout << endl << "Invalid option, please try again :(" << endl << endl;
                break;

        }
    } while (option != Constants::Option::EXIT);
}

void Runner::clearConsole() {
    system("clear");
}

void Runner::breakLines() {
    cout << endl << endl;
}

void Runner::showOptions() {
    cout << "----------------------------------------------" << endl;
    cout << "Georgy Adelson-Velsky and Evgenii Landis' Tree" << endl;
    cout << "----------------------------------------------" << endl;
    cout << endl;
    cout << Constants::Option::INSERT_NODE << " - Insert node" << endl;
    cout << Constants::Option::REMOVE_NODE << " - Remove node" << endl;
    cout << Constants::Option::CLEAR_TREE << " - Clear tree" << endl;
    cout << Constants::Option::SHOW_TREE_BY_LEVEL << " - Show tree by level" << endl;
    cout << Constants::Option::SHOW_TREE_PRE_ORDER << " - Show tree with pre order" << endl;
    cout << Constants::Option::SHOW_TREE_IN_ORDER << " - Show tree in order" << endl;
    cout << Constants::Option::SHOW_TREE_POS_ORDER << " - Show tree with pos order" << endl;
    cout << Constants::Option::SHOW_TREE_HEIGHT << " - Show tree height" << endl;
    cout << Constants::Option::EXIT << " - Exit" << endl;
    cout << endl << "Choose a option: " << endl;
}