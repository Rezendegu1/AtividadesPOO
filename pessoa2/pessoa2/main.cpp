#include <iostream>
#include <string>
#include "pessoa.h"
using namespace std;

int main() {

	system("cls");
	
	string n, e;
	int i, ir;
	Pessoa p;

	cout << "Digite o nome: ";
	getline(cin, n); 
	p.setNome(n);
	p.getNome();
	
	cout << "Digite o endereco: ";
	getline(cin, e); 
	p.setEndereco(e);
	p.getEndereco();

	cout << "Digite a idade: ";
	cin >> i; 
	p.setIdade(i);
	p.getIdade();

	cout << "Digite a quantidade de irmãos: ";
	cin >> ir; 
	p.setIdade(ir);
	p.getIdade();


}