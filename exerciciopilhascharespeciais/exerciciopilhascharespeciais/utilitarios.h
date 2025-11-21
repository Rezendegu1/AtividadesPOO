#pragma once
#include "Pilha.h"

class Utilitarios {
public: 
	Utilitarios();
	bool corresponde(char aberto, char fechado);
	bool verificaBalanco(const string& expressao);
};