#pragma once
#include "Personagem.h"
#include "Monstro.h"

class Batalha {
	public: 
		Batalha(Personagem* jogador, Monstro* inimigo);

		bool executar(); 

	private: 

		Personagem* jogador;
		Monstro* inimigo;

		void exibirStatus();
		void turnoDoJogador();
		void turnoDoInimigo();
		int calcularForcaAtaque(int habilidade);
};

		
