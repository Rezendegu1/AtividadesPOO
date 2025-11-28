#include "ReadingProcess.h"
#include "ComputingProcess.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
using namespace std;

ReadingProcess::ReadingProcess(int id, FilaProcessos* fila) : Processo(id, "Reading") {
	filaSistema = fila;
}

void ReadingProcess::execute() {
	ifstream arquivo("computation.txt");

	if (!arquivo.is_open()) {
		cout << "Pid " << pid << ". Leitura: arquivo vazio ou nao existe";
		return;
	}

	string linha; 
	int count = 0; 

	while (getline(arquivo, linha)) {
		if (!linha.empty()) {
			int novoPid = filaSistema->gerarPid();
			ComputingProcess* novoProcesso = new ComputingProcess(novoPid, linha);
			filaSistema->adicionar(novoProcesso);
			count++;
		}
	}
	arquivo.close();
	remove("computation.txt");

	cout << "Pid " << pid << " Leitura: " << count << " processos de calculo criados e colocados na fila." << endl;
}