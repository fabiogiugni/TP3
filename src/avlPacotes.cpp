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

AVLPacotes::Node* AVLPacotes::insert(Node* node, int idPacote, int index) {
    if (node == nullptr) {
        // Criar novo nó com o pacote e a rota contendo esse índice
        Pacote novoPacote(idPacote);
        novoPacote.rota = new ListaEncadeada();
        novoPacote.rota->insereFinal(index);
        return new Node(novoPacote);
    }

    if (idPacote < node->pacote.id) {
        node->left = insert(node->left, idPacote, index);
    } 
    else if (idPacote > node->pacote.id) {
        node->right = insert(node->right, idPacote, index);
    } 
    else {
        // Se já existe, só adiciona o índice na lista
        if (!node->pacote.rota) {
            node->pacote.rota = new ListaEncadeada();
        }
        node->pacote.rota->insereFinal(index);
        return node;
    }

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

AVLPacotes::Node* AVLPacotes::findNode(Node* node, int idPacote) const {
    if (!node) return nullptr;
    if (idPacote < node->pacote.id)
        return findNode(node->left, idPacote);
    else if (idPacote > node->pacote.id)
        return findNode(node->right, idPacote);
    else
        return node;
}

// Encontra o nó com valor mínimo
AVLPacotes::Node* AVLPacotes::minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

// Busca auxiliar
bool AVLPacotes::contains(Node* node, int idPacote) const {
    if (!node) return false;
    if (idPacote < node->pacote.id)
        return contains(node->left, idPacote);
    else if (idPacote > node->pacote.id)
        return contains(node->right, idPacote);
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
    // Só delega para insert, que resolve tudo
    root = insert(root, evento.idPacote, index);
}

void AVLPacotes::remover(const Pacote& pacote) {
    root = remove(root, pacote);
}

bool AVLPacotes::contem(int idPacote) const {
    return contains(root, idPacote);
}

bool AVLPacotes::estaVazia() const {
    return root == nullptr;
}

void AVLPacotes::imprimirEmOrdem() const {
    inOrder(root);
}

void AVLPacotes::imprimirPacote(No* primeiro) const {
    for (No* atual = primeiro; atual != nullptr; atual = atual->prox) {
        imprimeEvento(eventos[atual->item]);  // imprime o valor do nó atual
    }
}

void AVLPacotes::imprimirPrimeiro(int idPacote) const{
    Node* aux = findNode(root, idPacote);
    imprimeEvento(eventos[aux->pacote.rota->primeiro->item]);
}

void AVLPacotes::imprimirUltimo(int idPacote) const{
    Node* aux = findNode(root, idPacote);
    imprimeEvento(eventos[aux->pacote.rota->ultimo->item]);
}


Evento AVLPacotes::acessaUltimo(int idPacote) const{
    Node* aux = findNode(root, idPacote);
    return (eventos[aux->pacote.rota->ultimo->item]);
}

void AVLPacotes::imprimeEvento(const Evento& evento) const {
    std::cout << std::setw(7) << std::setfill('0') << evento.tempo << " ";

    if (evento.eventoOuConsulta == "CL") {
        std::cout << "CL " << evento.tipoEvento;
    } else if (evento.eventoOuConsulta == "PC") {
        std::cout << "PC " << std::setw(3) << std::setfill('0') << evento.idPacote;
    } else if (evento.eventoOuConsulta == "EV") {
        std::cout << "EV " << evento.tipoEvento << " ";
        
        if (evento.tipoEvento == "RG") {
            std::cout << std::setw(3) << std::setfill('0') << evento.idPacote << " "
                      << evento.remetente << " " << evento.destinatario << " "
                      << std::setw(3) << std::setfill('0') << evento.armOrigem << " "
                      << std::setw(3) << std::setfill('0') << evento.armDestino;
        } else if (evento.tipoEvento == "AR" || evento.tipoEvento == "RM" || evento.tipoEvento == "UR") {
            std::cout << std::setw(3) << std::setfill('0') << evento.idPacote << " "
                      << std::setw(3) << std::setfill('0') << evento.armDestino << " "
                      << std::setw(3) << std::setfill('0') << evento.secaoDestino;
        } else if (evento.tipoEvento == "TR") {
            std::cout << std::setw(3) << std::setfill('0') << evento.idPacote << " "
                      << std::setw(3) << std::setfill('0') << evento.armOrigem << " "
                      << std::setw(3) << std::setfill('0') << evento.armDestino;
        } else if (evento.tipoEvento == "EN") {
            std::cout << std::setw(3) << std::setfill('0') << evento.idPacote << " "
                      << std::setw(3) << std::setfill('0') << evento.armDestino;
        } else {
            std::cout << "(Evento desconhecido)";
        }
    } else {
        std::cout << "(Evento desconhecido)";
    }

    std::cout << std::endl;
}


void AVLPacotes::consultaPacote(int idPacote) const {
    
    Node* node = findNode(root, idPacote);
    if (node) {
        std::cout <<node->pacote.rota->getTamanho()<<std::endl;
        if (node->pacote.rota) {
            imprimirPacote(node->pacote.rota->primeiro);
        } else {
            std::cout << "(sem rota armazenada)";
        }
    } else {
        std::cout << "Pacote com ID " << idPacote << " NÃO encontrado na árvore.\n";
    }
}