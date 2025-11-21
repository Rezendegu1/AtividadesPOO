#pragma once
#include "Produto.h"
#include <string>
using namespace std;

class Laptop : public Produto {
private:
	string marca;
	double tamanhoTela;
public:
	Laptop(string nome, double preco, int codigoDeBarras, string marca, double tamanhoTela, int quantidade);
	Laptop();
	virtual ~Laptop();

	string getMarca();
	void setMarca(string marca);
	double getTamanhoTela();
	void setTamanhoTela(double tamanhoTela);

	virtual void imprimirDados() override;
};
