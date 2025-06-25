#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include "tadsAuxiliares.hpp"

class Cliente {
    public:
        Cliente();
        Cliente(const Cliente& outro);
        Cliente(int tempo, int ident, int org, int dest);
        ~Cliente();
        
        private:
        /*
        O que vem aqui??
        */
    friend class Pacote;
};


#endif