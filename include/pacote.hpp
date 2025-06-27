#ifndef PACOTE_HPP
#define PACOTE_HPP

#include "tadsAuxiliares.hpp"


/*  
    ARMAZENA INFORMAÇÕES SOBRE OS PACOTES, ACHO Q CLASSE EVENTO VAI DE RALO
 */

class Pacote {
    public:
        Pacote();
        ~Pacote();
        void setRota(ListaEncadeada* novaRota);

        private:
        int id; //6digitos
        ListaEncadeada* rota;
    friend class Cliente;
};

#endif