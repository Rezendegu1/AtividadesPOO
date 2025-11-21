#include "Laptop.h"
#include <iostream>

Laptop::Laptop(string nome, double preco, int codigoDeBarras, string marca, double tamanhoTela, int quantidade) {
	this->setNome(nome);
	this->setPreco(preco);
	this->setCodigoDeBarras(codigoDeBarras);
	this->setQuantidade(quantidade);
	this->marca = marca;
	this->tamanhoTela = tamanhoTela;
}
Laptop::Laptop() {
	this->setNome("");
	this->setPreco(0.0);
	this->setCodigoDeBarras(0);
	this->setQuantidade(0);
	this->marca = "";
	this->tamanhoTela = 0.0;
}
Laptop::~Laptop() {
}

string Laptop::getMarca() {
	return this->marca;
}

void Laptop::setMarca(string marca) {
	this->marca = marca;
}

double Laptop::getTamanhoTela() {
	return this->tamanhoTela;
}

void Laptop::setTamanhoTela(double tamanhoTela) {
	this->tamanhoTela = tamanhoTela;
}

void Laptop::imprimirDados() {
	cout << "Laptop:" << endl;
	cout << "Nome: " << this->getNome() << endl;
	cout << "Preco: " << this->getPreco() << endl;
	cout << "Codigo de Barras: " << this->getCodigoDeBarras() << endl;
	cout << "Marca: " << this->getMarca() << endl;
	cout << "Tamanho da Tela: " << this->getTamanhoTela() << " polegadas" << endl;
}