#pragma once
#include "FilaProcessos.h"

class PrintingProcess : public Processo {
private:
	FilaProcessos* filaSistema;

public:
	PrintingProcess(int id, FilaProcessos* fila);
	void execute() override;
};
