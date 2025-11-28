#pragma once
#include "Processo.h"

struct Nodo { //struct pra deixar tudo publico direto, facilita
	Processo* processo; //nodo dentro dessa classe pela simplicidade, já que o nó é um detalhe interno da fila, não é algo que ela faz
	Nodo* proximo;
};

class FilaProcessos {
private:
	Nodo* inicio;
	Nodo* fim;
	int proximoPid; //contador pra gerar pids unicos

public:
	FilaProcessos();
	~FilaProcessos();

	int gerarPid(); //gera um pid automaticamente
	void adicionar(Processo* p); //enfileirar
	void executarProximo(); //desenfileirar
	bool vazia();
};