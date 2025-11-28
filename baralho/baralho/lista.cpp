#include "Lista.h"
#include <iostream>
#include <string>

using namespace std;

// --- Construtor e Funções Auxiliares ---

template <class T>
Lista<T>::Lista() {
    inicio = nullptr;
    fim = nullptr;
    tamanho = 0;
}

template <class T>
Lista<T>::~Lista() {
    // Libera a memória de todos os nós (reaproveita a remocao do primeiro)
    while (inicio != nullptr) {
        removerPrimeiro();
    }
}

template <class T>
bool Lista<T>::vazio() const {
    return inicio == nullptr;
}

template <class T>
int Lista<T>::size() const {
    return tamanho;
}


// --- Funções de Manipulação Principal ---

// Remove o primeiro nó da lista (o de maior iniciativa) e retorna o dado
template <class T>
T Lista<T>::removerPrimeiro() {
    if (vazio()) {
        // Retorna o valor padrao do tipo T (sinal de erro)
        return T();
    }

    Nodo<T>* noRemovido = inicio;
    T dadoRemovido = noRemovido->dado;

    inicio = inicio->proximo; // 1. Avanca o inicio

    // 2. Se a lista nao ficou vazia, limpa o ponteiro anterior do novo inicio
    if (inicio != nullptr) {
        inicio->anterior = nullptr;
    }
    // 3. Se a lista ficou vazia, atualiza o fim
    else {
        fim = nullptr;
    }

    delete noRemovido;
    tamanho--;
    return dadoRemovido;
}


// O CERNE DA INSERÇÃO POR POSIÇÃO
template <class T>
bool Lista<T>::inserirNaPosicao(const T& item, int posicao) {
    // 1. Checa Erro: Posicao Invalida
    if (posicao < 0 || posicao > tamanho) {
        return false; // Retorna falso para indicar falha
    }

    Nodo<T>* novoNo = new Nodo<T>(item);

    // CASO 1: Lista Vazia OU Inserção na Posição 0 (Início)
    if (posicao == 0) {
        if (vazio()) {
            inicio = novoNo;
            fim = novoNo;
        }
        else {
            novoNo->proximo = inicio;
            inicio->anterior = novoNo;
            inicio = novoNo;
        }
    }

    // CASO 2: Inserção no FIM
    else if (posicao == tamanho) {
        fim->proximo = novoNo;
        novoNo->anterior = fim;
        fim = novoNo;
    }

    // CASO 3: Inserção no MEIO (Requer Travessia e 4 Links)
    else {
        Nodo<T>* atual = inicio;

        // Percorre ate encontrar o no que VEM DEPOIS da posicao desejada (posicao - 1 passos)
        for (int i = 0; i < posicao; i++) {
            atual = atual->proximo;
        }

        // Nodo A (o anterior)
        Nodo<T>* anterior = atual->anterior;

        // 1. Liga o novo nó (Nó B) aos vizinhos
        novoNo->anterior = anterior;
        novoNo->proximo = atual;

        // 2. Liga os vizinhos (Nó A e Nó C) ao novo nó (Nó B)
        anterior->proximo = novoNo;
        atual->anterior = novoNo;
    }
    tamanho++;
    return true; // Retorna sucesso
}


// --- Funções de Visualização ---
template <class T>
void Lista<T>::imprimir() const {
    if (vazio()) {
        std::cout << "Lista Vazia." << std::endl;
        return;
    }

    Nodo<T>* atual = inicio;
    int index = 0;

    std::cout << "\n--- LISTA ---\n";
    while (atual != nullptr) {
        // Output simples do index 
        std::cout << index << " - (Dado) \n";
        atual = atual->proximo;
        index++;
    }
    std::cout << "--------------------------\n";
}

template <class T>
bool Lista<T>::removerNaPosicao(int posicao) {
    // 1. Validação: A posição deve ser maior ou igual a zero E menor que o tamanho.
    if (posicao < 0 || posicao >= tamanho) {
        return false; // Retorna false se a posição for inválida
    }

    // 2. Caso Especial: Remoção do Primeiro Nó (Posicao 0)
    if (posicao == 0) {
        removerPrimeiro();
        return true;
    }

    // 3. Travessia (Busca do Nó a ser removido)
    Nodo<T>* noRemover = inicio;

    // Percorre até o nó que deve ser removido
    for (int i = 0; i < posicao; i++) {
        noRemover = noRemover->proximo;
    }

    // 4. Identificação dos Vizinhos
    Nodo<T>* anterior = noRemover->anterior;
    Nodo<T>* proximo = noRemover->proximo;

    // 5. Religa os Ponteiros (O Splicing)

    // Link 1: O nó anterior aponta para o próximo (Pula o nó removido)
    anterior->proximo = proximo;

    // Link 2: O nó próximo aponta para o anterior (Link bidirecional)
    if (proximo != nullptr) {
        // Se o nó próximo existe, ele se liga ao nó anterior
        proximo->anterior = anterior;
    }
    else {
        // Caso de Borda: Removendo o ÚLTIMO item da lista.
        // O ponteiro 'fim' da Lista precisa ser atualizado para o nó anterior.
        fim = anterior;
    }

    // 6. Limpeza
    delete noRemover;
    tamanho--;
    return true;
}

// NOTA CRÍTICA: O conteúdo deste arquivo DEVE ser incluído no final do Lista.h
// para que o compilador possa gerar as versões template corretamente.