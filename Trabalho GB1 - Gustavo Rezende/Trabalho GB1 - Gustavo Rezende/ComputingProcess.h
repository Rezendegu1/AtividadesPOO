#pragma once
#include "Processo.h"
#include <string>
using namespace std;

class ComputingProcess : public Processo {
private:
	double numero1;
	double numero2;
	char operacao;
	string expressaoOriginal;

public:
	ComputingProcess(int id, string expressao);
	void execute() override;
	string toString() const override;
};
