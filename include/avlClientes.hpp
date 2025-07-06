#ifndef AVLCLIENTES_HPP
#define AVLCLIENTES_HPP

#include "cliente.hpp"
#include "tadsAuxiliares.hpp"
#include "avlPacotes.hpp"
#include <iomanip>

class AVLClientes {
private:
    struct Node {
        Cliente cliente;
        Node* left;
        Node* right;
        int height;
        
        Node(const Cliente& c) : cliente(c), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    // Funções auxiliares
    int height(Node* node);
    void updateHeight(Node* node);
    int balanceFactor(Node* node);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);         
    Node* balance(Node* node);
    Node* insert(Node* node, std::string nomeCliente, int index);
    Node* remove(Node* node, const Cliente& cliente);
    Node* minValueNode(Node* node);
    bool contains(Node* node, std::string nomeCliente) const;
    void inOrder(Node* node) const;
    void clear(Node* node);
    Node* findNode(Node* node, std::string nomeCliente) const;

public:
    AVLClientes();
    ~AVLClientes();
    
    // Operações públicas
    void inserePacote(const Evento& evento);
    Cliente* consultaCliente(std::string nomeCliente) const;
    void remover(const Cliente& cliente);
    bool contem(std::string nomeCliente) const;
    bool estaVazia() const;
    void imprimirEmOrdem() const;
    void imprimirCliente(No* pacote) const;
};

#endif
