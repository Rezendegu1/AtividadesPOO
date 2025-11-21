#pragma once
#include <iostream>
#include "pessoa.h"
using namespace std;

class Nodo {
public:
	Nodo(Pessoa& p);
	Pessoa representante;
	Nodo* proximo;
};