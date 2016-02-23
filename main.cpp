#include <iostream>

using namespace std;

class Noh {
public:
    int dado;

public:
    Noh *esquerda, *direita, *pai;

    Noh(int dado, Noh *e = NULL, Noh *d = NULL, Noh *p = NULL) {
        this->dado = dado;
        this->esquerda = e;
        this->direita = d;
        this->pai = p;
    };

    ~Noh() {
        // Noh *auxPai = this;
        if (this->pai != NULL) {
            if (this->pai->esquerda == this) {
                this->pai->esquerda = NULL;
            } else {
                this->pai->direita = NULL;
            }
        }
    };

    int getDado() {
        return this->dado;
    };

    void setDado(int dado) {
        this->dado = dado;
    };
};

class Arvore {
public:
    Noh *raiz;

    int alturaRec(Noh *no) {
        if (no == NULL) {
            return 0;
        }

        int hed;
        //A altura do(s) nó(s) à esquerda será(ão) atribuídos a variável he
        int he = alturaRec(no->esquerda);

        //A altura do(s) nó(s) à direita será(ão) atribuídos a variável hd
        int hd = alturaRec(no->direita);

        //A altura com maior valor será retornado e somada a 1, que corresponde À altura do nó raiz
        hed = max(he, hd);
        return 1 + hed;
    };

    void preOrdemRec(Noh *aux) {
        if (aux != NULL) {
            //Exibe pai -> filho(s)
            cout << aux->getDado() << ", ";
            preOrdemRec(aux->esquerda);
            preOrdemRec(aux->direita);
        }
    };

    void emOrdemRec(Noh *aux) {
        if (aux != NULL) {
            //Exibe filho(s) -> pai -> filhos
            emOrdemRec(aux->esquerda);
            cout << aux->getDado() << ", ";
            emOrdemRec(aux->direita);
        }
    };

    void posOrdemRec(Noh *aux) {
        if (aux != NULL) {
            //Exibe filho(s) -> pai
            posOrdemRec(aux->esquerda);
            posOrdemRec(aux->direita);
            cout << aux->getDado() << ", ";
        }
    };

    Noh *maisEsquerda(Noh *noh) {
        //Retorna o nó mais à esquerda da árvore
        Noh *aux = noh;
        if (noh != NULL) {
            while (aux->esquerda != NULL) {
                aux = aux->esquerda;
            }
        }
        return aux;
    }

    Noh *maisDireita(Noh *noh) {
        //Retorna o nó mais à direita da árvore
        Noh *aux = noh;
        if (noh != NULL) {
            while (aux->direita != NULL) {
                aux = aux->direita;
            }
        }
        return aux;
    };

    bool estaVazia() {
        return this->raiz == NULL;
    };

    int max(int a, int b) {
        if (a > b) {
            return a;
        } else {
            return b;
        }
    };

    int getFb(Noh *noh) {
        int he = alturaRec(noh->esquerda);
        int hd = alturaRec(noh->direita);
        return he - hd;
    };

    Noh *inserir(int dado, Noh *noh) {
        //Se o no passado como parâmetro for nulo, logo um nó é adicionando contendo o dado
        if (noh == NULL) {
            noh = new Noh(dado);
            //Se o dado passado for menor que dado de um nó já existente, este será inserido à esquerda do nó existente
            //Senão, será inserido à direita do nó existente
        } else if (dado < noh->getDado()) {
            noh->esquerda = inserir(dado, noh->esquerda);
        } else if (dado > noh->getDado()) {
            noh->direita = inserir(dado, noh->direita);
        }
        //A cada inserção a árvore é balanceada, se necessário.
        noh = balancear(noh);
        return noh;
    };

public:
    Arvore() {
        this->raiz = NULL;
    };

    ~Arvore() {
        while (raiz != NULL) {
            remover(raiz->dado);
        }

        //Antes de sair do destrutor da árvore é retornado a mensagem de "Árvore Vazia"
        if (raiz == NULL) {
            cout << "Arvore Vazia!";
        }
    };

