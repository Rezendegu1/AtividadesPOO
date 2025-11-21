#include "Tablet.h"
#include <iostream>
using namespace std;

Tablet::Tablet(string nome, double preco, int codigoDeBarras, string marca, double duracaoBateria, int quantidade) {
	this->setNome(nome);
	this->setPreco(preco);
	this->setCodigoDeBarras(codigoDeBarras);
	this->setQuantidade(quantidade);
	this->marca = marca;
	this->duracaoBateria = duracaoBateria;
}

Tablet::Tablet() {
	this->setNome("");
	this->setPreco(0.0);
	this->setCodigoDeBarras(0);
	this->setQuantidade(0);
	this->marca = "";
	this->duracaoBateria = 0.0;
}
Tablet::~Tablet() {
}
string Tablet::getMarca() {
	return this->marca;
}
void Tablet::setMarca(string marca) {
	this->marca = marca;
}
int Tablet::getDuracaoBateria() {
	return this->duracaoBateria;
}
void Tablet::setDuracaoBateria(int horas) {
	this->duracaoBateria = horas;
}

void Tablet::imprimirDados() {
	cout << "Tablet:" << endl;
	cout << "Nome: " << this->getNome() << endl;
	cout << "Preco: " << this->getPreco() << endl;
	cout << "Codigo de Barras: " << this->getCodigoDeBarras() << endl;
	cout << "Marca: " << this->getMarca() << endl;
	cout << "Duracao da Bateria: " << this->getDuracaoBateria() << " horas" << endl;
}


