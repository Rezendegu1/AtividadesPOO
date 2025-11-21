#include "Pilha.h"

Pilha::Pilha() {
	topo = -1;
}

void Pilha::push(char c) {
	if (topo < 99) {
		topo++;
		dados[topo] = c;
	}
}

void Pilha::pop() {
	if (topo >= 0) {
		topo--;
	}
}

char Pilha::top() {
	if (topo >= 0) {
		return dados[topo];
	}
	return '\0';
}

int Pilha::getValorTopo() {
	return this->topo;
}

bool Pilha::vazio() {
	return topo == -1;
}
