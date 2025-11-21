#include <iostream>
#include <vector>
#include <cstdlib> 
#include "Batalha.h"

Batalha::Batalha(Personagem* jogador, Monstro* inimigo) :
    jogador(jogador),
    inimigo(inimigo)
{
}

bool Batalha::executar() {
    cout << "\n--- A BATALHA COMECOU! ---" << endl;

    // O loop continua enquanto ambos estiverem vivos
    while (jogador->estaVivo() && inimigo->estaVivo()) {
        exibirStatus();
        turnoDoJogador();

        // Se o inimigo morrer no turno do jogador, a batalha acaba
        if (!inimigo->estaVivo()) {
            break;
        }

        turnoDoInimigo();
    }

    cout << "\n--- FIM DA BATALHA ---" << endl;

    if (jogador->estaVivo()) {
        cout << "Voce venceu a batalha!" << endl;
        return true;
    }
    else {
        cout << "Voce foi derrotado..." << endl;
        return false;
    }
}

// Mostra a energia atual tanto do jogador quanto do monstro.
void Batalha::exibirStatus() {
    cout << "----------------------------------------" << endl;
    cout << "  " << jogador->getNome() << " - Energia: " << jogador->getEnergia() << endl;
    cout << "  " << inimigo->getNome() << " - Energia: " << inimigo->getEnergia() << endl;
    cout << "----------------------------------------" << endl;
}

void Batalha::turnoDoJogador() { //aqui tem toda a logica do turno do jogador
    cout << "\n--- SEU TURNO ---" << endl; //primeiro suas possibilidades de acao
    cout << "Escolha sua acao:" << endl;
    cout << "1. Atacar" << endl;
    cout << "2. Usar Item" << endl;
    cout << "3. Tentar Fugir" << endl;

    int escolha;
    cin >> escolha;

    if (escolha == 1) { // ATACAR
        int faJogador = calcularForcaAtaque(jogador->getHabilidade() + jogador->getBonusForcaAtaque()); //o dano do jogador pode ser aumentado por armas
        int faInimigo = calcularForcaAtaque(inimigo->getHabilidade()); //o dano do inimigo nao pode ser aumentado por nada
        cout << "Sua Forca de Ataque: " << faJogador << " | Inimigo: " << faInimigo << endl;

        if (faJogador > faInimigo) { //se a forca de ataque do jogador for maior que a do inimigo, o jogador acerta
            cout << "Voce acertou o inimigo!" << endl;

            char usarSorteEscolha;
            cout << "Deseja Testar sua Sorte para ampliar o dano? (S/N): "; //opcional, sorte pode aumentar ou diminuir o dano
            cin >> usarSorteEscolha;

            if (usarSorteEscolha == 'S' || usarSorteEscolha == 's') {
                if (jogador->usarSorte()) { //se o jogador tiver sorte, o dano e ampliado
                    cout << "GOLPE DE SORTE! O dano e dobrado!" << endl;
                    inimigo->tomarDano(4);
                }
                else {
                    cout << "AZAR! Seu golpe foi mais fraco." << endl; //se tiver azar, o dano é penalizado
                    inimigo->tomarDano(1); // Dano penalizado
                }
            }
            else { //se ele decidir nao usar a sorte, o dano é normal
                inimigo->tomarDano(2);
            }
        }
        else { //se a forca de ataque do inimigo for maior ou igual, o inimigo defende seu ataque
            cout << "O inimigo defendeu o seu ataque." << endl;
        }
    }
    else if (escolha == 2) { // USAR ITEM
        vector<Item> inventario = jogador->getInventario(); //primeiro o codigo chama o get inventario do jogador
        cout << "Qual item voce quer usar?" << endl; //isso cria uma copia de todos os itens do inventario do jogador
        for (size_t i = 0; i < inventario.size(); ++i) {  //ele percorre essa lista de itens e exibe um menu numerado para o jogador, mostrando o nome de cada item
            cout << i + 1 << ". " << inventario[i].getNome() << endl;
        }
        cout << "0. Cancelar" << endl; //vai ter um 0 no final para cancelar a acao

        int escolhaItem;
        cin >> escolhaItem;

        if (escolhaItem > 0 && escolhaItem <= inventario.size()) {
            Item& itemEscolhido = inventario[escolhaItem - 1];

            if (itemEscolhido.getNome() == "Pocao de Cura") {
                cout << "Voce bebe a pocao de cura." << endl;
                jogador->curar(7);
            }
            else {
                cout << "Este item nao tem efeito em batalha. Voce perde o turno." << endl;
            }
        }
        else {
            cout << "Acao cancelada. Voce perde o turno." << endl;
        }

    }
    else if (escolha == 3) { // FUGIR
        if (inimigo->isFugaPermitida()) {
            cout << "Voce conseguiu escapar da batalha!" << endl;
            inimigo->tomarDano(999); // Forca o fim da batalha, tratando a fuga como "vitoria" do monstro
        }
        else {
            cout << "Voce tenta fugir, mas o " << inimigo->getNome() << " bloqueia seu caminho! Voce perde o turno." << endl;
        }
    }
}

// Contem a logica para as acoes do inimigo.
void Batalha::turnoDoInimigo() {
    cout << "\n--- TURNO DO INIMIGO ---" << endl;

    int faInimigo = calcularForcaAtaque(inimigo->getHabilidade());
    int faJogador = calcularForcaAtaque(jogador->getHabilidade());
    cout << "Forca de Ataque do " << inimigo->getNome() << ": " << faInimigo << " | Sua Defesa: " << faJogador << endl;

    if (faInimigo > faJogador) {
        cout << "O inimigo acertou voce!" << endl;
        jogador->tomarDano(2);
    }
    else {
        cout << "Voce conseguiu defender o ataque do inimigo." << endl;
    }
}

// Calcula a Forca de Ataque conforme a regra do PDF.
int Batalha::calcularForcaAtaque(int habilidade) {
    int rolagem = rand() % 10 + 1; // Gera um numero de 1 a 10
    return habilidade + rolagem;
}