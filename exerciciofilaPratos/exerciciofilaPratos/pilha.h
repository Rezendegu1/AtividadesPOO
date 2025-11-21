#pragma once
#pragma once
#include <iostream>
using namespace std;

class Pilha {
private:
	int dados[100];
	int topo;

public:
	Pilha();
	void push(int prato);
	void pop();
	int top();
	int size();
	bool vazio();
	int getValorTopo();
};