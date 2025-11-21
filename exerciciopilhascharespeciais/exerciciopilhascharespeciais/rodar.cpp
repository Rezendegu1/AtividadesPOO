#include "rodar.h"
using namespace std;

void Rodar::rodarprograma() {
	string expressao;
	char continuar;

	do {
		cout << endl << "Digite a expressao";
		cin >> expressao;
		Utilitarios util;

		if (util.verificaBalanco(expressao)) {
			cout << "Expressao balanceada";
		} else { 
			cout << "Expressao desbalanceada";
		}
		cout << endl << "deseja verificar outra expressao? " << endl;
		cin >> continuar;
	} while (continuar == 's' || continuar == 'S');
}