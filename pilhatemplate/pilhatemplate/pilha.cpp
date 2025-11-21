#include "Pilha.h"
#include <iostream> 
// Note: std::string, std::cout, etc., viriam daqui, mas não são usados diretamente aqui.

using namespace std; // <-- Adicionado o uso do namespace padrão

// --- Construtor ---
template <class T>
Pilha<T>::Pilha() {
    topo = -1;
}

// --- Retorna o Tamanho ---
template <class T>
int Pilha<T>::size() {
    return topo + 1;
}

// --- Verifica se está vazia ---
template <class T>
bool Pilha<T>::isEmpty() {
    return topo == -1;
}

// --- Inserir (Push) ---
template <class T>
void Pilha<T>::push(T item) {
    if (topo >= 99) {
        // A pilha ignora o push se estiver cheia (sem exceções).
        return;
    }
    topo++;
    dados[topo] = item;
}

// --- Remover (Pop) ---
template <class T>
void Pilha<T>::pop() {
    if (topo >= 0) {
        topo--;
    }
}

// --- Ver o topo (Top) ---
template <class T>
T Pilha<T>::top() {
    if (topo >= 0) {
        return dados[topo];
    }
    // Retorna o valor padrao do tipo T em caso de pilha vazia.
    // O usuário DEVE checar isEmpty() antes de chamar top().
    return T();
}