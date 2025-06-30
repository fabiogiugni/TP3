#include <iostream>
#include "avlPacotes.hpp"

// Construtor
AVLPacotes::AVLPacotes() : root(nullptr), eventos(nullptr), numEventos (0) {}

AVLPacotes::AVLPacotes(Evento* eventos,int numEventos) : root(nullptr), eventos(eventos), numEventos(numEventos) {}

// Destrutor
AVLPacotes::~AVLPacotes() {
    clear(root);
}

// Função auxiliar: retorna altura de um nó
int AVLPacotes::height(Node* node) {
    return node ? node->height : 0;
}

// Atualiza a altura de um nó
void AVLPacotes::updateHeight(Node* node) {
    if (node)
        node->height = 1 + std::max(height(node->left), height(node->right));
}

// Calcula o fator de balanceamento
int AVLPacotes::balanceFactor(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// Rotação simples à direita
AVLPacotes::Node* AVLPacotes::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Rotação simples à esquerda
AVLPacotes::Node* AVLPacotes::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Balanceamento de um nó
AVLPacotes::Node* AVLPacotes::balance(Node* node) {
    if (!node) return nullptr;

    updateHeight(node);

    int balance = balanceFactor(node);

    // Casos de desbalanceamento
    // Left Left
    if (balance > 1 && balanceFactor(node->left) >= 0)
        return rotateRight(node);

    // Left Right
    if (balance > 1 && balanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Right
    if (balance < -1 && balanceFactor(node->right) <= 0)
        return rotateLeft(node);

    // Right Left
    if (balance < -1 && balanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Inserção auxiliar
AVLPacotes::Node* AVLPacotes::insert(Node* node, const Pacote& pacote) {
    if (!node)
        return new Node(pacote);

    if (pacote < node->pacote)
        node->left = insert(node->left, pacote);
    else if (pacote > node->pacote)
        node->right = insert(node->right, pacote);
    else
        return node; // não insere duplicado

    return balance(node);
}

// Remoção auxiliar
AVLPacotes::Node* AVLPacotes::remove(Node* node, const Pacote& pacote) {
    if (!node)
        return nullptr;

    if (pacote < node->pacote)
        node->left = remove(node->left, pacote);
    else if (pacote > node->pacote)
        node->right = remove(node->right, pacote);
    else {
        // Encontrou o nó
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;
            delete node;
            return temp;
        } else {
            // Dois filhos: encontra sucessor em ordem
            Node* temp = minValueNode(node->right);
            node->pacote = temp->pacote;
            node->right = remove(node->right, temp->pacote);
        }
    }

    return balance(node);
}

// Encontra o nó com valor mínimo
AVLPacotes::Node* AVLPacotes::minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

// Busca auxiliar
bool AVLPacotes::contains(Node* node, const Pacote& pacote) const {
    if (!node) return false;
    if (pacote < node->pacote)
        return contains(node->left, pacote);
    else if (pacote > node->pacote)
        return contains(node->right, pacote);
    else
        return true;
}

// Impressão in-order auxiliar
void AVLPacotes::inOrder(Node* node) const {
    if (!node) return;
    inOrder(node->left);
    std::cout << "Pacote ID: " << node->pacote.id << std::endl;
    inOrder(node->right);
}

// Limpa a árvore recursivamente
void AVLPacotes::clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

// Chamadas públicas
void AVLPacotes::insereEvento(const Evento& evento, int index) {
    Node* atual = root;

    // Busca na árvore para ver se o pacote já existe
    while (atual) {
        if (evento.idPacote < atual->pacote.id) {
            atual = atual->left;
        } else if (evento.idPacote > atual->pacote.id) {
            atual = atual->right;
        } else {
            // Pacote já existe na árvore
            if (!atual->pacote.rota) {
                atual->pacote.rota = new ListaEncadeada();
            }
            atual->pacote.rota->insereFinal(index);
            return;
        }
    }

    // Pacote ainda não existe na árvore: cria novo
    Pacote novoPacote(evento.idPacote);
    novoPacote.rota = new ListaEncadeada();
    novoPacote.rota->insereFinal(index);

    // Insere o novo pacote na AVL
    root = insert(root, novoPacote);
}


void AVLPacotes::remover(const Pacote& pacote) {
    root = remove(root, pacote);
}

bool AVLPacotes::contem(const Pacote& pacote) const {
    return contains(root, pacote);
}

bool AVLPacotes::estaVazia() const {
    return root == nullptr;
}

void AVLPacotes::imprimirEmOrdem() const {
    inOrder(root);
}
