#include "WritingProcess.h"
#include <iostream>
using namespace std;

WritingProcess::WritingProcess(int id, string expre) : Processo(id, "Writing") {
	expressao = expre;
}

void WritingProcess::execute() {
	ofstream arquivo("computation.txt", ios::app);

	if (arquivo.is_open()) {
		arquivo << expressao << endl;
		cout << "Pid " << pid << "Gravacao: Expressao '" << expressao << "' gravada com sucesso." << endl;
		arquivo.close();
	}
	else {
		cout << "Erro: nao foi possivel abrir o arquivo" << endl;
	}
}

string WritingProcess::toString() const {
	return Processo::toString() + ";" + expressao;
}