#pragma once
#include "FilaProcessos.h"
using namespace std;

class Sistema {
private: 
	FilaProcessos fila; // FAZER COM PONTEIRO DE FILA

public: 
	Sistema();

	void iniciar();
	void mostrarMenu();
	void criarProcesso();
	void executarProximo();
	void executarEspecifico();
	void salvarFila();
	void carregarFila();

	void executarPorPid(int pidBusca);
	void imprimirFila();
	void salvarArquivo();
	void carregarArquivo();
};
