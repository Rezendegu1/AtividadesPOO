#include "pilhadechar.h"

PilhaDeChar::PilhaDeChar() {
	topo = -1;
}

void PilhaDeChar::push(char c) {
	if (topo < 99) {
		topo++;
		dados[topo] = c;
	}
}

void PilhaDeChar::pop() {
	if (topo >= 0) {
		char c = dados[topo];
		topo--;
	}
}

char PilhaDeChar::top() {
	if (topo >= 0) {
		return dados[topo];
	}
	return '\0';
}

int PilhaDeChar::getValorTopo() {
	return this->topo;
}
