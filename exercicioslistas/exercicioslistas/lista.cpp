#include "lista.h"

Lista::Lista() {
	inicio = nullptr;
	fim = nullptr;
}

Lista::~Lista() {
	while (!vazio()) {
		removerPrimeiro();
	}
}

bool Lista::vazio() {
	if (inicio == nullptr) {
		return true;
	}
}

void Lista::inserir(Combatente& c) {
	Nodo* novoNodo = new Nodo(c); //cria uma caixa temporária que guarda as informações da caixa que guarda as informações do item

		if (vazio()) {
			inicio = novoNodo;
			fim = novoNodo;
	}

		Nodo* atual = inicio;
		while (atual != nullptr && c.iniciativa <= atual->dado.iniciativa) {
			atual = atual->proximo;
			}

		if (atual == inicio) {
			novoNodo->proximo = inicio;
			inicio->anterior = novoNodo;
			inicio = novoNodo;
			return;
		}

		else if (atual == nullptr) {
			fim->proximo = novoNodo;
			novoNodo->anterior = fim;
			fim = novoNodo;
			return;
		}

		else {
			Nodo* anterior = atual->anterior;

			novoNodo->anterior = anterior;
			novoNodo->proximo = atual;

			anterior->proximo = novoNodo;
			atual->anterior = novoNodo;
		}
}

Combatente Lista::removerPrimeiro() {
if (vazio()) {
    throw std::runtime_error("Erro: Lista vazia.");
}

Nodo* noRemovido = inicio;
Combatente dadoRemovido = noRemovido->dado;

// 1. Avanca o inicio para o proximo
inicio = inicio->proximo;

// 2. Se a lista nao ficou vazia, limpa o ponteiro anterior do novo inicio
if (inicio != nullptr) {
    inicio->anterior = nullptr;
}
// 3. Se a lista ficou vazia, atualiza o fim
else {
    fim = nullptr;
}

// 4. Limpa a memória
delete noRemovido;
return dadoRemovido;
}


// --- Funções de Visualização ---
void Lista::imprimir() {
    if (vazio()) {
        cout << "Lista de Combate Vazia." << endl;
        return;
    }

    Nodo* atual = inicio;
    int rank = 1;

    cout << "\n--- ORDEM DE INICIATIVA ---\n";
    while (atual != nullptr) {
        cout << rank << ". "
            << atual->dado.nome
            << " (Iniciativa: " << atual->dado.iniciativa << ")\n";

        atual = atual->proximo;
        rank++;
    }
    cout << "--------------------------\n";
}