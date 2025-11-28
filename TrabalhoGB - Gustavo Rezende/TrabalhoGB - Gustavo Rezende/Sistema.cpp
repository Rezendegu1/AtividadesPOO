#include "Sistema.h"
#include "ComputingProcess.h"
#include "ReadingProcess.h"
#include "PrintingProcess.h"
#include "WritingProcess.h"
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
			cin.ignore();
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
	fila.executarProximo(); //NAO
}

void Sistema::executarEspecifico() {
	int pid;
	cout << "Digite o PID do processo a ser executado: ";
	cin >> pid;
	executarPorPid(pid);
}

void Sistema::salvarFila() {
	cout << "Funcionalidade de Salvar ainda nao implementada na Fila." << endl;
}

void Sistema::carregarFila() {
	cout << "Funcionalidade de Carregar ainda nao implementada na Fila." << endl;
}

void Sistema::executarPorPid(int pidBusca) { // fora da fila
	if (inicio == nullptr) { //get inicio
		cout << "Fila vazia" << endl; 
		return;
	}

	Nodo* atual = inicio;
	//NAO USAR PONTEIRO, COLOCAR UM FOR QUE PERCORRE A FILA INTEIRA, REFAZENDO ELA, TIRANDO O PID BUSCADO E REFAZENDO A ORDEM DA FILA
	Nodo* anterior = nullptr;

	while (atual != nullptr && atual->processo->getPid() != pidBusca) {
		anterior = atual;
		atual = atual->proximo;
	}

	//se nao achou, avisa
	if (atual == nullptr) {
		cout << "Processo PID " << pidBusca << "nao foi encontrado" << endl;
		return;
	}

	//se achou, executa ele
	cout << "Executando PID '" << pidBusca << "'" << endl;
	atual->processo->execute();

	if (anterior == nullptr) {
		inicio = atual->proximo;
		if (atual == fim) {
			fim = nullptr;
		}
	}
	else {
		anterior->proximo = atual->proximo;
		if (atual == fim) {
			fim = anterior;
		}
	}

	delete atual->processo;
	delete atual;
}

void Sistema::imprimirFila() {
	if (inicio == nullptr) {
		cout << "Pool de processos vazio" << endl;
		return;
	}

	Nodo* atual = inicio;
	cout << "======== Pool de Processos ========" << endl;
	while (atual != nullptr) {
		cout << "Pid: " << atual->processo->getPid() << endl;
		cout << " | Tipo: " << atual->processo->getTipo() << endl;
		atual = atual->proximo;
	}
	cout << "---------------------" << endl;
}

void Sistema::salvarArquivo() {
	if (inicio == nullptr) {
		cout << "Fila vazia, nao ha nada para salvar" << endl;
		return;
	}

	ofstream arquivo("fila_backup.txt");
	if (!arquivo.is_open()) {
		cout << "Erro ao criar arquivo backup" << endl;
		return;
	}

	Nodo* atual = inicio;
	while (atual != nullptr) {
		arquivo << atual->processo->toString() << endl;
		atual = atual->proximo;
	}

	arquivo << "Proximo_Pid;" << proximoPid << endl; //VERIFICAR ISSO AQUI, PRA VER SE EU POSSO DAR UM GET NESSE PROXIMO PID
	arquivo.close();
	cout << "Fila salva com sucesso em 'fila_backup.txt'" << endl;
}