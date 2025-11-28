#include "carta.h"
#include <iostream>
#include <string>

Carta::Carta(int v, string n) {
	valor = v;
	naipe = n;
}

string Carta::getNomeCompleto() {
	string nomeValor;

	if (valor >= 2 && valor <= 10) {
		nomeValor = to_string(valor);
	}
	else if (valor == 1) {
		nomeValor = "Ás";
	}
	else if (valor == 11) {
		nomeValor = "Valete";
	}
	else if (valor == 12) {
		nomeValor = "Rainha";
	}
	else if (valor == 13) {
		nomeValor = "Rei";
	}
	else {
		nomeValor = "Valor Invalido";
	}
	return nomeValor + " de " + naipe;

}