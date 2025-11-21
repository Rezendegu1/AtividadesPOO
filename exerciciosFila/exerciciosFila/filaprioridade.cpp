#include "filaprioridade.h"

FilaP::FilaP() {
    inicio = nullptr;
    fim = nullptr;
}

bool FilaP::vazio() {
    return inicio == nullptr;
}

FilaP::~FilaP() {
    while (!vazio()) {
        atendido();
    }
}

void FilaP::chegouPrioridade(Pessoa& p) {
    Nodo* novaCaixinha = new Nodo(p);

    if (vazio()) {
        inicio = novaCaixinha;
        fim = novaCaixinha;
        return;
    }
    if (novaCaixinha->representante.prioridade > inicio->representante.prioridade) {
        novaCaixinha->proximo = inicio;
        inicio = novaCaixinha;
        return;
    }

    Nodo* atual = inicio;
    Nodo* anterior = nullptr;

    while (atual != nullptr && atual->representante.prioridade >= novaCaixinha->representante.prioridade) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (anterior == nullptr) {
        // A nova caixinha é o novo início.
        novaCaixinha->proximo = inicio;
        inicio = novaCaixinha;
    }

    // 2. CASO INSERÇÃO NO MEIO OU FIM (anterior é válido):
    else {
        // Esta logica é executada SOMENTE QUANDO 'anterior' NÃO é nullptr.

        // a) Insere no FIM: Se o loop terminou porque 'atual' é nulo (chegou ao fim da fila).
        if (atual == nullptr) {
            anterior->proximo = novaCaixinha; // Liga o penúltimo ao novo último
            fim = novaCaixinha;               // Atualiza o marcador 'fim'
        }
        // b) Insere no MEIO: O loop parou porque 'atual' tem prioridade menor.
        else {
            anterior->proximo = novaCaixinha;  // Linka o anterior ao novo
            novaCaixinha->proximo = atual;     // Linka o novo ao próximo
        }
    }
}

void FilaP::atendido() {

    if (inicio == nullptr) {
        return;
    }

    Nodo* guardar = inicio;
    inicio = inicio->proximo;

    if (inicio == nullptr) {
        fim = nullptr;
    }

    delete guardar;
    guardar = nullptr;

}

Pessoa FilaP::front() {
    if (inicio == nullptr) {
        return Pessoa();
    }

    cout << endl << "primeiro da fila: " << inicio->representante.nome << " e idade " << inicio->representante.idade << endl;
    return inicio->representante;
}

void FilaP::imprimirFilaP() {
    Nodo* nodoatual = inicio;
    int posicao = 1;
    while (nodoatual != nullptr) {
        cout << posicao << ". " << nodoatual->representante.nome << " e idade " << nodoatual->representante.idade << endl;
        nodoatual = nodoatual->proximo;
        posicao++;
    }
}