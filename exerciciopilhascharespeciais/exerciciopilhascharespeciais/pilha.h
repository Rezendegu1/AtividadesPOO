#pragma once
#include <iostream>
using namespace std;

class Pilha {
private:
	char dados[100];
	int topo;

public:
	Pilha();
	void push(char c);
	void pop();
	char top();
	int getValorTopo();
	bool vazio();
};