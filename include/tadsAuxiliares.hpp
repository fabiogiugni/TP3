#ifndef TADSAUXILIARES_HPP
#define TADSAUXILIARES_HPP

#include <iostream>
#include <string>
#include <exception>

struct Evento{
    int tempo;
    std::string eventoOuConsulta;
    std::string tipoEvento;     //Em consulta de Clientes, esse é o nome do cliente.
    int idPacote;
    std::string remetente;
    std::string destinatario;
    int armOrigem;
    int armDestino;
    int secaoDestino;
};

struct No{
    int item;
    No* prox;
};

class ListaEncadeada{
    public:
        ListaEncadeada();
        ListaEncadeada(const ListaEncadeada& outra);
        ~ListaEncadeada();
    
        void insereInicio(int item);
        void insereFinal(int item);
        void removeInicio();
        void removeFinal();
        void imprime();
        ListaEncadeada& operator=(const ListaEncadeada& outra);
        int getTamanho();
    
    private:
        No *primeiro;
        No *ultimo;
        int tamanho;
    friend class Cliente;
    friend class Pacote;
    friend class AVLPacotes;
};

#endif