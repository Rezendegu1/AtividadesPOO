#pragma once
#include <string>
using namespace std; 

class Item {
public: 
	Item() :
		nome(""),
		tipo('c'),
		podeUsarEmCombate(false),
		bonusForcaAtaque(0),
		bonusDano(0)
	{

	}
	Item(string nome, char tipo, bool combate, int fa, int dano);
	~Item() {
	}

	bool isUsavelEmCombate();
	string getNome();
	char getTipo();
	int getBonusForcaAtaque();
	int getBonusDano(); 

private: 
	string nome;
	char tipo; //'c' (comum), 'r' (armadura), 'w' (arma), 'm' (magia), caso tenha itens assim
	bool podeUsarEmCombate; 
	int bonusForcaAtaque;
	int bonusDano;

};