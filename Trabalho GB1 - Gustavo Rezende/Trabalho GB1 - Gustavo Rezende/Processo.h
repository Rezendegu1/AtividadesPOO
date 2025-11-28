#pragma once
#include <iostream>
#include <string>

using namespace std;

class Processo {
protected:
	int pid;
	string tipo;

public:
	Processo(int id, string t);

	virtual ~Processo();

	int getPid() const;
	string getTipo() const;

	virtual void execute() = 0; //=0 obriga as classes filhas a implementarem
	virtual string toString() const; //pra converter os dados em texto, ajuda na hora de salvar ou imprimir
};

