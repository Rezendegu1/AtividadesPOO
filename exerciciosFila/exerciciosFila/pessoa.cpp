#include "pessoa.h"

Pessoa::Pessoa(int i, string n, int p) {
	nome = n;
	idade = i;
	prioridade = p;
}

Pessoa::Pessoa() {
	nome = "";
	idade = 0;
	prioridade = 99;
}