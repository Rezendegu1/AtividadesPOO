#pragma once
#include <iostream>
#include "nodo.h"
using namespace std;

class Fila {
public:
	Fila();
	~Fila();
	void chegou(Pessoa& p);
	void atendido();
	Pessoa front();
	bool vazio();
	void imprimirFila();
private: 
	Nodo* inicio;
	Nodo* fim;
};