static vector<string> split(const string & s, char separador) { //static faz com
    istringstream pedacoStream(s); //istringstream lê dados de uma string como se fosse um arquivo
    //ou seja, a string s é tratada como um arquivo, e o pedacoStream é o "arquivo" que lê essa string
    while (getline(pedacoStream, pedaco, separador)) { //esse while diz que enquanto o getline conseguir ler um pedaco, continua a executar o que ta dentro da {}
        //o getline é o que da a ordem para a "maquina de leitura", cada vez que ele é chamado, ele faz:
        pedacos.push_back(pedaco);                     //o getline é o que da a ordem para a "maquina de leitura", cada vez que ele é chamado, ele faz:
    }                                                  //1. Comeca a ler do ponto onde o "cursor" da pedacoStream parou.
    return pedacos;                                    //2.Continua a ler caractere por caractere ate encontrar o ';'.
    //3.Pega em tudo o que leu antes do separador e guarda na variavel pedaco.
    @ - 93, 32 + 93, 32 @@
        // Linha de HABILIDADE do monstro [cite: 122, 136]
        else if (lendoMonstro && linha.rfind("H:", 0) == 0) {
            // Supondo que voc� crie um m�todo setHabilidade em Monstro
            // inimigo->setHabilidade(stoi(linha.substr(2)));
            inimigo->setHabilidade(stoi(linha.substr(2)));
        }
        // Linha de ENERGIA do monstro [cite: 124, 138]
        else if (lendoMonstro && linha.rfind("E:", 0) == 0) {
            // Supondo que voc� crie um m�todo setEnergia em Monstro
            // inimigo->setEnergia(stoi(linha.substr(2)));
            inimigo->setEnergia(stoi(linha.substr(2)));
        }
        // Linha de VIT�RIA/DERROTA (ex: "12:13") [cite: 128, 142]
        else if (lendoMonstro && linha.find(':') != string::npos) {
            size_t posDoisPontos = linha.find(':');
            this->cenaVitoria = stoi(linha.substr(0, posDoisPontos));
            this->cenaDerrota = stoi(linha.substr(posDoisPontos + 1));
        }
        // Se n�o for nenhuma das anteriores, � texto da hist�ria
        else {
            textoPrincipal += linha + "\n";
        }
}

arquivo.close();
return true;
}

// --- M�TODOS GETTER ---

string Cena::getTexto() {
    return this->textoPrincipal;
}


    }

    arquivo.close();
    return true;
}

// --- M�TODOS GETTER ---

string Cena::getTexto() {
    return this->textoPrincipal;
}