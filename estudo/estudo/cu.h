#include <iostream>
using namespace std; 

class Pessoa {

public: 
	Pessoa() {
	} 
	~Pessoa() {
	}
private: 
	string nome;
	int idade; 
	string cidade;
	string estado; 

public:
	//Setters
	void setNome(string n);
	void setIdade(int i);
	void setCidade(string c);
	void setEstado(string e);
	void ImprimeInfo();
	//Getters
	string getNome();
	int getIdade();
	string getCidade();
	string getEstado();
};