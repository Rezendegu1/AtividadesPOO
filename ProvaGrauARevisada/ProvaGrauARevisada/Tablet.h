#pragma once
#include "Produto.h"
#include <iostream>
using namespace std;

class Tablet : public Produto {
private:
	string marca;
	double duracaoBateria;
public:

	Tablet(string nome, double preco, int codigoDeBarras, string marca, double duracaoBateria, int quantidade);
	Tablet();
	virtual ~Tablet();

	string getMarca();
	void setMarca(string marca);
	int getDuracaoBateria();
	void setDuracaoBateria(int horas);

	virtual void imprimirDados() override;
};

