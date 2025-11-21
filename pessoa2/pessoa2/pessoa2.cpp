#include <iostream>
#include <string>
#include "pessoa.h"
using namespace std;

Pessoa::Pessoa() {
	string nome;
	int idade;
	string endereco;
	int irmaos;
}

//Setters

void Pessoa::setNome(string n) {
	n = nome;
}

void Pessoa::setEndereco(string e) {
	e = endereco; 
}

void Pessoa::setIdade(int i) {
	i = idade;
}

void Pessoa::setIrmaos(int ir) {
	ir = irmao;
}

//Getters

string Pessoa::getEndereco() {
	return endereco;
}
string Pessoa::getNome() {
	return nome;
}
int Pessoa::getIdade() {
	return idade;
}
int Pessoa::getIrmaos() {
	return irmao;
}

void Pessoa::imprimir() {
	cout << "Nome: " << nome << endl;
	cout << "Idade: " << idade << endl;
	cout << "Endereço: " << endereco << endl;
	cout << "Número de irmãos: " << irmao << endl; 
}

