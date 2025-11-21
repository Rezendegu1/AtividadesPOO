#pragma once
#include <string>
#include <vector>
#include "Item.h"
#include "Monstro.h"
using namespace std;

class Cena {
public:
	Cena() :
		textoPrincipal(""),
		item(nullptr),
		inimigo(nullptr),
		cenaVitoria(0),
		cenaDerrota(0)
	{
	}

	~Cena() {
		delete item;
		delete inimigo;
	}
	
	bool carregar(int numeroCena); //para carregar a cena a partir de um arquivo

	//Métodos para obter as informações da cena
	string getTexto(); 
	bool isCenaDeCombate();
	Monstro* getInimigo(); 
	int getCenaVitoria(); //retornam o número da próxima cena em caso de vitória ou derrota
	int getCenaDerrota();
	Item* getItem(); //retorna o item encontrado na cena se tiver

	//Escolhas
	const vector<string>& getTextoEscolhas();
	const vector<int>& getCenasDestino(); 

private: 

	string textoPrincipal;
	Item* item; //os ponteiros nesse caso servem para entender o que há ou não na cena
	Monstro* inimigo; //exemplo: se o ponteiro for nulo, não há um inimigo na cena e ela é de exploração

	vector<string> textoEscolhas;
	vector<int> cenasDestino; //números das cenas destino para cada escolha

	int cenaVitoria; //número da cena para onde ir em caso de vitória no combate
	int cenaDerrota;

};