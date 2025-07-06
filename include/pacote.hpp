#ifndef PACOTE_HPP
#define PACOTE_HPP

#include "tadsAuxiliares.hpp"

struct Pacote {
    int id; // 6 dígitos
    ListaEncadeada* rota; // Index para as posições do vetor original
    
    // Construtores
    Pacote() : id(0), rota(nullptr) {}
    Pacote(int id) : id(id), rota(nullptr) {}
    Pacote(const Pacote& outro) {
        id = outro.id;
        if (outro.rota)
            rota = new ListaEncadeada(*outro.rota);
        else
            rota = nullptr;
    }
    ~Pacote(){ delete rota; }
    
    // Operadores de comparação
    Pacote& operator=(const Pacote& outro) {
        if (this == &outro) return *this; // proteção contra autoatribuição
        id = outro.id;
        delete rota; // libera a rota atual, se houver
        rota = outro.rota ? new ListaEncadeada(*outro.rota) : nullptr;
        return *this;
    }
    bool operator==(const Pacote& outro) const { return id == outro.id; }
    bool operator!=(const Pacote& outro) const { return !(*this == outro); }
    bool operator<(const Pacote& outro) const { return id < outro.id; }
    bool operator>(const Pacote& outro) const { return id > outro.id; }
    bool operator<=(const Pacote& outro) const { return !(*this > outro); }
    bool operator>=(const Pacote& outro) const { return !(*this < outro); }
    
    friend class Cliente;
};

#endif