    int getAltura() {
        return alturaRec(raiz);
    };

    bool inserir(int dado) {
        //A cada inserção e balanceamento feito, o valor da raiz da árvore é atualizado
        this->raiz = inserir(dado, raiz);
        return true;
    };

    void remover(int dado) {
        Noh *aux = this->raiz;
        do {
            if (aux->getDado() == dado) {
                break;
            }

            if (dado <= aux->getDado()) {
                aux = aux->esquerda;
            } else {
                aux = aux->direita;
            }
        } while (aux != NULL);

        if (aux == NULL) {
            return;
        }

        if (aux->esquerda == NULL && aux->direita == NULL) {
            //Nó folha
            if (aux == this->raiz) {
                this->raiz = NULL;
            }
            //Busca um nó-pai, se existir, e ele valor é passado para o destrutor
            aux->pai = buscarPai(aux->dado);

            //Se o nó-pai não for encontrado, o raiz permanece nula e a árvore estará vazia
            //	if(aux -> pai != NULL){
            delete aux;
            //	}
        } else {
            //Nó interno
            int tdado;
            if (aux->direita != NULL) {
                Noh *esq = maisEsquerda(aux->direita);
                tdado = esq->getDado();
                remover(esq->dado);
            } else {
                Noh *dir = maisDireita(aux->esquerda);
                tdado = dir->getDado();
                remover(dir->getDado());
            }
            aux->setDado(tdado);
        }

        //Após toda remoção a árvore é "re - balanceada"
        if (this->raiz != NULL) {
            balancear(this->raiz);
        }
    };

    Noh *balancear(Noh *noh) {
        //Se o fb for maior ou igual a 2 é verificado se o fb do filho à esquerda é maior que 0
        //Se sim, então apenas uma rotação simples à direita é realizada, se não, uma rotação dupla EsquerdaDireita é realizada
        if (this->getFb(noh) >= 2) {
            if (this->getFb(noh->esquerda) > 0) {
                noh = rotDireita(noh);
            } else {
                noh = rotEsquerdaDireita(noh);
            }

            //Se o fb for menor ou igual a -2 é verificado se o fb do filho à direita é menor que 0
            //Se sim, então apenas uma rotação simples à esquerda é realizada, se não, uma rotação dupla DireitaEsquerda é realizada
        } else if (this->getFb(noh) <= -2) {
            if (this->getFb(noh->direita) < 0) {
                noh = rotEsquerda(noh);
            } else {
                noh = rotDireitaEsquerda(noh);
            }
        }
        //Atualiza o valor da raiz da árvore
        this->raiz = noh;

        return this->raiz;
    };

    //Rotação simples à direita
    Noh *rotDireita(Noh *noh) {
        Noh *esquerda = noh->esquerda;
        noh->esquerda = esquerda->direita;
        esquerda->direita = noh;
        return esquerda;
    };

    //Rotação simples à esquerda
    Noh *rotEsquerda(Noh *noh) {
        Noh *direita = noh->direita;
        noh->direita = direita->esquerda;
        direita->esquerda = noh;
        return direita;
    };

    Noh *rotEsquerdaDireita(Noh *noh) {
        //Nessa rotação dupla, primeiro é passado como parâmetro o filho "penso" à esquerda,
        //Depois o nó problemático que será passado
        noh->esquerda = rotEsquerda(noh->esquerda);
        return rotDireita(noh);
    };

    Noh *rotDireitaEsquerda(Noh *noh) {
        //Nessa rotação dupla, primeiro é passado como parâmetro o filho "penso" à direita,
        //Depois o nó problemático que será passado
        noh->direita = rotDireita(noh->direita);
        return rotEsquerda(noh);
    };

