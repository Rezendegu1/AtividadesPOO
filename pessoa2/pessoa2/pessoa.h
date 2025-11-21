#include <iostream>
#include <string>
using namespace std;

class Pessoa {
private:
	string nome = "";
	int idade = 0;
	string endereco = "";
	int irmao = 0;
public:
	Pessoa();
	~Pessoa() {

	}

	//Setters

	void setNome(string nome);
	void setIdade(int idade);
	void setEndereco(string endereço);
	void setIrmaos(int irmaos);

	//Getters

	string getNome();
	int getIdade();
	string getEndereco();
	int getIrmaos();

	void imprimir();
};