#ifndef AVLPACOTES_HPP
#define AVLPACOTES_HPP

#include "pacote.hpp"
#include "tadsAuxiliares.hpp"

class AVLPacotes {
private:
    struct Node {
        Pacote pacote;
        Node* left;
        Node* right;
        int height;
        
        Node(const Pacote& p) : pacote(p), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;
    Evento* eventos;
    int numEventos;

    // Funções auxiliares
    int height(Node* node);
    void updateHeight(Node* node);
    int balanceFactor(Node* node);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* balance(Node* node);
    Node* insert(Node* node, const Pacote& pacote);
    Node* remove(Node* node, const Pacote& pacote);
    Node* minValueNode(Node* node);
    bool contains(Node* node, const Pacote& pacote) const;
    void inOrder(Node* node) const;
    void clear(Node* node);

public:
    AVLPacotes();
    AVLPacotes(Evento* eventos, int numEventos);
    ~AVLPacotes();
    
    // Operações públicas
    void insereEvento(const Evento& evento, int index);
    void remover(const Pacote& pacote);
    bool contem(const Pacote& pacote) const;
    bool estaVazia() const;
    void imprimirEmOrdem() const;
};

#endif