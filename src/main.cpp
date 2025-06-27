#include "tadsAuxiliares.hpp"
#include "pacote.hpp"
#include "cliente.hpp"
#include <fstream>

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
    while (getline(arquivo, linha)) {
        numeroLinhas++; //Contagem de linhas
    }

    arquivo.close();

    Evento *eventos = nullptr;
    eventos = new Evento[numeroLinhas];
    
    std::ifstream arquivo(argv[1]);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo!"<< argv[1] << std::endl;
        return 1;  // Sai do programa se não conseguir abrir o arquivo
    }

    for(int i = 0; i < numeroLinhas; i++){

    }
    
    return 0;
}