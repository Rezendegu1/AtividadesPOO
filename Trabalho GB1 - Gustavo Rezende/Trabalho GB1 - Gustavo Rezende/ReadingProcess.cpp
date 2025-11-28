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

	// Lê linha por linha do arquivo
	while (getline(arquivo, linha)) {
		if (!linha.empty()) {
			// 1. Gera um PID novo usando a fila
			int novoPid = filaSistema->gerarPid();

			// 2. Cria um Processo de Cálculo com a linha lida
			// Ex: linha = "10 + 5"
			Processo* novoProcesso = new ComputingProcess(novoPid, linha);

			// 3. Adiciona na fila
			filaSistema->adicionar(novoProcesso);

			count++;
		}
	}
	arquivo.close();
	ofstream limpar("computation.txt", ios::trunc);
	limpar.close();

	cout << "PID " << pid << " (Reading): " << count << " processos de calculo criados." << endl;
}