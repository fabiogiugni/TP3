#ifndef PACOTE_HPP
#define PACOTE_HPP

#include "tadsAuxiliares.hpp"

class Pacote {
    public:
        Pacote();
        ~Pacote();
    private:
        int id;
        ListaEncadeada* rota; // Index para as posições do vetor original que indicam atualizações do pacote
    friend class Cliente;
};

#endif