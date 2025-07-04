#ifndef AVLPACOTES_HPP
#define AVLPACOTES_HPP

#include "pacote.hpp"
#include "tadsAuxiliares.hpp"
#include <iomanip>

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
    Node* insert(Node* node, int idPacote, int index);
    Node* remove(Node* node, const Pacote& pacote);
    Node* minValueNode(Node* node);
    bool contains(Node* node, int idPacote) const;
    void inOrder(Node* node) const;
    void clear(Node* node);
    Node* findNode(Node* node, int idPacote) const;

    public:
    AVLPacotes();
    AVLPacotes(Evento* eventos, int numEventos);
    ~AVLPacotes();
    
    // Operações públicas
    void insereEvento(const Evento& evento, int index);
    void consultaPacote(int idPacote) const;
    void remover(const Pacote& pacote);
    bool contem(int idPacote) const;
    bool estaVazia() const;
    void imprimirEmOrdem() const;
    void imprimirPacote(No* primeiro) const;
    void imprimeEvento(const Evento& evento)const;
};

#endif