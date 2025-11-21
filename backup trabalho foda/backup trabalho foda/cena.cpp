#include "Cena.h"
#include <fstream> //biblioteca file stream, serve para ler arquivos
#include <iostream>
#include <sstream> // biblioteca para tratar a string como se fosse um arquivo, o que facilita na sua divisão

static vector<string> split(const string& s, char separador) { //static faz com que essa funcao seja visivel apenas nesse arquivo
    vector<string> pedacos; //essa funcao divide uma string em varias strings menores, usando um caractere como separador
    //ou seja, isso é uma lista de pedacos de texto
    string pedaco; //tipo, Adaga;w;1.0;2; - separador é o caractere que separa essas partes, nesse caso é o ';'
    istringstream pedacoStream(s); //istringstream lê dados de uma string como se fosse um arquivo
    //ou seja, a string s é tratada como um arquivo, e o pedacoStream é o "arquivo" que lê essa string
    while (getline(pedacoStream, pedaco, separador)) { //esse while diz que enquanto o getline conseguir ler um pedaco, continua a executar o que ta dentro da {}
        pedacos.push_back(pedaco);                     //o getline é o que da a ordem para a "maquina de leitura", cada vez que ele é chamado, ele faz:
    }                                                  //1. Comeca a ler do ponto onde o "cursor" da pedacoStream parou.
    return pedacos;                                    //2.Continua a ler caractere por caractere ate encontrar o ';'.
    //3.Pega em tudo o que leu antes do separador e guarda na variavel pedaco.
}                                                  //4.Move o "cursor" da pedacoStream para a posicao logo depois do; que ela encontrou.
                                                   //5.Se ela conseguiu ler alguma coisa, a funcao getline retorna true, se não, retorna false e o loop quebra.

// --- M?TODO PRINCIPAL DE CARREGAMENTO ---

bool Cena::carregar(int numeroCena) {
    // 1. Limpa os dados da cena anterior para evitar lixo de mem?ria
    delete item;
    item = nullptr;
    delete inimigo;
    inimigo = nullptr;
    textoPrincipal.clear();
    textoEscolhas.clear();
    cenasDestino.clear();
    cenaVitoria = 0;
    cenaDerrota = 0;

    // 2. Abre o arquivo da cena (ex: "cenas/1.txt")
    ifstream arquivo("scenes/" + to_string(numeroCena) + ".txt");
    if (!arquivo.is_open()) {
        cerr << "Erro: Nao foi possivel abrir o arquivo da cena " << numeroCena << endl;
        return false; // Retorna false se o arquivo n?o existir (pode ser o fim do jogo)
    }

    string linha;
    bool lendoMonstro = false;

    // 3. L? o arquivo linha por linha
    while (getline(arquivo, linha)) {
        if (linha.empty()) continue;

        // 4. Interpreta cada tipo de linha de acordo com as regras do PDF

        // Linha de ESCOLHA (come?a com '#') [cite: 101, 108, 109, 110]
        if (linha[0] == '#') {
            size_t posDoisPontos = linha.find(':');
            string numStr = linha.substr(1, posDoisPontos - 1);
            string texto = linha.substr(posDoisPontos + 2); // Pula o ':' e o espa?o
            cenasDestino.push_back(stoi(numStr));
            textoEscolhas.push_back(texto);
        }
        // Linha de ITEM (come?a com 'I:') [cite: 107, 127, 141, 143]
        else if (linha.rfind("I:", 0) == 0) {
            vector<string> dados = split(linha.substr(2), ';'); // Pula o "I:"
            // nome;tipo;combate;FA;dano
            if (dados.size() == 5) {
                Item* novoItem = new Item(dados[0], dados[1][0], stoi(dados[2]), stoi(dados[3]), stoi(dados[4]));
                if (lendoMonstro && inimigo) {
                    inimigo->setItemDrop(*novoItem); // Define o item que o monstro dropa
                    delete novoItem; // A c?pia foi feita, podemos deletar o tempor?rio
                }
                else {
                    this->item = novoItem; // Item encontrado na cena
                }
            }
        }
        // Linha de NOME DO MONSTRO (come?a com 'N:') [cite: 120, 135]
        else if (linha.rfind("N:", 0) == 0) {
            lendoMonstro = true;
            inimigo = new Monstro(linha.substr(2), 0, 0); // Cria o monstro, stats v?m depois
        }
        // Linha de HABILIDADE do monstro [cite: 122, 136]
        else if (lendoMonstro && linha.rfind("H:", 0) == 0) {
            // Supondo que voc? crie um m?todo setHabilidade em Monstro
            inimigo->setHabilidade(stoi(linha.substr(2)));
        }
        // Linha de ENERGIA do monstro [cite: 124, 138]
        else if (lendoMonstro && linha.rfind("E:", 0) == 0) {
            // Supondo que voc? crie um m?todo setEnergia em Monstro
            inimigo->setEnergia(stoi(linha.substr(2)));
        }
        else if (lendoMonstro && linha.rfind("S:", 0) == 0) {
            inimigo->setSorte(stoi(linha.substr(3)));
        }
        else if (lendoMonstro && linha.rfind("T:", 0) == 0) {
            inimigo->setTesouro(stoi(linha.substr(3)));
        }
        else if (lendoMonstro && linha.rfind("P:", 0) == 0) {
            inimigo->setProvisoes(stoi(linha.substr(3)));
        }
        else if (lendoMonstro && linha.rfind("FUGIR:", 0) == 0) {
            inimigo->setFugaPermitida(linha.substr(7) != "N");
        }
        // Linha de VIT?RIA/DERROTA (ex: "12:13") [cite: 128, 142]
        else if (lendoMonstro && linha.find(':') != string::npos) {
            size_t posDoisPontos = linha.find(':');
            this->cenaVitoria = stoi(linha.substr(0, posDoisPontos));
            this->cenaDerrota = stoi(linha.substr(posDoisPontos + 1));
        }
        // Se n?o for nenhuma das anteriores, ? texto da hist?ria
        else {
            textoPrincipal += linha + "\n";
        }
    }

    arquivo.close();
    return true;
}

string Cena::getTexto() {
    return this->textoPrincipal;
}

bool Cena::isCenaDeCombate() {
    return this->inimigo != nullptr;
}

Monstro* Cena::getInimigo() {
    return this->inimigo;
}

int Cena::getCenaVitoria() {
    return this->cenaVitoria;
}

int Cena::getCenaDerrota() {
    return this->cenaDerrota;
}

Item* Cena::getItem() {
    return this->item;
}

const vector<string>& Cena::getTextoEscolhas() {
    return this->textoEscolhas;
}

const vector<int>& Cena::getCenasDestino() {
    return this->cenasDestino;
}