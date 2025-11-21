#include <iostream>
#include <vector>
#include <cstdlib> //para a randomizacao
#include "Batalha.h"
#include "Item.h"    

Batalha::Batalha(Personagem* jogador, Monstro* inimigo) :
    jogador(jogador),
    inimigo(inimigo)
{
}

bool Batalha::executar() {
    cout << "\n--- A BATALHA COMECOU! ---" << endl;

    while (jogador->estaVivo() && inimigo->estaVivo()) { //esse loop s acaba quando um dos dois esta morto
        exibirStatus(); //mostra a vida atual de ambos
        turnoDoJogador(); //executa o turno do jogador

        if (!inimigo->estaVivo()) { //se o inimigo morrer no turno do jogador, a batalha acaba
            break;
        }

        turnoDoInimigo(); 
    }

    cout << "\n--- FIM DA BATALHA ---" << endl;

    if (jogador->estaVivo()) { //verifica se o jogador esta vivo 
        cout << "Voce venceu a batalha!" << endl; //se sim, mostra vitoria
        return true; //e retorna true para que o jogo saiba que o jogador venceu
    }
    else {
        cout << "Voce foi derrotado..." << endl; //aqui acontece o oposto
        return false;
    }
}

void Batalha::exibirStatus() {
    cout << "----------------------------------------" << endl;
    cout << "  " << jogador->getNome() << " - Energia: " << jogador->getEnergia() << endl; //mostra a energia do jogador e do inimigo a cada turno 
    cout << "  " << inimigo->getNome() << " - Energia: " << inimigo->getEnergia() << endl;
    cout << "----------------------------------------" << endl;
}

void Batalha::turnoDoJogador() {
    cout << "\n--- SEU TURNO ---" << endl;
    cout << "Escolha sua acao:" << endl;
    cout << "1. Atacar" << endl;
    cout << "2. Usar Item" << endl;
    cout << "3. Tentar Fugir" << endl;

    int escolha;
    cin >> escolha;

    if (escolha == 1) { // ATACAR
        // Calcula a Forca de Ataque do jogador, somando a Habilidade base com o bonus da arma.
        int faJogador = calcularForcaAtaque(jogador->getHabilidade() + jogador->getBonusForcaAtaque());
        // Calcula a Forca de Ataque do inimigo.
        int faInimigo = calcularForcaAtaque(inimigo->getHabilidade());
        cout << "Sua Forca de Ataque: " << faJogador << " | Inimigo: " << faInimigo << endl;

        if (faJogador > faInimigo) { //se a forca de ataque do jogador for maior, acerta o ataque
            cout << "Voce acertou o inimigo!" << endl;
            char usarSorteEscolha; 
            cout << "Deseja Testar sua Sorte para ampliar o dano? (S/N): "; //e da a oportunidade de usar a sorte para ampliar o dano
            cin >> usarSorteEscolha;

            int bonusDeDano = jogador->getBonusDano(); // Pega o bonus da arma equipada

            if (usarSorteEscolha == 'S' || usarSorteEscolha == 's') {
                if (jogador->usarSorte()) { //se o teste de sorte der certo
                    cout << "GOLPE DE SORTE! O dano e dobrado!" << endl;
                    inimigo->tomarDano(4 + bonusDeDano); // aumenta o dano
                }
                else {
                    cout << "AZAR! Seu golpe foi mais fraco." << endl;
                    inimigo->tomarDano(1 + bonusDeDano); // Dano de azar + bonus da arma
                }
            }
            else { //caso nao use a sorte
                inimigo->tomarDano(2 + bonusDeDano); // Dano normal + bonus da arma
            }
        }
        else { //se a forca de ataque do jogador for menor que do inimigo 
            cout << "O inimigo defendeu o seu ataque." << endl;
        }
    }

    else if (escolha == 2) { // USAR ITEM
        vector<Item> inventario = jogador->getInventario();
        cout << "Qual item voce quer usar?" << endl; //mostra a lista de itens do inventario 
        for (size_t i = 0; i < inventario.size(); ++i) {
            cout << i + 1 << ". " << inventario[i].getNome() << endl;
        }
        cout << "0. Cancelar" << endl;
        int escolhaItem;
        cin >> escolhaItem;

        if (escolhaItem > 0 && escolhaItem <= inventario.size()) {
            Item& itemEscolhido = inventario[escolhaItem - 1]; 
            cout << "Tentando usar o item de nome: [" << itemEscolhido.getNome() << "]" << endl;
            if (itemEscolhido.getNome() == "Pocao de Cura" || itemEscolhido.getNome() == "Frasco com Agua da Fonte") { //verifica se o nome do item e um dos itens de cura conhecidos
                cout << "Voce usa o item de cura e sente suas forcas a voltar." << endl;
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
        if (inimigo->isFugaPermitida()) { //verifica se o inimigo permite a fuga
            cout << "Voce conseguiu escapar da batalha!" << endl;
            inimigo->tomarDano(999); //mata o inimigo para encerrar a batalha
        }
        else {
            cout << "Voce tenta fugir, mas o " << inimigo->getNome() << " bloqueia seu caminho! Voce perde o turno." << endl; //caso nao possa fugir
        }
    }
}

void Batalha::turnoDoInimigo() {
    cout << "\n--- TURNO DO INIMIGO ---" << endl;

    int faInimigo = calcularForcaAtaque(inimigo->getHabilidade());
    int faJogador = calcularForcaAtaque(jogador->getHabilidade());
    cout << "Forca de Ataque do " << inimigo->getNome() << ": " << faInimigo << " | Sua Defesa: " << faJogador << endl;

    if (faInimigo > faJogador) {
        cout << "O inimigo acertou voce!" << endl;

        char usarSorteEscolha;
        cout << "Deseja Testar sua Sorte para reduzir o dano? (S/N): ";
        cin >> usarSorteEscolha;

        if (usarSorteEscolha == 'S' || usarSorteEscolha == 's') {
            if (jogador->usarSorte()) {
                cout << "POR SORTE! Voce desvia parcialmente do golpe." << endl;
                jogador->tomarDano(1); // Dano reduzido
            }
            else {
                cout << "AZAR! O golpe acerta um ponto vital." << endl;
                jogador->tomarDano(3); // Dano penalizado
            }
        }
        else {
            jogador->tomarDano(2); // Dano normal
        }
    }
    else {
        cout << "Voce conseguiu defender o ataque do inimigo." << endl;
    }
}

int Batalha::calcularForcaAtaque(int habilidade) {
    int rolagem = rand() % 10 + 1;
    return habilidade + rolagem;
}