#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include "tadsAuxiliares.hpp"

struct Cliente {
    std::string nome; // 6 dígitos
    ListaEncadeada* pacotes; // Index para o id do pacote
    
    // Construtores
    Cliente() : nome(""), pacotes(nullptr) {}
    Cliente(std::string nome) : nome(nome), pacotes(nullptr) {}
    Cliente(const Cliente& outro) {
        nome = outro.nome;
        if (outro.pacotes)
            pacotes = new ListaEncadeada(*outro.pacotes);
        else
            pacotes = nullptr;
    }
    ~Cliente(){ delete pacotes; }
    
    // Operadores de comparação
    Cliente& operator=(const Cliente& outro) {
        if (this == &outro) return *this; // proteção contra autoatribuição
        nome = outro.nome;
        delete pacotes; // libera a pacotes atual, se houver
        pacotes = outro.pacotes ? new ListaEncadeada(*outro.pacotes) : nullptr;
        return *this;
    }
    bool operator==(const Cliente& outro) const { return nome == outro.nome; }
    bool operator!=(const Cliente& outro) const { return !(*this == outro); }
    bool operator<(const Cliente& outro) const { return nome < outro.nome; }
    bool operator>(const Cliente& outro) const { return nome > outro.nome; }
    bool operator<=(const Cliente& outro) const { return !(*this > outro); }
    bool operator>=(const Cliente& outro) const { return !(*this < outro); }
    
    friend class AVLClientes;
};

#endif