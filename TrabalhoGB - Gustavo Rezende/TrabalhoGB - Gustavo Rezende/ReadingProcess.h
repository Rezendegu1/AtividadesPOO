#pragma once
#include "FilaProcessos.h"
using namespace std;

class ReadingProcess : public Processo {
private:
	FilaProcessos* filaSistema; //ponteiro pra eu poder acessar a fila principal

public:
	ReadingProcess(int id, FilaProcessos* fila);
	void execute() override;
};