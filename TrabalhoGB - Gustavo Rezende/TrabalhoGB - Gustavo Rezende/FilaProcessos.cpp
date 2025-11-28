#include "FilaProcessos.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

FilaProcessos::FilaProcessos() {
	inicio = nullptr;
	fim = nullptr;
	proximoPid = 1; //pids começam em 1 por padrao
}

FilaProcessos::~FilaProcessos() { //pra deletar a fila
	Nodo* atual = inicio;
	while (atual != nullptr) {
		Nodo* proximo = atual->proximo;
		delete atual->processo; //deleta o objeto processo
		delete atual;
		atual = proximo;
	}
}
int FilaProcessos::gerarPid() {
	return proximoPid++;
}

void FilaProcessos::adicionar(Processo* p) { // talvez mudar pra PUSH
	Nodo* novo = new Nodo;
	novo->processo = p;
	novo->proximo = nullptr;

	if (inicio == nullptr) { //se a fila tiver vazia, inicio e fim apontam pro novo processo
		inicio = novo;
		fim = novo;
	}
	else { //se não, o proximo do item que o fim aponta vai apontar pro novo
		fim->proximo = novo;
		fim = novo; //e o novo se torna o fim
	}
}

void FilaProcessos::executarProximo() { //RETORNAR o temporario pro sistema poder executar;
	if (inicio == nullptr) {
		cout << "Fila vazia. Nao ha nenhum processo para executar" << endl;
	}

	Nodo* temporario = inicio;
	cout << "Executando proximo (Pid " << temporario->processo->getPid() << "):" << endl;

	temporario->processo->execute();// fila não deve saber como executar um processo. isso é responsabilidade do sistema

	inicio = inicio->proximo;
	if (inicio == nullptr) {
		fim = nullptr;
	}

	delete temporario->processo;
	delete temporario;
}

bool FilaProcessos::vazia() {
	return inicio == nullptr;
}
