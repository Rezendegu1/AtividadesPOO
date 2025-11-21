#include <iostream>
#include "cu.h"

using namespace std;
 //Construtor

Pessoa::Pessoa() {
	nome = "";
	idade = 0;
	cidade = "";
	estado = "";
}

void Pessoa::ImprimeInfo() {
	cout << "Nome: " << nome << endl;
	cout << "Idade: " << idade << endl;
	cout << "Cidade: " << cidade << endl;
	cout << "Estado: " << estado << endl;
}
//Setters
void Pessoa::setNome(string n) {
	nome = n;
}
void Pessoa::setIdade(int i) {
	cin >> i; 
}
void Pessoa::setCidade(string c) {
	cin >> c; 
}
void Pessoa::setEstado(string e) {
	cin >> e; 
}
//Getters


