#pragma once
#include "Produto.h"
using namespace std;

class Smartphone : public Produto {
private:
	string modelo;
	int armazenamento;
public:
	Smartphone(string nome, double preco, int codigoDeBarras, string modelo, int armazenamento, int quantidade);
	Smartphone();
	virtual ~Smartphone();

	string getModelo();
	void setModelo(string modelo);
	int getArmazenamento();
	void setArmazenamento(int armazenamento);
	virtual void imprimirDados() override;
};


