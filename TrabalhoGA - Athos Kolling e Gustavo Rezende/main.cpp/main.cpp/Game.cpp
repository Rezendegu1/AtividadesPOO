#include "Game.h"
#include "Batalha.h"
#include <iostream>//cout e cin basico
#include <fstream>//file stream para fluxo de arquivos, ler os .txt, salvar e carregar eles
#include <ctime>// pra randomizar o tempo quando eu fiz as funções de rand
#include <cstdlib>//biblioteca padrao do c, ai tem funcoes como o rand
#include <sstream>// deixa ler uma string como se fosse um arquivo, fluxo de string, funcao split
#include <limits> //limpar buffer de entrada com isso em especifico cin.ignore(numeric_limits<streamsize>::max(), '\n');
#include <cctype> // Para a função toupper

using namespace std;

// Função auxiliar para dividir strings, usada no carregamento do save
static vector<string> split(const string& s, char delimiter) {
    vector<string> pedacos;
    string pedaco;
    istringstream pedacoStream(s);
    while (getline(pedacoStream, pedaco, delimiter)) {
        pedacos.push_back(pedaco);
    }
    return pedacos;
}

Jogo::Jogo() : jogador(nullptr), numeroCenaAtual(0) {
    srand(time(nullptr));
}

Jogo::~Jogo() {
    delete jogador;
}

void Jogo::iniciar() {
    telaDeAbertura();
}

void Jogo::telaDeAbertura() {
    int escolha = 0;
    while (escolha != 4) {
        cout << "\n==============================" << endl;
        cout << "     JURAMENTO DO EXILADO     " << endl;
        cout << "==============================" << endl;
        cout << "1. Novo Jogo" << endl;
        cout << "2. Carregar Jogo Salvo" << endl;
        cout << "3. Creditos" << endl;
        cout << "4. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> escolha;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            escolha = 0;
        }

        switch (escolha) {
        case 1: {
            int slot = escolherSlot();
            criarNovoJogo(slot);
            break;
        }
        case 2: {
            int slot = escolherSlot();
            carregarJogoSalvo(slot);
            break;
        }
        case 3:
            exibirCreditos();
            break;
        case 4:
            cout << "Saindo do jogo. Ate a proxima!" << endl;
            break;
        default:
            cout << "Opcao invalida. Tente novamente." << endl;
        }
    }
}

void Jogo::criarNovoJogo(int slot) {
    cout << "\n -- Criando um Novo Jogo -- \n" << endl;
    jogador = new Personagem();
    telaDeInventario(true);

    cout << "\nVoce recebe um equipamento basico para a sua jornada." << endl;
    Item espadaInicial("Laminas do caos", 'w', true, 1, 2);
    jogador->adicionarItem(espadaInicial);
    jogador->equiparArma(jogador->getInventario().size() - 1);//pega o indice do ultimo item adicionado ao inventario e equipa ele

    jogador->mostrarInventario();
    cout << "Pressione Enter para iniciar sua aventura...";
    cin.ignore(1000, '\n');
    cin.get();
    
    numeroCenaAtual = 1;
    cenasVisitadas.clear();
    cenasVisitadas.push_back(numeroCenaAtual);

    telaPrincipalDoJogo(slot);
}

void Jogo::carregarJogoSalvo(int slot) {
    cout << "\n -- Carregando Jogo Salvo -- \n" << endl;
    if (carregar(slot)) {
        cout << "Jogo carregado com sucesso!" << endl;
        telaDeInventario(false);
        telaPrincipalDoJogo(slot);
    }
    else {
        cout << "Nenhum jogo salvo encontrado no slot " << slot << "." << endl;
    }
}

void Jogo::exibirCreditos() {
    cout << "\n -- Creditos -- \n" << endl;
    cout << "Desenvolvido por:" << endl;
    cout << "Athos Nunes Kolling" << endl;
    cout << "Gustavo Sbardelotto Rezende" << endl;
    cout << "Obrigado por jogar!" << endl;
}

