#pragma once
#include <iostream>
using namespace std;

class Carta {
public:
	int valor;
	string naipe;

	Carta(int v, string n);
	string getNomeCompleto();
};