#include "PrintingProcess.h"
#include "FilaProcessos.h"
#include <iostream>
using namespace std;

PrintingProcess::PrintingProcess(int id, FilaProcessos* fila) : Processo(id, "Printing") {
	filaSistema = fila;
}

void PrintingProcess::execute() {
	filaSistema->imprimirFila();
}