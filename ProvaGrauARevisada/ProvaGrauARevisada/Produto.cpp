#include "Produto.h"
using namespace std;

Produto::Produto(string nome, double preco, int codigoDeBarras, int quantidade) {
	this->nome = nome;
	this->preco = preco;
	this->codigoDeBarras = codigoDeBarras;
	this->quantidade = quantidade;
}

Produto::Produto() {
	this->nome = "";
	this->preco = 0.0;
	this->codigoDeBarras = 0;
	this->quantidade = 0;
}

Produto::~Produto() {
}

string Produto::getNome() {
	return this->nome;
}

void Produto::setNome(string nome) {
	this->nome = nome;
}

double Produto::getPreco() {
	return this->preco;
}

void Produto::setPreco(double preco) {
	this->preco = preco;
}

int Produto::getCodigoDeBarras() const {
	return this->codigoDeBarras;
}

void Produto::setCodigoDeBarras(int codigoDeBarras) {
	this->codigoDeBarras = codigoDeBarras;
}

bool Produto::verificaCodigoDeBarras(const Produto& a, const Produto& b) {
	return a.getCodigoDeBarras() == b.getCodigoDeBarras();
}

int Produto::getQuantidade() {
	return this->quantidade;
}

void Produto::setQuantidade(int quantidade) {
	this->quantidade = quantidade;
}



