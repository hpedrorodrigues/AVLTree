#include "Tree.h"

/**
 * Constrói uma árvore com raiz nula.
 */
Tree::Tree() {
    this->root = NULL;
}

/**
 * Destrói toda a árvore.
 *
 * Antes de sair do destrutor da árvore é exibida a mensagem de "Árvore Vazia".
 */
Tree::~Tree() {
    while (this->root != NULL) {

        remove(this->root->getData());
    }

    if (this->isEmpty()) {

        cout << "Empty Tree!";
    }
}

/**
 * Informa a altura da árvore.
 */
int Tree::getHeight() {
    return heightRec(this->root);
}

/**
 * Insere um novo nó na árvore com o valor informado.
 */
bool Tree::insert(int data) {
    this->root = insert(data, root);

    return true;
}

/**
 * Remove o nó com o valor informado.
 *
 * Após toda remoção a árvore é rebalanceada.
 */
void Tree::remove(int data) {
    Noh *aux = this->root;

    do {
        if (aux->getData() == data) {
            break;
        }

        aux = (data <= aux->getData()) ? aux->getLeft() : aux->getRight();
    } while (aux != NULL);

    if (aux == NULL) {
        return;
    }

    if (aux->getLeft() == NULL && aux->getRight() == NULL) {
        if (aux == this->root) {
            this->root = NULL;
        }

        aux->setFather(searchFather(aux->getData()));

        delete aux;
    } else {

        int auxData;

        if (aux->getRight() != NULL) {

            Noh *left = moreLeft(aux->getRight());
            auxData = left->getData();

            remove(left->getData());
        } else {

            Noh *right = moreRight(aux->getLeft());
            auxData = right->getData();

            remove(right->getData());
        }

        aux->setData(auxData);
    }

    if (this->root != NULL) {
        balance(this->root);
    }
}

/**
 * Realiza o balanceamento de toda a árvore.
 *
 * Se o fator de balanceamento for maior ou igual a 2,
 * é verificado se o fator de balanceamento do filho à esquerda é maior que 0.
 * Se sim, então apenas uma rotação simples à direita é realizada, se não, uma rotação dupla EsquerdaDireita é
 * realizada.
 *
 * Se o fator de balanceamento for menor ou igual a -2,
 * é verificado se o fb do filho à direita é menor que 0.
 * Se sim, então apenas uma rotação simples à esquerda é realizada, se não, uma rotação dupla DireitaEsquerda é
 * realizada.
 */
Noh *Tree::balance(Noh *noh) {
    if (this->getBalanceFactor(noh) >= 2) {

        noh = (this->getBalanceFactor(noh->getLeft()) > 0) ? rotRight(noh) : rotLeftRight(noh);

    } else if (this->getBalanceFactor(noh) <= -2) {

        noh = (this->getBalanceFactor(noh->getRight()) < 0) ? rotLeft(noh) : rotRightLeft(noh);
    }

    this->root = noh;

    return this->root;
}

/**
 * Realiza uma rotação a direita.
 */
Noh *Tree::rotRight(Noh *noh) {
    Noh *left = noh->getLeft();

    noh->setLeft(left->getRight());

    left->setRight(noh);

    return left;
}

/**
 * Realiza uma rotação a esquerda.
 */
Noh *Tree::rotLeft(Noh *noh) {
    Noh *right = noh->getRight();

    noh->setRight(right->getLeft());

    right->setLeft(noh);

    return right;
}

/**
 * Realiza duas rotações: Esquerda e depois Direita.
 *
 * Nessa rotação dupla, primeiro é passado como parâmetro o filho "penso" à esquerda,
 * depois o nó problemático que será passado.
 */
Noh *Tree::rotLeftRight(Noh *noh) {
    noh->setLeft(rotLeft(noh->getLeft()));

    return rotRight(noh);
}

/**
 * Realiza duas rotações: Direita e depois Esquerda.
 *
 * Nessa rotação dupla, primeiro é passado como parâmetro o filho "penso" à direita,
 * depois o nó problemático que será passado.
 */
Noh *Tree::rotRightLeft(Noh *noh) {
    noh->setRight(rotRight(noh->getRight()));

    return rotLeft(noh);
}

/**
 * Realiza uma busca pelo pai do nó com o dado informado em toda árvore.
 */
Noh *Tree::searchFather(int data) {
    Noh *aux = this->root;
    Noh *previous = NULL;

    while (aux != NULL && aux->getData() != data) {

        previous = aux;

        aux = (aux->getData() < data) ? aux->getRight() : aux->getLeft();
    }

    /**
     * Se esse novo valor do auxiliar não for nulo e seu valor for igual ao do dado passado,
     * então o "anterior"(guarda o valor "pai" dos nós filhos) é retornado, senão searchFather retorna NULL.
     */
    return (aux != NULL && aux->getData() == data) ? previous : NULL;
}

/**
 * Exibe todos os dados da árvore.
 */