    Noh *buscarPai(int dado) {
        //O nó auxiliar é criado para guardar a raiz da árvore
        Noh *aux = this->raiz;
        //O nó "anterior" é criado guardando NULL
        Noh *anterior = NULL;

        //Enquanto o nó auxiliar não for nulo e o valor desse nó NÃO for igual ao dado passado como parâmetro,
        //então o "anterior" recebe o nó auxiliar
        while (aux != NULL && !(aux->getDado() == dado)) {
            anterior = aux;
            //Se o valor desse nó auxiliar for menor que o valor do dado passado então auxiliar recebe o valor à sua direita
            //Senão, auxiliar recebe o valor à sua esquerda
            if (aux->getDado() < dado) {
                aux = aux->direita;
            } else {
                aux = aux->esquerda;
            }
        }

        //Se esse novo valor do auxiliar não for nulo e seu valor for igual ao do dado passado,
        //então o "anterior"(guarda o valor "pai" dos nós filhos) é retornado, senão buscarPai retorna NULL
        if (aux != NULL && aux->getDado() == dado) {
            return anterior;
        } else {
            return NULL;
        }
    };

    void mostrarArvore() {
        //Verifica se a raiz da árvore é nula
        //if (this -> estaVazia()){
        if (this->raiz == NULL) {
            cout << "Arvore vazia!\n\n";
            return;
        }

        string separador = "  |__";

        //Exibe o valor da raiz da árvore
        cout << this->raiz->getDado() << "(Raiz)\n";

        //Passa como parâmetro o(s) nó(s) à esquerda da raiz e a string "separador"
        mostrarSubArvore(this->raiz->esquerda, separador);

        //Passa como parâmetro o(s) nó(s) à direita da raiz e a string "separador"
        mostrarSubArvore(this->raiz->direita, separador);
    };

    void mostrarSubArvore(Noh *noh, string separador) {
        if (noh != NULL) {
            //Busca o pai do nó partir de seu valor
            Noh *pai = this->buscarPai(noh->getDado());

            //Exibe a concatenação da string "separador" e o valor do nó
            cout << separador << noh->getDado();

            //Se o nó passado for igual ao valor do nó à esquerda do pai então é exibido "(Esquerda)", se não, "(Direita)"
            if (noh == pai->esquerda) {
                cout << "(Esquerda)" << "\n";
            } else {
                cout << "(Direita)" << "\n";
            }

            //Concatenação de "espaço" e a string "separador"
            string tabComSeparador = "     " + separador;

            //Os nós à esquerda e a direita do nó passado como parâmetro serão chamados com a string tabComSeparador
            //Se existirem serão exibidos em tela
            mostrarSubArvore(noh->esquerda, tabComSeparador);
            mostrarSubArvore(noh->direita, tabComSeparador);
        }
    };

    void preOrdem() {
        preOrdemRec(this->raiz);
    };

    void emOrdem() {
        emOrdemRec(this->raiz);
    };

    void posOrdem() {
        posOrdemRec(this->raiz);
    };
};


int main() {
    //Criando uma instância da classe Árvore
    Arvore *a = new Arvore();

    /*
    //insere e remover nó constantemente
    int i =0;
    while(i == 0){
            a->inserir(3);
            a->remover(3);
    }
    */

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
                system("cls || clear");

                a->inserir(dado);
                a->mostrarArvore();
                cout << "\n\n";
                break;

            case 2:
                //Remover nó da Árvore
                cout << "Digite o valor do no a ser removido: ";
                cin >> dado;
                system("cls || clear");

                a->remover(dado);
                a->mostrarArvore();
                cout << "\n\n";
                break;

            case 3:
                //Deletar Árvore
                system("cls || clear");
                delete a;

                a = new Arvore();

                //Teste para atribuir NULL à raiz. Aparentemente mesmo estando nula, a raiz está recebendo "lixo de memória"
                //if( a -> raiz != NULL){
                //	a -> raiz = NULL;
                //}
                //a -> mostrarArvore();

                cout << "\n\n";
                break;

            case 4:
                //Mostrar Árvore
                system("cls || clear");
                a->mostrarArvore();
                cout << "\n\n";
                break;

            case 5:
                //Exibe os nós em ordem (filho(s) -> pai -> filhos)
                system("cls || clear");
                cout << "Em Ordem: ";
                a->emOrdem();
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
