#include "Runner.h"

int Runner::run() {
    Tree *a = new Tree();

    int option = 0;
    int data;

    do {

        this->showOptions();
        cin >> option;

        switch (option) {

            case Constants::Option::INSERT_NODE:
                cout << "Type a value to insert: ";
                cin >> data;

                this->clearConsole();

                a->insert(data);

                a->showTree();

                this->breakLines();
                break;

            case Constants::Option::REMOVE_NODE:
                cout << "Type a value to remove: ";
                cin >> data;

                this->clearConsole();

                a->remove(data);

                a->showTree();

                this->breakLines();
                break;

            case Constants::Option::CLEAR_TREE:
                this->clearConsole();

                delete a;

                a = new Tree();

                this->breakLines();
                break;

            case Constants::Option::SHOW_TREE_BY_LEVEL:
                this->clearConsole();

                a->showTree();

                this->breakLines();
                break;

            case Constants::Option::SHOW_TREE_PRE_ORDER:
                this->clearConsole();

                cout << "Pre order: ";

                a->preOrder();

                this->breakLines();
                break;

            case Constants::Option::SHOW_TREE_IN_ORDER:
                this->clearConsole();

                cout << "In order: ";

                a->inOrder();

                this->breakLines();
                break;

            case Constants::Option::SHOW_TREE_POS_ORDER:
                this->clearConsole();

                cout << "Pos order: ";

                a->posOrder();

                this->breakLines();
                break;

            case Constants::Option::EXIT:
                cout << endl << "Exiting..." << endl << "Thx :) ->";
                break;

            default:
                cout << endl << "Invalid option, please try again :(" << endl << endl;
                break;

        }
    } while (option != Constants::Option::EXIT);

    return EXIT_SUCCESS;
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
    cout << Constants::Option::EXIT << " - Exit" << endl;
    cout << endl << "Choose a option: " << endl;
}