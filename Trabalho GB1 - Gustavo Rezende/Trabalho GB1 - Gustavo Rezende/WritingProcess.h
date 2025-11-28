#pragma once
#include "Processo.h"
#include <string>
#include <fstream> //pra manipular os txt que eu odeio
//os dois trabalhos tinham que ter txt ne sor, ja demorei pra aprender como aquilo funcionava da primeira vez
using namespace std;

class WritingProcess : public Processo {
private:
	string expressao; //essa variavel guarda a expressao que vai ser gravada

public:
	WritingProcess(int id, string expre);
	void execute() override;
	string toString() const override;
};