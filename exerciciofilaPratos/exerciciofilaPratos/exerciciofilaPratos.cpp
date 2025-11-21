#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "pilha.h"
#include <iostream>
using namespace std;

int gerarAleatorio(int min, int max) {
        return rand() % (max - min + 1) + min;
}

int main()
    {
        int Totalturnos = 10;
        srand(time(0));
        Pilha pilhadepratos;

        for (int turno = 1; turno < Totalturnos; turno++) {
            int pratosLavados = gerarAleatorio(1, 5);
            for (int i = 0; i < pratosLavados; i++) {
                pilhadepratos.push(1);
            }
        }
        int pratossecos = gerarAleatorio(1, 3);
        int pratosremovidos = 0;

        for (int i = 0; i < pratossecos; i++) {
            if (!pilhadepratos.vazio()) {
                pilhadepratos.pop();
                pratosremovidos++;
            }
        }

        cout << "Pratos lavados e nao secos: " << pilhadepratos.size();
    }