#include "tadsAuxiliares.hpp"
#include "pacote.hpp"
#include "cliente.hpp"
#include "avlPacotes.hpp"
#include <fstream>
#include <iomanip>

void imprimirEvento(const Evento& evento) {
    std::cout << "\n--- Registro ---\n";
    std::cout << "Tempo: " << evento.tempo << "\n";
    
    if (evento.eventoOuConsulta == "EV") {
        std::cout << "Tipo: Evento " << evento.tipoEvento << "\n";
        
        if (evento.tipoEvento == "RG" || evento.tipoEvento == "RM") {
            std::cout << "ID Pacote: " << evento.idPacote << "\n";
            std::cout << "Remetente: " << evento.remetente << "\n";
            std::cout << "Destinatário: " << evento.destinatario << "\n";
            std::cout << "Armazém Origem: " << evento.armOrigem << "\n";
            std::cout << "Armazém Destino: " << evento.armDestino << "\n";
        }
        else if (evento.tipoEvento == "AR" || evento.tipoEvento == "TR" || evento.tipoEvento == "UR") {
            std::cout << "ID Pacote: " << evento.idPacote << "\n";
            std::cout << "Armazém Origem: " << evento.armOrigem << "\n";
            std::cout << "Armazém Destino: " << evento.armDestino << "\n";
            if (evento.tipoEvento != "TR") {
                std::cout << "Seção Destino: " << evento.secaoDestino << "\n";
            }
        }
        else if (evento.tipoEvento == "EN") {
            std::cout << "ID Pacote: " << evento.idPacote << "\n";
            std::cout << "Armazém Destino: " << evento.armDestino << "\n";
        }
    }
    else if (evento.eventoOuConsulta == "CL") {
        std::cout << "Tipo: Consulta de Cliente\n";
        std::cout << "Nome: " << evento.tipoEvento << "\n";  // tipoEvento armazena o nome aqui
    }
    else if (evento.eventoOuConsulta == "PC") {
        std::cout << "Tipo: Consulta de Pacote\n";
        std::cout << "ID Pacote: " << evento.idPacote << "\n";
    }
    else {
        std::cout << "Tipo de registro desconhecido\n";
    }
    std::cout << "-----------------------\n";
}

int main(int argc,char *argv[]){

    // Cria um objeto ifstream para abrir o arquivo
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <nome_do_arquivo.wkl>" << std::endl;
        return 1;
    }

    // Usa o argumento da linha de comando como nome do arquivo
    std::ifstream arquivo(argv[1]);

    // Verifica se o arquivo foi aberto corretamente
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo!"<< argv[1] << std::endl;
        return 1;  // Sai do programa se não conseguir abrir o arquivo
    }

    int numeroLinhas = 0;

    std::string linha;
    while (getline(arquivo, linha)) numeroLinhas++; //Contagem de linhas

    arquivo.clear();
    arquivo.seekg(0);

    Evento *eventos = nullptr;
    eventos = new Evento[numeroLinhas];

    for(int i = 0; i < numeroLinhas; i++){
        int tempo = 0;
        arquivo>>tempo;
        eventos[i].tempo = tempo;
        std::string eventoOuConsulta;
        arquivo>>eventoOuConsulta;
        eventos[i].eventoOuConsulta = eventoOuConsulta;
        if(eventoOuConsulta == "CL"){
            std::string nomeCliente;
            arquivo>>nomeCliente;
            eventos[i].tipoEvento = nomeCliente;
        }else if(eventoOuConsulta == "PC"){
            int idPacote;
            arquivo>>idPacote;
            eventos[i].idPacote = idPacote;
            //pacotes.consultaPacote(idPacote);
        }else{
            eventos[i].eventoOuConsulta = eventoOuConsulta;
            std::string tipoEvento;
            arquivo>>tipoEvento;
            if(tipoEvento == "RG"){
                int idPacote;
                arquivo>>idPacote;
                std::string remetente;
                arquivo>>remetente;
                std::string destinatario;
                arquivo>>destinatario;
                int armOrg;
                arquivo>>armOrg;
                int armDest;
                arquivo>>armDest;
                eventos[i].tipoEvento = tipoEvento;
                eventos[i].idPacote = idPacote;
                eventos[i].remetente = remetente;
                eventos[i].destinatario = destinatario;
                eventos[i].armOrigem = armOrg;
                eventos[i].armDestino = armDest;
            }else if(tipoEvento == "AR"){
                int idPacote;
                arquivo>>idPacote;
                int armDest;
                arquivo>>armDest;
                int secaoDest;
                arquivo>>secaoDest;
                eventos[i].tipoEvento = tipoEvento;
                eventos[i].idPacote = idPacote;
                eventos[i].armDestino = armDest;
                eventos[i].secaoDestino = secaoDest;
            }else if(tipoEvento == "RM"){
                int idPacote;
                arquivo>>idPacote;
                int armDest;
                arquivo>>armDest;
                int secaoDest;
                arquivo>>secaoDest;
                eventos[i].tipoEvento = tipoEvento;
                eventos[i].idPacote = idPacote;
                eventos[i].armDestino = armDest;
                eventos[i].secaoDestino = secaoDest;
            }else if(tipoEvento == "UR"){
                int idPacote;
                arquivo>>idPacote;
                int armDest;
                arquivo>>armDest;
                int secaoDest;
                arquivo>>secaoDest;
                eventos[i].tipoEvento = tipoEvento;
                eventos[i].idPacote = idPacote;
                eventos[i].armDestino = armDest;
                eventos[i].secaoDestino = secaoDest;
            }else if(tipoEvento == "TR"){
                int idPacote;
                arquivo>>idPacote;
                int armOrg;
                arquivo>>armOrg;
                int armDest;
                arquivo>>armDest;
                eventos[i].tipoEvento = tipoEvento;
                eventos[i].idPacote = idPacote;
                eventos[i].armOrigem = armOrg;
                eventos[i].armDestino = armDest;
            }else{
                int idPacote;
                arquivo>>idPacote;
                int armDest;
                arquivo>>armDest;
                eventos[i].tipoEvento = tipoEvento;
                eventos[i].idPacote = idPacote;
                eventos[i].armDestino = armDest;
            }
        }
    }

    AVLPacotes pacotes(eventos,numeroLinhas);
    /*std::cout<<"vetor de eventos lido"<<std::endl;
    for(int i = 0; i < numeroLinhas; i++){
        imprimirEvento(pacotes.eventos[i]);
    }*/
    arquivo.close();
    //Começa leitura
    for(int i = 0; i < numeroLinhas; i++){
        if(eventos[i].eventoOuConsulta == "CL"){
            std::cout << std::setw(7) << std::setfill('0') << eventos[i].tempo << " "<< eventos[i].eventoOuConsulta << " "<< eventos[i].tipoEvento <<std::endl;
            //clientes.consultaCliente(eventos[i].tipoEvento);    //tipoEvento armazena nome do cliente
        }else if(eventos[i].eventoOuConsulta == "PC"){
            std::cout << std::setw(7) << std::setfill('0') << eventos[i].tempo <<" "<< eventos[i].eventoOuConsulta <<" "<< std::setw(3) << std::setfill('0') << eventos[i].idPacote<<std::endl;
            pacotes.consultaPacote(eventos[i].idPacote);    //tipoEvento armazena nome do cliente
        }
        else if(eventos[i].eventoOuConsulta == "EV"){
            pacotes.insereEvento(eventos[i],i);
            //clientes.insereEvento(eventos[i]);
        }
    }
    return 0;
}