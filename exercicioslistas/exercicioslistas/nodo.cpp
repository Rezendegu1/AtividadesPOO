#include "nodo.h"

Nodo::Nodo(Combatente& c) {
	dado = c;
	proximo = nullptr;
	anterior = nullptr;
}