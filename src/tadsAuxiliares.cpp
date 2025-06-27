#include "tadsAuxiliares.hpp"
#include <stdexcept>

ListaEncadeada::ListaEncadeada(){
    this->tamanho = 0;
    primeiro = nullptr;
    ultimo = nullptr;
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

// Construtor - Inicializa a pilha vazia
PilhaEncadeada::PilhaEncadeada() : topo(nullptr), tamanho(0) {}

// Destruidor - Libera toda a memória utilizada pela pilha
PilhaEncadeada::~PilhaEncadeada() {
    Limpa();
}

// Empilha um item na pilha
void PilhaEncadeada::Empilha(int item) {
    No* novo = new No{item, topo};  // Cria um novo nó com o item
    topo = novo;  // O topo da pilha aponta para o novo nó
    ++tamanho;  // Incrementa o tamanho
}

// Desempilha um item da pilha e retorna seu valor
int PilhaEncadeada::Desempilha() {
    if (Vazio()) {
        throw std::out_of_range("Pilha vazia");
    }

    No* temp = topo;  // Salva o nó do topo
    int item = topo->item;  // Obtém o item do topo
    topo = topo->prox;  // Atualiza o topo para o próximo nó
    delete temp;  // Libera a memória do nó desempilhado
    --tamanho;  // Decrementa o tamanho
    return item;  // Retorna o item desempilhado
}

// Verifica se a pilha está vazia
bool PilhaEncadeada::Vazio() const {
    return topo == nullptr;  // A pilha está vazia se o topo for nulo
}

// Limpa a pilha (remove todos os elementos)
void PilhaEncadeada::Limpa() {
    while (!Vazio()) {
        Desempilha();  // Desempilha até a pilha ficar vazia
    }
}

// Remove um item da pilha com base no valor do ID
bool PilhaEncadeada::removePorId(int id) {
    No* atual = topo;
    No* anterior = nullptr;

    while (atual != nullptr) {
        if (atual->item == id) {  // Se encontrar o item
            if (anterior == nullptr) {
                topo = atual->prox;  // Se for o primeiro item, atualiza o topo
            } else {
                anterior->prox = atual->prox;  // Remove o nó da lista
            }
            delete atual;  // Libera o nó
            --tamanho;  // Decrementa o tamanho
            return true;  // Retorna verdadeiro se o item foi removido
        }
        anterior = atual;
        atual = atual->prox;  // Avança para o próximo nó
    }
    return false;  // Retorna falso se o item não foi encontrado
}

// Retorna o tamanho da pilha
int PilhaEncadeada::Tamanho() const {
    return tamanho;  // Retorna o tamanho atual da pilha
}

void PilhaEncadeada::imprime() const {
    if (Vazio()) {
        std::cout << "Pilha vazia!" << std::endl;
        return;
    }

    No* atual = topo;
    std::cout << "Itens na pilha: ";
    while (atual != nullptr) {
        std::cout << atual->item << " ";  // Imprime o valor do nó atual
        atual = atual->prox;  // Avança para o próximo nó
    }
    std::cout << std::endl;  // Quebra a linha após imprimir todos os itens
}

Fila::Fila() : primeiro(nullptr), ultimo(nullptr) {}

Fila::~Fila() {
    while (primeiro != nullptr) {
        No* temp = primeiro;
        primeiro = primeiro->prox;
        delete temp;
    }
}

void Fila::Enfileira(int valor) {
    No* novo = new No{valor, nullptr};
    if (ultimo != nullptr) {
        ultimo->prox = novo;
    } else {
        primeiro = novo;
    }
    ultimo = novo;
}

int Fila::Desenfileira() {
    if (primeiro == nullptr) throw std::out_of_range("Fila vazia");

    int valor = primeiro->item;
    No* temp = primeiro;
    primeiro = primeiro->prox;
    if (primeiro == nullptr) {
        ultimo = nullptr;
    }
    delete temp;
    return valor;
}

bool Fila::vazia() const {
    return primeiro == nullptr;
}
