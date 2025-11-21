#pragma once
#include "combatente.h"

class Nodo {
public:
	Combatente dado;
	Nodo* proximo;
	Nodo* anterior;

	Nodo(Combatente& c);
};