void Jogo::telaDeInventario(bool criandoPersonagem) {
    if (criandoPersonagem) {

        string nomeDoHeroi;
        cout << "\n--- Criacao de Personagem ---" << endl;
        cout << "Primeiro, digite o nome do seu heroi: ";
        cin.ignore(1000, '\n');
        getline(cin, nomeDoHeroi);

        cout << "\n--- Criacao de Personagem ---" << endl;
        cout << "Como deseja criar seu personagem?" << endl;
        cout << "1. Distribuir Pontos (Recomendado)" << endl;
        cout << "2. Geracao Aleatoria (Rapido)" << endl;
        cout << "Escolha o modo: ";

        int modo;
        cin >> modo;

        int habilidade = 6, energia = 12, sorte = 6;

        if (modo == 2) { // MODO ALEATÓRIO
            cout << "Gerando personagem aleatoriamente..." << endl;
            int pontosParaDistribuir = 12;
            while (pontosParaDistribuir > 0) {
                int atributo = rand() % 3;
                if (atributo == 0 && habilidade < 12) habilidade++;
                else if (atributo == 1 && energia < 24) energia++;
                else if (atributo == 2 && sorte < 12) sorte++;
                else continue;
                pontosParaDistribuir--;
            }
        }
        else { // MODO PADRÃO - DISTRIBUIR PONTOS
            int pontosParaDistribuir = 12;
            while (pontosParaDistribuir > 0) {
                system("cls || clear");
                cout << "\nVoce tem " << pontosParaDistribuir << " pontos restantes." << endl;
                cout << "Atributos Atuais:" << endl;
                cout << "1. HABILIDADE: " << habilidade << " (Max: 12)" << endl;
                cout << "2. ENERGIA:    " << energia << " (Max: 24)" << endl;
                cout << "3. SORTE:      " << sorte << " (Max: 12)" << endl;

                cout << "\nEm qual atributo voce quer adicionar pontos? (1, 2 ou 3): ";
                int escolhaAtributo;
                cin >> escolhaAtributo;

                if (cin.fail() || escolhaAtributo < 1 || escolhaAtributo > 3) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Opcao invalida. Tente novamente." << endl;
                    continue;
                }

                cout << "Quantos pontos voce deseja adicionar? ";
                int pontosAdicionar;
                cin >> pontosAdicionar;

                if (cin.fail() || pontosAdicionar <= 0) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Voce deve adicionar um numero positivo de pontos." << endl;
                    continue;
                }

                if (pontosAdicionar > pontosParaDistribuir) {
                    cout << "Voce nao tem pontos suficientes!" << endl;
                    continue;
                }

                switch (escolhaAtributo) {
                case 1: // Habilidade
                    if (habilidade + pontosAdicionar > 12) {
                        cout << "Nao e possivel ultrapassar o valor maximo de 12 para HABILIDADE." << endl;
                    }
                    else {
                        habilidade += pontosAdicionar;
                        pontosParaDistribuir -= pontosAdicionar;
                    }
                    break;
                case 2: // Energia
                    if (energia + pontosAdicionar > 24) {
                        cout << "Nao e possivel ultrapassar o valor maximo de 24 para ENERGIA." << endl;
                    }
                    else {
                        energia += pontosAdicionar;
                        pontosParaDistribuir -= pontosAdicionar;
                    }
                    break;
                case 3: // Sorte
                    if (sorte + pontosAdicionar > 12) {
                        cout << "Nao e possivel ultrapassar o valor maximo de 12 para SORTE." << endl;
                    }
                    else {
                        sorte += pontosAdicionar;
                        pontosParaDistribuir -= pontosAdicionar;
                    }
                    break;
                }
            }
        }

        delete jogador;
        jogador = new Personagem(nomeDoHeroi, habilidade, energia, sorte);
        cout << "\n--- Personagem Criado! ---" << endl;
    }

    cout << "Pressione Enter para continuar...";
    cin.ignore(1000, '\n');
    cin.get();
}

