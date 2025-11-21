#include "nodo.h"

Nodo::Nodo(Pessoa& p) {
	representante = p;
	proximo = nullptr;
}