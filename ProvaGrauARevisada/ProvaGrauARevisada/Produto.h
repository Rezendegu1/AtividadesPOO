#pragma once
#include <string>

using namespace std;

class Produto {

private:

	string nome;
	double preco;
	int codigoDeBarras;
	int quantidade;

public:

	Produto(string nome, double preco, int codigoDeBarras, int quantidade);
	Produto(); 
	virtual ~Produto();
	string getNome();
	void setNome(string nome);
	double getPreco();
	void setPreco(double preco);
	int getCodigoDeBarras() const;
	void setCodigoDeBarras(int codigoDeBarras);
	bool verificaCodigoDeBarras(const Produto& a, const Produto& b);
	virtual void imprimirDados() = 0;
	int getQuantidade();
	void setQuantidade(int quantidade);
};
