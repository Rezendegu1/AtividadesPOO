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

	cout << "--- POOL DE PROCESSOS (Printing Process) ---" << endl;
	int tamanho = filaSistema->getTamanho();

	for (int i = 0; i < tamanho; i++)  {
		Processo* p = filaSistema->removerInicio();

		if (p != nullptr) {
			cout << "PID: " << p->getPid() << " | Tipo: " << p->getTipo() << endl;

			string detalhes = p->getDetalhes();

			if (!detalhes.empty()) {
				cout << " | Detalhes: " << detalhes;
			}

			cout << endl; 
			filaSistema->adicionar(p);
		}
	}
	cout << "-----------------------------------------------" << endl;
}