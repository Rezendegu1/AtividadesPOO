#include "PrintingProcess.h"
#include "FilaProcessos.h"
#include <iostream>
using namespace std;

PrintingProcess::PrintingProcess(int id, FilaProcessos* fila) : Processo(id, "Printing") {
	filaSistema = fila;
}

void PrintingProcess::execute() {
	if (filaSistema->vazia()) {
		cout << "PID " << pid << " (Printing): Pool de processos vazio." << endl;
		return;
	}

	cout << "--- POOL DE PROCESSOS (Via Printing Process) ---" << endl;

	// Precisamos saber o tamanho para girar a quantidade certa
	int tamanho = filaSistema->getTamanho();

	for (int i = 0; i < tamanho; i++) {
		// 1. Tira do início
		Processo* p = filaSistema->removerInicio();

		if (p != nullptr) {
			// 2. Imprime
			cout << "PID: " << p->getPid() << " | Tipo: " << p->getTipo() << endl;

			// 3. Devolve para o final
			filaSistema->adicionar(p);
		}
	}
	cout << "-----------------------------------------------" << endl;
}