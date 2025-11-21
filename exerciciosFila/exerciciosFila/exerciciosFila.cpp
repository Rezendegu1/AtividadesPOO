#include "fila.h"
#include "filaprioridade.h"
#include <iostream>

int main()
{
	Fila fila1;
	Pessoa p1(10, "gerson", 0);
	Pessoa p2(11, "rogerio", 0);
	fila1.chegou(p1);
	fila1.chegou(p2);
	fila1.imprimirFila();
	cout << fila1.front().nome << endl;
	fila1.atendido();
	cout << fila1.front().nome << endl;

	FilaP fila2;
	Pessoa p3(80, "idoso", 3);
	Pessoa p4(25, "gravida", 2);
	Pessoa p5(15, "jovem", 1);
	fila2.chegouPrioridade(p3);
	fila2.chegouPrioridade(p4);
	fila2.chegouPrioridade(p5);
	fila2.imprimirFilaP();
	fila2.atendido();
	fila2.front();
	fila2.imprimirFilaP();
}

