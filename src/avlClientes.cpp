#include <iostream>
#include "avlClientes.hpp"

// Construtor
AVLClientes::AVLClientes() : root(nullptr) {}

// Destrutor
AVLClientes::~AVLClientes() {
    clear(root);
}

// Altura
int AVLClientes::height(Node* node) {
    return node ? node->height : 0;
}

void AVLClientes::updateHeight(Node* node) {
    if (node)
        node->height = 1 + std::max(height(node->left), height(node->right));
}

int AVLClientes::balanceFactor(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// Rotações
AVLClientes::Node* AVLClientes::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

AVLClientes::Node* AVLClientes::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

AVLClientes::Node* AVLClientes::balance(Node* node) {
    if (!node) return nullptr;

    updateHeight(node);

    int bf = balanceFactor(node);

    // Left Left
    if (bf > 1 && balanceFactor(node->left) >= 0)
        return rotateRight(node);

    // Left Right
    if (bf > 1 && balanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Right
    if (bf < -1 && balanceFactor(node->right) <= 0)
        return rotateLeft(node);

    // Right Left
    if (bf < -1 && balanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Inserção
AVLClientes::Node* AVLClientes::insert(Node* node, std::string nomeCliente, int index) {
    if (!node) {
        Cliente novo(nomeCliente);
        novo.pacotes = new ListaEncadeada();
        novo.pacotes->insereFinal(index);
        return new Node(novo);
    }

    if (nomeCliente < node->cliente.nome) {
        node->left = insert(node->left, nomeCliente, index);
    }
    else if (nomeCliente > node->cliente.nome) {
        node->right = insert(node->right, nomeCliente, index);
    }
    else {
        // Já existe
        if (!node->cliente.pacotes)
            node->cliente.pacotes = new ListaEncadeada();
        node->cliente.pacotes->insereFinal(index);
        return node;
    }

    return balance(node);
}

void AVLClientes::inserePacote(const Evento& evento) {
    root = insert(root, evento.remetente, evento.idPacote);
    root = insert(root, evento.destinatario, evento.idPacote);
}

// Busca
AVLClientes::Node* AVLClientes::findNode(Node* node, std::string nomeCliente) const {
    if (!node) return nullptr;
    if (nomeCliente < node->cliente.nome)
        return findNode(node->left, nomeCliente);
    else if (nomeCliente > node->cliente.nome)
        return findNode(node->right, nomeCliente);
    else
        return node;
}

bool AVLClientes::contains(Node* node, std::string nomeCliente) const {
    return findNode(node, nomeCliente) != nullptr;
}

bool AVLClientes::contem(std::string nomeCliente) const {
    return contains(root, nomeCliente);
}

Cliente* AVLClientes::consultaCliente(std::string nomeCliente) const {
    Node* node = findNode(root, nomeCliente);
    if (node)
        return &(node->cliente);
    return nullptr;
}

// Remoção
AVLClientes::Node* AVLClientes::minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

AVLClientes::Node* AVLClientes::remove(Node* node, const Cliente& cliente) {
    if (!node) return nullptr;

    if (cliente.nome < node->cliente.nome)
        node->left = remove(node->left, cliente);
    else if (cliente.nome > node->cliente.nome)
        node->right = remove(node->right, cliente);
    else {
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;
            delete node;
            return temp;
        } else {
            Node* temp = minValueNode(node->right);
            node->cliente = temp->cliente;
            node->right = remove(node->right, temp->cliente);
        }
    }

    return balance(node);
}

void AVLClientes::remover(const Cliente& cliente) {
    root = remove(root, cliente);
}

// Traversal
void AVLClientes::inOrder(Node* node) const {
    if (!node) return;
    inOrder(node->left);
    std::cout << "Cliente: " << node->cliente.nome << std::endl;
    if (node->cliente.pacotes) {
        std::cout << "Pacotes: ";
        node->cliente.pacotes->imprime();
    }
    inOrder(node->right);
}

void AVLClientes::imprimirEmOrdem() const {
    inOrder(root);
}

// Limpa
void AVLClientes::clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

// Dummy
void AVLClientes::imprimirCliente(No* primeiro) const {
    // Ajuste de acordo com a sua ListaEncadeada
}