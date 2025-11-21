#pragma once
#include "pessoa.h"
#include "nodo.h"

class FilaP {
public:
	FilaP();
	~FilaP();
	void chegouPrioridade(Pessoa& p);
	void atendido();
	Pessoa front();
	bool vazio();
	void imprimirFilaP();
private:
	Nodo* inicio;
	Nodo* fim;
};