#pragma once
#include <string>
#include <vector>
#include "Item.h"
using namespace std;

class Personagem {
public:

	Personagem();
	Personagem(string nome, int habilidade, int energia, int sorte);
	~Personagem();

	string getNome();
	void tomarDano(int dano);
	void curar(int cura);
	int getHabilidade();
	int getEnergia();
	bool usarSorte(); //tenta usar a sorte, retornando true se conseguir
	int getSorte();
	bool estaVivo(); //retorna true se energia > 0
	int getTesouro();
	int getProvisoes();
	int getBonusForcaAtaque();
	int getBonusDano();
	void equiparArma(int indiceDoInventario);
	vector<Item> getInventario();

	//Métodos para funcionamento do inventário
	void adicionarItem(Item& item);
	void usarProvisao(); //recupera 4 pontos de vida
	void adicionarTesouro(int valor);
	void mostrarInventario();

private:

	string nome;
	int habilidade;
	int energia;
	int sorte;
	int tesouro; //valor númerico, como moedas de ouro 
	int provisoes; //número de provisões
	Item* armaEquipada; //ponteiro para o item do tipo arma que pode estar equipado 
	vector<Item> inventario; //itens do personagem, o vetor armazena itens do tipo Item e aloca dinamincamente

};