#include "Monstro.h"
#include "Item.h"

Monstro::Monstro(string nome, int habilidade, int energia) :
	nome(nome),
	habilidade(habilidade),
	energia(energia),
	tesouroDrop(0),
	provisoesDrop(0),
	itemDrop(nullptr) //inicia como nulo, para indicar que não há drop
{

}

//getters
string Monstro::getNome() {
	return this->nome;
}
int Monstro::getTesouro() {
	return this->tesouroDrop;
}
int Monstro::getHabilidade() {
	return this->habilidade;
}
Item* Monstro::getItemDrop() {
	return this->itemDrop;
}
int Monstro::getEnergia() {
	return this->energia;
}
bool Monstro::isFugaPermitida() {
	return this->fugaPermitida;
}
bool Monstro::estaVivo() {
	return this->energia > 0;
}
int Monstro::getSorte() {
	return this->sorte;
}
int Monstro::getProvisoes() {
	return this->provisoesDrop;
}

//setters
void Monstro::setTesouro(int valor) {
	this->tesouroDrop = valor;
}
void Monstro::setNome(string nome) {
	this->nome = nome;
}
void Monstro::setHabilidade(int valor) {
	this->habilidade = valor;
}
void Monstro::setEnergia(int valor) {
	this->energia = valor;
}

void Monstro::setItemDrop(Item &item) {
	delete this->itemDrop; //apaga a memória do item antigo, se houver. Evita memory leak
	this->itemDrop = new Item(item); //cria uma cópia nova e permanente do item na memória dinamica
}

void Monstro::setFugaPermitida(bool permitida) {
	this->fugaPermitida = permitida;
}

void Monstro::tomarDano(int dano) {
	this->energia -= dano;
	if (this->energia < 0) {
		this->energia = 0; //evita energia negativa
		}
}

void Monstro::setSorte(int valor) {
	this->sorte = valor;
}

void Monstro::setProvisoes(int quantidade) {
	this->provisoesDrop = quantidade;
}