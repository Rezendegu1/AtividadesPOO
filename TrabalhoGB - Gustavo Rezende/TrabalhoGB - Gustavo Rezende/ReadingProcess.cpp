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
		cout << "PID " << pid << " (Reading): Arquivo computation.txt vazio ou inexistente." << endl;
		return;
	}

	string linha;
	int count = 0;

	//le linha por linha do arquivo
	while (getline(arquivo, linha)) {
		if (!linha.empty()) {
			//gera um PID novo usando a fila
			int novoPid = filaSistema->gerarPid();

			//cria um Processo de Cálculo com a linha lida
			Processo* novoProcesso = new ComputingProcess(novoPid, linha);

			//adiciona na fila
			filaSistema->adicionar(novoProcesso);

			count++;
		}
	}
	arquivo.close();
	ofstream limpar("computation.txt", ios::trunc);
	limpar.close();

	cout << "PID " << pid << " (Reading): " << count << " processos de calculo criados." << endl;
}