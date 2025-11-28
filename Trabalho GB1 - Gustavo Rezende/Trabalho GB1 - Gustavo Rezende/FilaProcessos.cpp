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
	while (inicio != nullptr) {
		removerInicio();
	}
}
int FilaProcessos::gerarPid() {
	return proximoPid++;
}

int FilaProcessos::getProximoPid() const {
	return proximoPid;
}

void FilaProcessos::setProximoPid(int pid) {
	proximoPid = pid;
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

int FilaProcessos::getTamanho() {
	int contador = 0;
	Nodo* temporario = inicio;
	while (temporario != nullptr) {
		contador++;
		temporario = temporario->proximo;
	}
	return contador;
}

Processo* FilaProcessos::removerInicio() { //RETORNAR o temporario pro sistema poder executar;
	if (inicio == nullptr) return nullptr;

	Nodo* temp = inicio;
	Processo* p = temp->processo; // Salva o processo para devolver

	inicio = inicio->proximo;
	if (inicio == nullptr) {
		fim = nullptr;
	}

	delete temp; // Deleta o nodo, mas o processo continua, para que o sistema o delete
	return p;
}

bool FilaProcessos::vazia() {
	return inicio == nullptr;
}
