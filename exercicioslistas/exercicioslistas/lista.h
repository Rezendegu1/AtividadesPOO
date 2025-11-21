#pragma once
#include <iostream>
#include "nodo.h"
using namespace std;

class Lista {
public: 
	Nodo* inicio;
	Nodo* fim;
	Lista();
	~Lista();

	bool vazio();
	void inserir(Combatente& c);
	void imprimir(); 
	Combatente removerPrimeiro();
	bool remover(string nomeBusca);
};