#include "fila.h"

Fila::Fila() {
	inicio = nullptr;
	fim = nullptr;
}

bool Fila::vazio() {
    return inicio == nullptr;
}

Fila::~Fila() {
	while (!vazio()) {
		atendido();
	}
}

void Fila::chegou(Pessoa& p) {
    Nodo* novaCaixinha = new Nodo(p); 

    if (vazio()) {
        inicio = novaCaixinha;
        fim = novaCaixinha;
    }
    else {
        fim->proximo = novaCaixinha;
        fim = novaCaixinha;
    }
}

void Fila::atendido() {

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

Pessoa Fila::front() { 
    if (inicio == nullptr) {
        return Pessoa();
    }
    return inicio->representante;
}

void Fila::imprimirFila() {
    Nodo* atual = inicio;
    int posicao = 1;
    while (atual != nullptr){
        cout << posicao << ". " << atual->representante.nome << " e idade " << atual->representante.idade << endl;
        atual = atual->proximo;
        posicao++;
}
}