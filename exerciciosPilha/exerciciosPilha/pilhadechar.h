#pragma once
#include <iostream>
using namespace std;

class PilhaDeChar {
private:
	char dados[100];
	int topo;

public:
	PilhaDeChar();
	void push(char c);
	void pop();
	char top();
	int getValorTopo();
};