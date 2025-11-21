#pragma once
#pragma once

template <class T>
class Pilha {
private:
    // O array agora guarda itens de TIPO GENÉRICO T
    T dados[100];
    int topo;

public:
    Pilha();

    // Funções de manipulação que usam T
    void push(T item); // Recebe um item de tipo T
    void pop();
    T top();          // Retorna um item de tipo T
    bool isEmpty();
    int size();
};