#include "Item.h"

Item::Item(string nome, char tipo, bool combate, int fa, int dano) :
	nome(nome),
	tipo(tipo),
	podeUsarEmCombate(combate),
	bonusForcaAtaque(fa),
	bonusDano(dano)
{

}



string Item::getNome() {
	return this->nome;
}
char Item::getTipo() {
	return this->tipo;
}
int Item::getBonusForcaAtaque() {
	return this->bonusForcaAtaque;
}
int Item::getBonusDano() {
	return this->bonusDano;
}
bool Item::isUsavelEmCombate() {
	return this->podeUsarEmCombate;
}