void Jogo::telaPrincipalDoJogo(int slot) {//versao arrumada
    bool jogoAtivo = true;
    while (jogoAtivo && jogador->estaVivo()) {
        salvarProgresso(slot);

        if (!cenaAtual.carregar(numeroCenaAtual)) {
            cout << "Fim da Aventura! Obrigado por jogar." << endl;
            jogoAtivo = false;
            continue;
        }

        Item* itemDaCena = cenaAtual.getItem();
        if (itemDaCena) {
            cout << "\nVoce encontrou: " << itemDaCena->getNome() << endl;
            jogador->adicionarItem(*itemDaCena);
        }

        if (cenaAtual.isCenaDeCombate()) {
            Batalha batalha(jogador, cenaAtual.getInimigo());
            bool vitoria = batalha.executar();
            if (vitoria) {
                int tesouro = cenaAtual.getInimigo()->getTesouro();
				int provisoes = cenaAtual.getInimigo()->getProvisoes();

                // Adicionar provisões se houver
                Item* itemDrop = cenaAtual.getInimigo()->getItemDrop();
				jogador->adicionarTesouro(tesouro);
				jogador->adicionarProvisao(provisoes); 
                if (itemDrop) {
                    jogador->adicionarItem(*itemDrop);
                }

				cout << "Voce recuperou " << tesouro << " de tesouro e " << provisoes << " provisao(oes)." << endl;
                numeroCenaAtual = cenaAtual.getCenaVitoria();
            }
            else {
                if (!jogador->estaVivo()) {
                    jogoAtivo = false;
                }
                numeroCenaAtual = cenaAtual.getCenaDerrota();
            }
        }
        else {
			system("cls || clear");//limpa a tela antes de mostrar o texto da cena(cls para windows, clear para linux)
            cout << cenaAtual.getTexto() << endl;

            bool escolheuAcaoDaCena = false;
            while (!escolheuAcaoDaCena) {
                cout << "\n----------------------------------------" << endl;
                cout << "O que voce deseja fazer?" << endl;

                const auto& opcoes = cenaAtual.getTextoEscolhas();
                for (size_t i = 0; i < opcoes.size(); ++i) {
                    cout << i + 1 << ". " << opcoes[i] << endl;
                }

                cout << "----------------------------------------" << endl;
                cout << "[Acoes do Jogador]" << endl;
                cout << "I - Abrir Inventario (Equipar/Desequipar)" << endl;
                cout << "C - Usar Provisao (Curar)" << endl;
                cout << "----------------------------------------" << endl;

                cout << "Sua escolha: ";
                string escolhaStr;
                cin >> escolhaStr;

                try {
                    int escolhaNum = stoi(escolhaStr);
                    processarEscolha(escolhaNum);
                    escolheuAcaoDaCena = true;
                }
                catch (const invalid_argument& e) {
                    char escolhaChar = toupper(escolhaStr[0]);// esse bloco vai executar se o stoi falhou, ai da pra ter certeza que o jogador digitou uma letra
                    if (escolhaChar == 'I') {
                        abrirInventario();
                    }
                    else if (escolhaChar == 'C') {
                        jogador->usarProvisao();
                        cout << "Pressione Enter para continuar...";
						cin.ignore(1000, '\n'); //ignora até 1000 caracteres ou até nova linha do buffer, pra não dar conflito na leitura
                        cin.get();
                    }
                    else {
                        cout << "Comando invalido." << endl;
                    }
                    system("cls || clear");
                    cout << cenaAtual.getTexto() << endl;
                }
            }
        }

        if (numeroCenaAtual == 0) {
            jogoAtivo = false;
        }
    }

    if (!jogador->estaVivo()) {
        cout << "\n--- VOCE FOI DERROTADO --- \nFim de Jogo." << endl;
		exit(0);
    }
}

void Jogo::abrirInventario() {
    bool noInventario = true;
    while (noInventario) {
        jogador->mostrarInventario();
        cout << "Digite o numero do item para equipar/desequipar, ou 0 para voltar: ";
        int escolha;
        cin >> escolha;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Entrada invalida." << endl;
            continue;
        }

        if (escolha == 0) {
            noInventario = false;
        }
        else {
			int indiceEscolhido = escolha - 1;
            
            if (indiceEscolhido == jogador->getIndiceArmaEquipada()) {
                jogador->desequiparArma();
            }
            else {
                jogador->equiparArma(indiceEscolhido);
            }
        }

        if (noInventario) { // Pausa apenas se não for sair
            cout << "Pressione Enter para continuar...";
            cin.ignore(1000, '\n');
            cin.get();
        }
    }
}

