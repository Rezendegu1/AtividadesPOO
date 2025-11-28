#include "Processo.h"

Processo::Processo(int id, string t) {
	pid = id;
	tipo = t;
}

Processo::~Processo() {
}

int Processo::getPid() const {
	return pid;
}

string Processo::getTipo() const {
	return tipo;
}

string Processo::toString() const {
	return to_string(pid) + ";" + tipo;
}