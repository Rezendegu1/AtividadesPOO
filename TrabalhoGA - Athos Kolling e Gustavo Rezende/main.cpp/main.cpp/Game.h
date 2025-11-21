#pragma once
#include "Personagem.h"
#include "Cena.h"
#include <vector>

class Jogo {
public:
	Jogo();
	~Jogo();
	void iniciar(); //inicia o jogo, carregando o personagem e a primeira cena
	

private:

	//Funcoes para cada tela de jogo
	void telaDeAbertura();
	void criarNovoJogo(int slot);
	void carregarJogoSalvo(int slot);
	void exibirCreditos();
	void telaDeInventario(bool criandoPersonagem);
	void telaPrincipalDoJogo(int slot);
	void telaDeCombate(Monstro* inimigo);
	void abrirInventario();

	//Funcoes de logica de jogo
	void processarEscolha(int escolha);
	void executarCombate(Monstro* inimigo);

	//Funcoes de persistencia
	void salvarProgresso(int slot);
	bool carregar(int slot);
	int escolherSlot();

	Personagem* jogador; //ponteiro para o personagem do jogador
	Cena cenaAtual; //cena atual do jogo
	int numeroCenaAtual; //numero da cena atual
	vector<int> cenasVisitadas; //para rastrear as cenas visitadas
	

};