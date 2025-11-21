#include <iostream>
#include <cstdlib> 
#include "Personagem.h"

Personagem::Personagem() :
    nome(""),
    habilidade(0),
    energia(0),
    sorte(0),
    tesouro(0),
    provisoes(0),
	armaEquipada(-1) //indice da arma comeca como -1, indicando que nenhuma arma esta equipada
{
}

Personagem::Personagem(string nome, int habilidade, int energia, int sorte) :
    nome(nome),
    habilidade(habilidade),
    energia(energia),
    sorte(sorte),
    tesouro(0),
    provisoes(2), 
    armaEquipada(-1) 
{
}

Personagem::~Personagem() {
}

string Personagem::getNome() { 
    return this->nome; 
}
int Personagem::getHabilidade() { 
    return this->habilidade; 
}
int Personagem::getEnergia() { 
    return this->energia; 
}
int Personagem::getSorte() { 
    return this->sorte; 
}
int Personagem::getTesouro() { 
    return this->tesouro; 
}
int Personagem::getProvisoes() { 
    return this->provisoes; 
}
vector<Item> Personagem::getInventario() { 
    return this->inventario; 
}

int Personagem::getBonusForcaAtaque() {
    if (this->armaEquipada != -1) {
        return this->inventario[this->armaEquipada].getBonusForcaAtaque();
    }
    return 0;
}

int Personagem::getBonusDano() {
    if (this->armaEquipada != -1) {
        return this->inventario[this->armaEquipada].getBonusDano();
    }
    return 0;
}

void Personagem::tomarDano(int dano) {
    this->energia -= dano;
    if (this->energia < 0) this->energia = 0;
}

void Personagem::curar(int cura) { //para curar o personagem, sendo possivel usar em algumas cenas por exemplo
    this->energia += cura;

    if (this->energia > 24) { //verifica se a energia nao ultrapassou o maximo
        this->energia = 24; //se ultrapassou, seta a energia para o maximo
	}   
}

bool Personagem::usarSorte() {
    if (this->sorte <= 0) { //verifica se ainda tem sorte para gastar
        return false; //se for 0, nao pode usar
    }
    // Lembre-se de chamar srand(time(nullptr)) uma vez no main.cpp
    int rolagem = rand() % 10 + 1; // Numero aleatorio de 1 a 10

	this->sorte--; //decrementa a sorte em 1, com ou sem sucesso
	return rolagem <= this->sorte + 1; //como a sorte foi decrementada, adiciona 1 para compensar e fazer a comparacao com a sorte do personagem
} //vai retornar true se a rolagem for menor ou igual a sorte

bool Personagem::estaVivo() {
    return this->energia > 0;
}

void Personagem::adicionarItem(Item& item) { //aqui a gente passa o item por referencia para n�o criar uma copia
	this->inventario.push_back(item); //push back adiciona o item ao final do vetor inventario
    cout << item.getNome() << " foi adicionado ao inventario!" << endl;
}


void Personagem::usarProvisao() { //diferente do metodo curar, esse metodo so pro jogador, usa um item para se curar
    if (this->provisoes > 0) { //verifica se tem provisoes
        this->provisoes--; 
		energia += 4; //recupera 4 pontos de energia
        curar(4); //chama o metodo curar para recuperar 4 pontos de energia
        
        cout << "Voce usou uma provisao. Energia recuperada." << endl;
    }
    else {
        cout << "Voce nao tem mais provisoes!" << endl;
    }
}


void Personagem::adicionarProvisao(int quantidade) { //adiciona provisoes ao personagem
    this->provisoes += quantidade;
}
void Personagem::adicionarTesouro(int valor) { //dinheiro acumulado
    this->tesouro += valor;
}

void Personagem::equiparArma(int indiceDoInventario) { //esse trecho so serve para verificar se o indice do inventario que o jogador escolheu e valido
	if (indiceDoInventario < 0 || indiceDoInventario >= this->inventario.size()) { //ou seja, se for menor que 0 ou maior que o tamanho do vetor
        cout << "Selecao invalida." << endl; //n�o funciona
        return;
    }

    Item& itemParaEquipar = this->inventario[indiceDoInventario]; //o indice do inventario foi passado por parametro la em cima
                                                                  //se o if anterior foi falso, o codigo continua aqui. 
																  //Essa linha vai ate o vetor do inventario e pega o item na posi��o do indice passado
	if (itemParaEquipar.getTipo() == 'w') { //verifica o tipo do item, se for 'w' (weapon) e uma arma
        this->armaEquipada = indiceDoInventario;
        cout << "Voce equipou: " << itemParaEquipar.getNome() << endl;
    }
    else {
        cout << "Este item nao e uma arma e nao pode ser equipado." << endl;
    }
}

void Personagem::desequiparArma() {
    //Verifica se ha alguma arma equipada
    if (this->armaEquipada == -1) {
        cout << "Nenhuma arma esta equipada para desequipar." << endl;
        return;
    }

    //Pega o nome da arma antes de a desequipar (para a mensagem)
    string nomeArma = this->inventario[this->armaEquipada].getNome();

    //Acao de desequipar: reseta o indice para -1
    this->armaEquipada = -1;

    cout << "Voce desequipou: " << nomeArma << endl;
}

int Personagem::getIndiceArmaEquipada() {
    return this->armaEquipada;
}

void Personagem::mostrarInventario() { //metodo para mostrar o inventario do personagem e seus atributos
	system("cls"); //limpa a tela
    cout << "\n--- INVENTARIO DE " << this->nome << " ---" << endl;
    cout << "Habilidade: " << this->habilidade << " | Energia: " << this->energia << " | Sorte: " << this->sorte << endl;
    cout << "Tesouro: " << this->tesouro << " | Provisoes: " << this->provisoes << endl;
    cout << "--------------------" << endl;
    cout << "Equipamento:" << endl;

    string nomeArma = "Nenhuma"; // Comeca com o valor padrao "Nenhuma"
    // Verifica se o indice da arma e valido (diferente de -1)
    if (this->armaEquipada != -1) {
        // Se for valido, pega o nome da arma na posicao correta do inventario
        nomeArma = this->inventario[this->armaEquipada].getNome();
    }
    cout << "  Arma: " << nomeArma << endl; 
	cout << "--------------------" << endl;                                                         //ou seja, se tiver uma arma equipada, getNome da arma
	cout << "Itens na mochila:" << endl;    												 //se nao tiver, mostra "Nenhuma"                                   
	if (this->inventario.empty()) {  //aqui e onde ele vai printar os itens do invent�rio
        cout << "  (Vazia)" << endl; //se tiver vazio, printa vazio
    }
    else {
        for (size_t i = 0; i < this->inventario.size(); ++i) { //loop para percorrer o vetor do inventario
            cout << "  " << i + 1 << ". " << this->inventario[i].getNome() << endl; //printa indice do item + seu nome
        }
    }
    cout << "--------------------" << endl;
}
