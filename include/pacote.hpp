#ifndef PACOTE_HPP
#define PACOTE_HPP

#include "tadsAuxiliares.hpp"


/*  
    ARMAZENA INFORMAÇÕES SOBRE OS PACOTES, ACHO Q CLASSE EVENTO VAI DE RALO
 */

class Pacote {
    public:
        Pacote();
        Pacote(const Pacote& outro);
        Pacote(int tempo, int ident, int org, int dest);
        ~Pacote();
        Pacote& operator=(const Pacote& outro);
        int getOrigem();
        int getId();
        int getDestino();
        int getTempoPostagem();
        void setRota(ListaEncadeada* novaRota);
        void avancarRota();  // Avança para o próximo armazém
        int getArmazemAtual() const;  // Acessa o próximo armazém (sem remover)
        int getProximoArmazem() const;    //Acessa o próximo armazém destino
        bool chegouAoDestino() const;       // Verifica se a rota acabou
        void imprimirPacote() const;  // Imprime as informações do pacote

        bool postado;
        int tempoPostagem; //6 digitos
        int id; //6digitos
        int armazemOrigem;
        int armazemDestino;
        ListaEncadeada* rota;
    friend class Armazem;
    friend class Grafo;
    friend class Escalonador;
};

#endif