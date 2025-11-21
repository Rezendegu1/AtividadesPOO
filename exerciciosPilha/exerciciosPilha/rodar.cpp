#include <iostream>
#include "rodar.h"
#include "pilhadechar.h"
using namespace std;

Rodar::Rodar() {
}

void Rodar::exercicio1(PilhaDeChar& pilhaExercicio1) {
	pilhaExercicio1.push('A');
	pilhaExercicio1.push('B');
	pilhaExercicio1.push('C');

	cout << "O topo da pilha e: " << pilhaExercicio1.top() << endl;
	cout << "Removendo o topo da pilha" << endl;
	pilhaExercicio1.pop();
	cout << "O novo topo da pilha e: " << pilhaExercicio1.top() << endl;
}

void Rodar::exercicio2(PilhaDeChar& pilhaExercicio2) {
	string s;
	cout << "Digite a string" << endl;
	cin >> s;

	for (int i=0; i < s.length(); i++) {
		char caractere = s[i];
		pilhaExercicio2.push(caractere);
	}

	cout << "String '" << s << "' empilhada, o topo agora e: " << pilhaExercicio2.top() << endl;
	
	string palavraInvertida;
	for (int i=0; i < s.length(); i++){
		char c = pilhaExercicio2.top();
		palavraInvertida = palavraInvertida + c;
		pilhaExercicio2.pop();
	}

	cout << "A palavra invertida e " << palavraInvertida << endl;
}

void Rodar::exercicio3(PilhaDeChar& pilhaExercicio3) {
	string s; 
	cout << "Digite a string" << endl;
	cin >> s; 

	for (int i = 0; i < s.length(); i++) {
		char caractere = s[i];
		pilhaExercicio3.push(caractere);
	}

	string palavraInvertida;
	for (int i = 0; i < s.length(); i++) {
		char c = pilhaExercicio3.top();
		palavraInvertida = palavraInvertida + c;
		pilhaExercicio3.pop();
	}

	if (palavraInvertida == s) {
		cout << "E palindromo" << endl;
	}
	else {
		cout << "Nao e palindromo" << endl;
	}


}

