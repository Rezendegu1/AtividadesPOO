#include "pilha.h"

Pilha::Pilha() {
	topo = -1;
}

void Pilha::push(int prato) {
	if (topo < 99) {
		topo++;
		dados[topo] = prato;
	}
}

void Pilha::pop() {
	if (topo >= 0) {
		int prato = dados[topo];
		topo--;
	}
}

int Pilha::top() {
	if (topo >= 0) {
		return dados[topo];
	}
	return '\0';
}

int Pilha::getValorTopo() {
	return this->topo;
}

int Pilha::size() {
	return topo + 1;
}

bool Pilha::vazio() {
	return topo == -1;
}
