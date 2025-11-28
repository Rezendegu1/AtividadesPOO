#include "ComputingProcess.h"
#include <iostream>
#include <sstream> //pra quebrar a string
using namespace std;

ComputingProcess::ComputingProcess(int id, string expressao) : Processo(id, "Computing") {
	expressaoOriginal = expressao;

	stringstream ss(expressao);
	ss >> numero1 >> operacao >> numero2;
}

void ComputingProcess::execute() {
	double resultado = 0;
	bool erro = false;

    switch (operacao) {
    case '+': resultado = numero1 + numero2; break;
    case '-': resultado = numero1 - numero2; break;
    case '*': resultado = numero1 * numero2; break;
    case '/':
        if (numero2 != 0) {
            resultado = numero1 / numero2;
        }
        else {
            cout << "Erro. Divisao por zero." << endl;
            erro = true;
        }
        break;
    default:
        cout << "Operacao invalida (" << operacao << ")!" << endl;
        erro = true;
        break;
    }

    if (!erro) {
        cout << "PID " << pid << " (Calculo): " << expressaoOriginal << " = " << resultado << endl;
    }
}

string ComputingProcess::toString() const {
    //retorna algo como: "1;Computing;10 + 5"
    return Processo::toString() + ";" + expressaoOriginal;
}

string ComputingProcess::getDetalhes() const {
    return expressaoOriginal;
}