#include "tadsAuxiliares.hpp"
#include <stdexcept>

ListaEncadeada::ListaEncadeada(){
    this->tamanho = 0;
    primeiro = nullptr;
    ultimo = nullptr;
}

ListaEncadeada::ListaEncadeada(const ListaEncadeada& outra) : primeiro(nullptr), ultimo(nullptr), tamanho(0) {
    for (No* atual = outra.primeiro; atual != nullptr; atual = atual->prox) {
        this->insereFinal(atual->item);
    }
}

ListaEncadeada::~ListaEncadeada() {
    while (primeiro != nullptr) {
        No* temp = primeiro;
        primeiro = primeiro->prox;
        delete temp;
    }
}

void ListaEncadeada::insereInicio(int item){
    No *novo = new No{item, primeiro};
    primeiro = novo;
    if (ultimo == nullptr)
    {
        ultimo = novo;
    }
    ++tamanho;
}

ListaEncadeada& ListaEncadeada::operator=(const ListaEncadeada& outra) {
    if (this == &outra) return *this;

    // Limpa a lista atual
    while (primeiro != nullptr) {
        No* temp = primeiro;
        primeiro = primeiro->prox;
        delete temp;
    }
    primeiro = ultimo = nullptr;
    tamanho = 0;

    // Copia os elementos da outra lista
    for (No* atual = outra.primeiro; atual != nullptr; atual = atual->prox) {
        this->insereFinal(atual->item);
    }

    return *this;
}


void ListaEncadeada::insereFinal(int item){
    No *nova = new No{item, nullptr};
    if (ultimo != nullptr)
    {
        ultimo->prox = nova;
    }
    else
    {
        primeiro = nova;
    }
    ultimo = nova;
    ++tamanho;
}

void ListaEncadeada::imprime(){
    for (No* atual = primeiro; atual != nullptr; atual = atual->prox) {
        std::cout << atual->item << " ";  // imprime o valor do nó atual
    }
    std::cout << std::endl;  // quebra a linha após imprimir todos os vizinhos
}

void ListaEncadeada::removeInicio() {
    if (primeiro == nullptr) {
        throw std::out_of_range("Lista vazia");
    }

    No* temp = primeiro;  // Salva o nó do início
    primeiro = primeiro->prox;  // O primeiro nó agora é o próximo nó
    if (primeiro == nullptr) {  // Se a lista ficou vazia, o último nó também deve ser nulo
        ultimo = nullptr;
    }
    delete temp;  // Libera a memória do nó removido
    --tamanho;  // Decrementa o tamanho da lista
}

void ListaEncadeada::removeFinal() {
    if (ultimo == nullptr) {
        throw std::out_of_range("Lista vazia");
    }

    if (primeiro == ultimo) {  // Se a lista tem apenas um elemento
        delete primeiro;  // Remove o único nó
        primeiro = ultimo = nullptr;  // A lista fica vazia
    } else {
        No* penultimo = primeiro;
        while (penultimo->prox != ultimo) {  // Percorre até o penúltimo nó
            penultimo = penultimo->prox;
        }
        delete ultimo;  // Libera o último nó
        ultimo = penultimo;  // O penúltimo nó agora é o último
        ultimo->prox = nullptr;  // O próximo do último nó deve ser nulo
    }
    --tamanho;  // Decrementa o tamanho da lista
}

int ListaEncadeada::getTamanho(){
    return tamanho;
}

No* ListaEncadeada::getPrimeiro(){
    return primeiro;
}

No* ListaEncadeada::getUltimo(){
    return ultimo;
}