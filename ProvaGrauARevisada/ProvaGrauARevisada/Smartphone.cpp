#pragma once
#include "Smartphone.h"
#include <iostream>

Smartphone::Smartphone(string nome, double preco, int codigoDeBarras, string modelo, int armazenamento, int quantidade){
	this->setNome(nome);
	this->setPreco(preco);
	this->setCodigoDeBarras(codigoDeBarras);
	this->setQuantidade(quantidade);
	this->modelo = modelo;
	this->armazenamento = armazenamento;
}

Smartphone::Smartphone() {
	this->setNome("");
	this->setPreco(0.0);
	this->setCodigoDeBarras(0);
	this->setQuantidade(0);
	this->modelo = "";
	this->armazenamento = 0;
}

Smartphone::~Smartphone() {
}

string Smartphone::getModelo() {
	return this->modelo;
}

void Smartphone::setModelo(string modelo) {
	this->modelo = modelo;
}

int Smartphone::getArmazenamento() {
	return this->armazenamento;
}

void Smartphone::setArmazenamento(int armazenamento) {
	this->armazenamento = armazenamento;
}

void Smartphone::imprimirDados() {
	cout << "Smartphone:" << endl;
	cout << "Nome: " << this->getNome() << endl;
	cout << "Preco: " << this->getPreco() << endl;
	cout << "Codigo de Barras: " << this->getCodigoDeBarras() << endl;
	cout << "Modelo: " << this->getModelo() << endl;
	cout << "Armazenamento: " << this->getArmazenamento() << " GB" << endl;
}
