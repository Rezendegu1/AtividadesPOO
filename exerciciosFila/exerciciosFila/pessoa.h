#pragma once
#include <iostream>
using namespace std;

class Pessoa {
public: 
	Pessoa();
	Pessoa(int i, string n, int p);
	int idade;
	string nome;
	int prioridade;

};