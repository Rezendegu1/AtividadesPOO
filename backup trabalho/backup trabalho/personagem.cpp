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
    armaEquipada(nullptr) // Ponteiro da arma comeca nulo
{
}

Personagem::Personagem(string nome, int habilidade, int energia, int sorte) :
    nome(nome),
    habilidade(habilidade),
    energia(energia),
    sorte(sorte),
    tesouro(0),
    provisoes(2),
    armaEquipada(nullptr)
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
    if (this->armaEquipada != nullptr) {
        return this->armaEquipada->getBonusForcaAtaque();
    }
    return 0;
}

int Personagem::getBonusDano() {
    if (this->armaEquipada != nullptr) {
        return this->armaEquipada->getBonusDano();
    }
    return 0;
}

void Personagem::tomarDano(int dano) {
    this->energia -= dano;
    if (this->energia < 0) this->energia = 0;
}

void Personagem::curar(int cura) { //para curar o personagem, sendo possivel usar em algumas cenas por exemplo
    this->energia += cura;
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

void Personagem::adicionarItem(Item& item) { //aqui a gente passa o item por referencia para não criar uma copia
    this->inventario.push_back(item); //push back adiciona o item ao final do vetor inventario
    cout << item.getNome() << " foi adicionado ao inventario!" << endl;
}


void Personagem::usarProvisao() { //diferente do metodo curar, esse metodo é só pro jogador, usa um item para se curar
    if (this->provisoes > 0) { //verifica se tem provisoes
        this->provisoes--;
        this->energia += 4; // Uma provisao recupera sempre 4 pontos de vida
        cout << "Voce usou uma provisao. Energia recuperada." << endl;
    }
    else {
        cout << "Voce nao tem mais provisoes!" << endl;
    }
}

void Personagem::adicionarTesouro(int valor) { //dinheiro acumulado
    this->tesouro += valor;
}

void Personagem::equiparArma(int indiceDoInventario) { //esse trecho só serve para verificar se o indice do inventario que o jogador escolheu é valido
    if (indiceDoInventario < 0 || indiceDoInventario >= this->inventario.size()) { //ou seja, se for menor que 0 ou maior que o tamanho do vetor
        cout << "Selecao invalida." << endl; //não funciona
        return;
    }

    Item& itemParaEquipar = this->inventario[indiceDoInventario]; //o indice do inventario foi passado por parâmetro lá em cima
    //se o if anterior foi falso, o código continua aqui. 
    //Essa linha vai até o vetor do inventario e pega o item na posição do indice passado
    if (itemParaEquipar.getTipo() == 'w') { //verifica o tipo do item, se for 'w' (weapon) é uma arma
        this->armaEquipada = &itemParaEquipar;
        cout << "Voce equipou: " << itemParaEquipar.getNome() << endl;
    }
    else {
        cout << "Este item nao e uma arma e nao pode ser equipado." << endl;
    }
}

void Personagem::mostrarInventario() { //método para mostrar o inventário do personagem e seus atributos
    system("cls"); //limpa a tela
    cout << "\n--- INVENTARIO DE " << this->nome << " ---" << endl;
    cout << "Habilidade: " << this->habilidade << " | Energia: " << this->energia << " | Sorte: " << this->sorte << endl;
    cout << "Tesouro: " << this->tesouro << " | Provisoes: " << this->provisoes << endl;
    cout << "--------------------" << endl;
    cout << "Equipamento:" << endl;
    cout << "  Arma: " << (this->armaEquipada ? this->armaEquipada->getNome() : "Nenhuma") << endl; //? é um então
    cout << "--------------------" << endl;                                                         //ou seja, se tiver uma arma equipada, getNome da arma
    cout << "Itens na mochila:" << endl;    												 //se não tiver, mostra "Nenhuma"                                   
    if (this->inventario.empty()) {  //aqui é onde ele vai printar os itens do inventário
        cout << "  (Vazia)" << endl; //se tiver vazio, printa vazio
    }
    else {
        for (size_t i = 0; i < this->inventario.size(); ++i) { //loop para percorrer o vetor do inventario
            cout << "  " << i + 1 << ". " << this->inventario[i].getNome() << endl; //printa indice do item + seu nome
        }
    }
    cout << "--------------------" << endl;
}