void Tree::showTree() {
    if (this->isEmpty()) {

        cout << "Empty Tree!\n\n";
        return;
    }

    cout << this->root->getData() << "(Root)\n";

    this->showSubTreeRec(this->root->getLeft(), this->SEPARATOR);
    this->showSubTreeRec(this->root->getRight(), this->SEPARATOR);
}

/**
 * Exibe todos os nós filhos do nó informado, utilizando o separador informado.
 */
void Tree::showSubTreeRec(Noh *noh, string separator) {
    if (noh != NULL) {
        Noh *father = this->searchFather(noh->getData());

        cout << separator << noh->getData();
        cout << ((noh == father->getLeft()) ? "(Left)" : "(Right)") << "\n";

        string tabWithSeparator = "     " + separator;

        showSubTreeRec(noh->getLeft(), tabWithSeparator);
        showSubTreeRec(noh->getRight(), tabWithSeparator);
    }
}

/**
 * Exibe os dados da árvore seguindo a referência de pré-ordem (Pai, Filho esquerdo, Filho Direito).
 */
void Tree::preOrder() {
    preOrderRec(this->root);
}

/**
 * Exibe os dados da árvore seguindo a referência de em-ordem (Filho esquerdo, Pai, Filho Direito).
 */
void Tree::inOrder() {
    inOrderRec(this->root);
}

/**
 * Exibe os dados da árvore seguindo a referência de pós-ordem (Filho esquerdo, Filho Direito, Pai).
 */
void Tree::posOrder() {
    posOrderRec(this->root);
}

/**
 * Informa a altura da árvore a partir do nó informado.
 */
int Tree::heightRec(Noh *noh) {
    if (noh == NULL) {
        return 0;
    }

    int heightLeft = heightRec(noh->getLeft());
    int heightRight = heightRec(noh->getRight());

    return this->max(heightLeft, heightRight) + 1;
}

/**
 * Exibe os dados da árvore seguindo a referência de pré-ordem (Pai, Filho esquerdo, Filho Direito),
 * a partir do nó informado.
 */
void Tree::preOrderRec(Noh *noh) {
    if (noh != NULL) {

        cout << noh->getData() << ", ";

        this->preOrderRec(noh->getLeft());

        this->preOrderRec(noh->getRight());
    }
}

/**
 * Exibe os dados da árvore seguindo a referência de em-ordem (Filho esquerdo, Pai, Filho Direito),
 * a partir do nó informado.
 */
void Tree::inOrderRec(Noh *noh) {
    if (noh != NULL) {

        this->inOrderRec(noh->getLeft());

        cout << noh->getData() << ", ";

        this->inOrderRec(noh->getRight());
    }
}

/**
 * Exibe os dados da árvore seguindo a referência de pós-ordem (Filho esquerdo, Filho Direito, Pai),
 * a partir do nó informado.
 */
void Tree::posOrderRec(Noh *noh) {
    if (noh != NULL) {

        this->posOrderRec(noh->getLeft());

        this->posOrderRec(noh->getRight());

        cout << noh->getData() << ", ";
    }
}

/**
 * Retorna o nó mais à esquerda da árvore a partir do nó informado.
 */
Noh *Tree::moreLeft(Noh *noh) {
    Noh *aux = noh;

    if (noh != NULL) {

        while (aux->getLeft() != NULL) {

            aux = aux->getLeft();
        }
    }

    return aux;
}

/**
 * Retorna o nó mais à direita da árvore a partir do nó informado.
 */
Noh *Tree::moreRight(Noh *noh) {
    Noh *aux = noh;

    if (noh != NULL) {

        while (aux->getRight() != NULL) {

            aux = aux->getRight();
        }
    }

    return aux;
}

/**
 * Informa se a árvore está vazia.
 */
bool Tree::isEmpty() {

    return this->root == NULL;
}

/**
 * Informa o maior valor entre os dois informados.
 */
int Tree::max(int a, int b) {
    return a > b ? a : b;
}

/**
 * Calcula o valor do fator de balanceamento.
 */
int Tree::getBalanceFactor(Noh *noh) {
    int heightLeft = heightRec(noh->getLeft());
    int heightRight = heightRec(noh->getRight());

    return heightLeft - heightRight;
}

/**
 * Insere um nó na árvore.
 *
 * Se o nó passado como parâmetro for nulo, logo um nó é adicionado contendo o dado.
 * Se o dado passado for menor que o dado de um nó já existente, este será inserido à esquerda do nó existente.
 * Senão será inserido à direita do nó existente.
 *
 * A cada inserção a árvore é balanceada, se necessário.
 */
Noh *Tree::insert(int dado, Noh *noh) {
    if (noh == NULL) {

        noh = new Noh(dado);
    } else if (dado < noh->getData()) {

        noh->setLeft(insert(dado, noh->getLeft()));
    } else if (dado > noh->getData()) {

        noh->setRight(insert(dado, noh->getRight()));
    }

    noh = balance(noh);

    return noh;
}