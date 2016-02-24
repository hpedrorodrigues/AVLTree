#include "Runner.h"

int Runner::run() {
    //Criando uma instância da classe Árvore
    Tree *a = new Tree();

    int escolha = 0;
    do {
        // Menu
        cout << "1 - Inserir\n";
        cout << "2 - Remover No\n";
        cout << "3 - Limpar Arvore\n";
        cout << "4 - Imprimir por nivel\n";
        cout << "5 - Imprimir em ordem\n";
        cout << "6 - Imprima Ordenado\n";
        cout << "7 - Sair\n";
        cout << "\nEscolha uma opcao do menu: ";
        cin >> escolha;

        int dado;
        switch (escolha) {
            case 1:
                //Inserir nó na Árvore
                cout << "Digite o valor do no a ser inserido: ";
                cin >> dado;
                //Limpa tela
                this->clearConsole();

                a->insert(dado);
                a->showTree();
                cout << "\n\n";
                break;

            case 2:
                //Remover nó da Árvore
                cout << "Digite o valor do no a ser removido: ";
                cin >> dado;
                this->clearConsole();

                a->remove(dado);
                a->showTree();
                cout << "\n\n";
                break;

            case 3:
                //Deletar Árvore
                this->clearConsole();
                delete a;

                a = new Tree();

                //Teste para atribuir NULL à raiz. Aparentemente mesmo estando nula, a raiz está recebendo "lixo de memória"
                //if( a -> raiz != NULL){
                //	a -> raiz = NULL;
                //}
                //a -> showTree();

                cout << "\n\n";
                break;

            case 4:
                //Mostrar Árvore
                this->clearConsole();
                a->showTree();
                cout << "\n\n";
                break;

            case 5:
                //Exibe os nós em ordem (filho(s) -> pai -> filhos)
                this->clearConsole();
                cout << "Em Ordem: ";
                a->inOrder();
                cout << "\n\n";
                break;

            case 6:
                //Exibir ordenado
                break;

            case 7:
                cout << "\nSaindo...";
                break;

            default:
                cout << "\nOpcao invalida, tente novamente.\n";
                break;

        }
    } while (escolha != 7);

    return 0;
}

void Runner::clearConsole() {
    system("clear");
}