void Jogo::processarEscolha(int escolha) {
	const auto& destinos = cenaAtual.getCenasDestino();//constante referencia para o vetor de destinos da cena atual, alem de nao dizer o tipo da variavel, constante definida, ou seja, nao muda em outra parte do codigo
    if (escolha > 0 && escolha <= destinos.size()) {
        numeroCenaAtual = destinos[escolha - 1];
    }
    else {
        cout << "Escolha invalida." << endl;
    }
}

int Jogo::escolherSlot() {
    int slot = 0;
    while (slot < 1 || slot > 3) {
        cout << "\nEscolha um slot de jogo (1, 2 ou 3): ";
        cin >> slot;
        if (cin.fail() || slot < 1 || slot > 3) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Opcao invalida." << endl;
            slot = 0;
        }
    }
    return slot;
}

void Jogo::salvarProgresso(int slot) {
    if (!jogador) return;
    ofstream saveFile("savegame" + to_string(slot) + ".txt");
    if (!saveFile.is_open()) return;

    saveFile << jogador->getNome() << "\n"
        << jogador->getHabilidade() << "\n"
        << jogador->getEnergia() << "\n"
        << jogador->getSorte() << "\n"
        << jogador->getTesouro() << "\n"
        << jogador->getProvisoes() << "\n";

    vector<Item> inventario = jogador->getInventario();
    saveFile << inventario.size() << "\n";
    for (auto& item : inventario) {
        saveFile << item.getNome() << ";" << item.getTipo() << ";" << item.isUsavelEmCombate() << ";" << item.getBonusForcaAtaque() << ";" << item.getBonusDano() << "\n";
    }

    saveFile << numeroCenaAtual << "\n";
    saveFile << cenasVisitadas.size() << "\n";
    for (int cena : cenasVisitadas) {
        saveFile << cena << " ";
    }
    saveFile << "\n";
    saveFile.close();
}

bool Jogo::carregar(int slot) {
    ifstream loadFile("savegame" + to_string(slot) + ".txt");
    if (!loadFile.is_open()) {
        return false;
    }

    try {
        string nome;
        int habilidade, energia, sorte, tesouro, provisoes;
        string linha;

        getline(loadFile, nome);
        getline(loadFile, linha); habilidade = stoi(linha);
        getline(loadFile, linha); energia = stoi(linha);
        getline(loadFile, linha); sorte = stoi(linha);
        getline(loadFile, linha); tesouro = stoi(linha);
        getline(loadFile, linha); provisoes = stoi(linha);

        delete jogador;
        jogador = new Personagem(nome, habilidade, energia, sorte);
        jogador->adicionarTesouro(tesouro);
        // jogador->setProvisoes(provisoes); // Garanta que Personagem.h/cpp tenha este método

        getline(loadFile, linha);
        int numItens = stoi(linha);

        for (int i = 0; i < numItens; ++i) {
            string itemLinha;
            getline(loadFile, itemLinha);
            vector<string> dadosItem = split(itemLinha, ';');
            if (dadosItem.size() == 5) {
                Item item(dadosItem[0], dadosItem[1][0], stoi(dadosItem[2]), stoi(dadosItem[3]), stoi(dadosItem[4]));
                jogador->adicionarItem(item);
            }
        }

        getline(loadFile, linha);
        this->numeroCenaAtual = stoi(linha);

        this->cenasVisitadas.clear();
        getline(loadFile, linha);
        int numCenasVisitadas = stoi(linha);

        if (numCenasVisitadas > 0) {
            getline(loadFile, linha);
            istringstream cenasStream(linha);
            int idCena;
            while (cenasStream >> idCena) {
                this->cenasVisitadas.push_back(idCena);
            }
        }

        loadFile.close();
        return true;
    }
    catch (const std::exception& e) {
        cerr << "Erro ao carregar o jogo: arquivo de save corrompido. (" << e.what() << ")" << endl;
        loadFile.close();
        return false;
    }
}
