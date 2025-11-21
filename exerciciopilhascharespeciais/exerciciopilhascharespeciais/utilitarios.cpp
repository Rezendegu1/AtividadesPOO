#include "utilitarios.h"

Utilitarios::Utilitarios() {

}

bool Utilitarios::corresponde(char aberto, char fechado) {
    return (aberto == '(' && fechado == ')') ||
        (aberto == '[' && fechado == ']') ||
        (aberto == '{' && fechado == '}');
}

bool Utilitarios::verificaBalanco(const string& expressao) {
    Pilha pilha;
    for (int i = 0; i < expressao.length(); i++) {
        char caractere = expressao[i];

        if (caractere == '(' || caractere == '{' || caractere == '[') {
            pilha.push(caractere);
        }

        else if (caractere == ')' || caractere == '}' || caractere == ']') {
            if (pilha.vazio()) {
                cout << "Erro" << endl;
                return false;
            }
            char topo = pilha.top();

            if (!corresponde(topo, caractere)) {
                cout << "Erro, MISMATCH" << endl;
                return false;
            }

            pilha.pop();
        }
    }
    if (!pilha.vazio()) {
        cout << "Erro: expressao nao fechou. Sobrou: " << pilha.top() << endl;
        return false;
    }
    return true;
}