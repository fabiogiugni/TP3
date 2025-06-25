#ifndef TADSAUXILIARES_HPP
#define TADSAUXILIARES_HPP

#include <iostream>

struct No{
    int item;
    No* prox;
};

class ListaEncadeada{
    public:
        ListaEncadeada();
        ~ListaEncadeada();
    
        void insereInicio(int item);
        void insereFinal(int item);
        void removeInicio();
        void removeFinal();
        void imprime();
    
    private:
        No *primeiro;
        No *ultimo;
        int tamanho;
    friend class ListaAdjacencia;
    friend class Grafo;
    friend class Armazem;
    friend class Pacote;
};

class PilhaEncadeada {
public:
    PilhaEncadeada();  // Construtor
    ~PilhaEncadeada();  // Destruidor

    void Empilha(int item);  // Empilha um item
    int Desempilha();  // Desempilha e retorna um item
    bool Vazio() const;  // Verifica se a pilha está vazia
    void Limpa();  // Limpa a pilha
    bool removePorId(int id);  // Remove um item da pilha pelo ID
    int Tamanho() const;  // Retorna o tamanho da pilha
    void imprime() const;  // Imprime todos os itens da pilha

private:
    No* topo;  // Ponteiro para o topo da pilha
    int tamanho;  // Tamanho da pilha
};

class Fila {
public:
    Fila();
    ~Fila();

    void Enfileira(int valor);
    int Desenfileira();
    bool vazia() const;

private:
    No* primeiro;
    No* ultimo;
};

#endif