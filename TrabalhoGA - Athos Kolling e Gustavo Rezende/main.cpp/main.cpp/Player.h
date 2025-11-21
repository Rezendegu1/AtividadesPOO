#pragma once
#include <string>
#include "Inventario.h"

class Player {
public:
    Player();
    Player(const std::string& nome);

    std::string nome;
    int habilidade;
    int energia;
    int sorte;
    bool vivo;
    Inventory inventario;

    void distribuirPontosManual();
    void distribuirPontosAleatorio();
    bool testarSorte();
    void usarProvisao();
    void receberDano(int d);
    bool estaVivo() const;
    void mostrarInventario() const;
    int atacarFA() const; // força de ataque total (dado + habilidade + bônus)
};
