#include "combatente.h"

Combatente::Combatente(string n){
	nome = n;
	iniciativa = (rand() % 10) + 1;
}



