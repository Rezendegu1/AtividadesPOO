#include "Sistema.h"
#include "ComputingProcess.h"
#include "ReadingProcess.h"
#include "PrintingProcess.h"
#include "WritingProcess.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

Sistema::Sistema() {

}

void Sistema::iniciar() {
	int opcao = 0;

	do {
		mostrarMenu();
		cin >> opcao;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			opcao = -1;
		}

		switch (opcao) {
		case 1:
			criarProcesso();
			break;
		case 2:
			executarProximo();
			break;
		case 3:
			executarEspecifico();
			break;
		case 4:
			salvarFila();
			break;
		case 5:
			carregarFila();
			break;
		case 0:
			cout << "Finalizando sistema" << endl;
			break;
		default:
			cout << "Opcao invalida" << endl;
		}
	} while (opcao != 0);
}

void Sistema::mostrarMenu() {
	cout << endl << "=== SISTEMA DE PROCESSOS ===" << endl;
	cout << "1. Criar Processo" << endl;
	cout << "2. Executar Proximo" << endl;
	cout << "3. Executar Processo Especifico por PID" << endl;
	cout << "4. Salvar Fila em Arquivo" << endl;
	cout << "5. Carregar Fila do Arquivo" << endl;
	cout << "0. Sair" << endl;
	cout << "Escolha: ";
}

void Sistema::criarProcesso() {
	int tipo;
	cout << "--- Criar Processo ---" << endl;
	cout << "1 - Calculation Process/Calculo" << endl;
	cout << "2 - Writing Process/Gravacao" << endl;
	cout << "3 - Reading Process/Leitura" << endl;
	cout << "4 - Printing Process/Impressao" << endl;
	cout << "Escolha o tipo" << endl;
	cin >> tipo;
	cin.ignore();

	int pid = fila.gerarPid();

	if (tipo == 1) {
		string expr;
		cout << "Digite a expressao (ex: 10 + 5): ";
		getline(cin, expr);

		fila.adicionar(new ComputingProcess(pid, expr));
		cout << "Processo de Calculo criado com PID " << pid << endl;
	}
	else if (tipo == 2) {
		string expr;
		cout << "Digite a expressao para gravar: ";
		getline(cin, expr);
		fila.adicionar(new WritingProcess(pid, expr));
		cout << "Processo de Gravacao criado com PID " << pid << endl;
	}
	else if (tipo == 3) {
		fila.adicionar(new ReadingProcess(pid, &fila));
		cout << "Processo de Leitura criado com PID " << pid << endl;
	}
	else if (tipo == 4) {
		fila.adicionar(new PrintingProcess(pid, &fila));
		cout << "Processo de Impressao criado com PID " << pid << endl;
	}
	else {
		cout << "Tipo invalido! Processo nao criado." << endl;
	}
}



void Sistema::executarProximo() {
	if (fila.vazia()) {
		cout << "Fila vazia" << endl;
		return;
	}

	Processo* p = fila.removerInicio();
	if (p != nullptr) {
		cout << "Executando proximo pid (Pid: " << p->getPid() << "): " << endl;
		p->execute();
		delete p;
	}
}

void Sistema::executarEspecifico() {
	int pid;
	cout << "Digite o PID do processo a ser executado: ";
	cin >> pid;
	executarPorPid(pid);
}

void Sistema::executarPorPid(int pidBusca) { // fora da fila
	if (fila.vazia()) {
		cout << "Fila vazia" << endl;
		return;
	}

	int tamanhoOriginal = fila.getTamanho();
	Processo* encontrado = nullptr;

	for (int i = 0; i < tamanhoOriginal; i++) {
		Processo* p = fila.removerInicio();

		if (p->getPid() == pidBusca) {
			encontrado = p;
		}
		else {
			fila.adicionar(p);
		}
	}

	if (encontrado != nullptr) {
		cout << "Executando pid especifico (" << pidBusca << ")" << endl;
		encontrado->execute();
		delete encontrado;
	}
	else {
		cout << "Processo pid " << pidBusca << " nao encontrado" << endl;
	}

}

void Sistema::imprimirFila() {
	if (fila.vazia()) {
		cout << "Pool de processos vazio" << endl;
		return;
	}

	int tamanho = fila.getTamanho();
	cout << "Fila de processos" << endl;

	for (int i = 0; i < tamanho; i++) {
		Processo* p = fila.removerInicio();

		cout << "Pid: " << p->getPid() << endl;
		cout << " Tipo: " << p->getTipo() << endl;

		fila.adicionar(p);
	}
	cout << endl;
}

void Sistema::salvarFila() {
	if (fila.vazia()) {
		cout << "Fila vazia, nada para salvar." << endl;
		return;
	}

	ofstream arquivo("fila_backup.txt");
	if (!arquivo.is_open()) {
		cout << "Erro ao criar arquivo backup" << endl;
		return;
	}

	int tamanho = fila.getTamanho();

	for (int i = 0; i < tamanho; i++) {
		Processo* p = fila.removerInicio();

		arquivo << p->toString() << endl;

		fila.adicionar(p);
	}

	// Salva o contador de PID
	arquivo << "Proximo_Pid;" << fila.getProximoPid() << endl;

	arquivo.close();
	cout << "Fila salva com sucesso em 'fila_backup.txt'!" << endl;
}

void Sistema::carregarFila() {
	ifstream arquivo("fila_backup.txt");

	// pra verificar se o arquivo existe
	if (!arquivo.is_open()) {
		cout << "Arquivo de backup nao encontrado." << endl;
		return;
	}

	// limpa a fila antes de colocar uma nova
	if (!fila.vazia()) {
		cout << "Limpando fila atual para carregar backup" << endl;
		while (!fila.vazia()) {
			Processo* lixo = fila.removerInicio();
			delete lixo;
		}
	}

	string linha;
	int count = 0;

	while (getline(arquivo, linha)) {
		if (linha.empty()) continue;

		stringstream ss(linha);
		string s_pid, tipo, dados;

		getline(ss, s_pid, ';'); //pega o PID (ou a tag Proximo_Pid)
		getline(ss, tipo, ';');  //pega o Tipo (ou o valor do contador)

		//verifica se é a linha especial de configuração
		if (s_pid == "Proximo_Pid") {
			try {
				//restaura o contador da fila
				fila.setProximoPid(stoi(tipo));
			}
			catch (...) {
				cout << "Erro ao ler config de PID." << endl;
			}
			continue; //pula para a próxima linha do while
		}

		// Se chegou aqui, é um processo normal
		int pid = stoi(s_pid);
		Processo* novo = nullptr;

		// 3. Fábrica de Processos: Cria o objeto certo baseado no texto
		if (tipo == "Computing") {
			getline(ss, dados); // Lê o resto da linha (expressão)
			novo = new ComputingProcess(pid, dados);
		}
		else if (tipo == "Writing") {
			getline(ss, dados); // Lê o resto da linha (expressão)
			novo = new WritingProcess(pid, dados);
		}
		else if (tipo == "Reading") {
			// Reading precisa do ponteiro da fila
			novo = new ReadingProcess(pid, &fila);
		}
		else if (tipo == "Printing") {
			// Printing precisa do ponteiro da fila
			novo = new PrintingProcess(pid, &fila);
		}

		// 4. Adiciona na fila
		if (novo != nullptr) {
			fila.adicionar(novo);
			count++;
		}
	}

	arquivo.close();
	cout << "Backup carregado com sucesso! " << count << " processos restaurados." << endl;
}