#pragma once
#include "Tablet.h"
#include "Smartphone.h"
#include "Produto.h"
#include "Laptop.h"
#include <iostream>
using namespace std;

const int MAX_ESTOQUE = 100;

class Loja {
private: 
	string nome;

	Produto* estoque[MAX_ESTOQUE];
	int numProdutos; 
	int buscarIndicePeloCodigo(int codigoDeBarras) const;

public: 

	Loja(string nome);
	virtual ~Loja();
	void buscarProduto(int codigoDeBarras);
	void listarInformacoes() const;
	void adicionarProduto(Produto* novoProduto);
	void editarProduto(int codigoDeBarras);
	void removerProduto(int codigoDeBarras);
	double getValorTotalEstoque() const;
	void aplicarDesconto(int codigoDeBarras, double percentual);
	void realizarVenda(int codigoDeBarras);
	void listarProdutosAcimaDe(double valor) const; 
	void verificarEstoque(int codigoDeBarras) const; 
	string getNome();
	int getQuantidadeTotalItens() const;
};