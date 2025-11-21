#include <iostream>
#include <string>
#include <limits> 
#include "Loja.h"

using namespace std;

void adicionarNovoProduto(Loja& loja) {
	int tipo;
	cout << "--- Adicionar Novo Produto ---" << endl;
	cout << "Qual tipo de produto deseja adicionar?" << endl;
	cout << "1. Smartphone" << endl;
	cout << "2. Laptop" << endl;
	cout << "3. Tablet" << endl;
	cout << "Escolha: ";
	cin >> tipo;

	if (tipo < 1 || tipo > 3) {
		cout << "Tipo invalido." << endl;
		return;
	}
	string nome, marca, modelo;
	double preco;
	int codigo, qtd;

	cout << "Nome: ";
	cin.ignore();
	cin >> nome;

	cout << "Preco (ex: 1999.90): ";
	cin >> preco;

	cout << "Codigo de Barras (int): ";
	cin >> codigo;

	cout << "Quantidade em estoque: ";
	cin >> qtd;

	Produto* produto = nullptr;

	switch (tipo) {
	case 1: { 
		int arm;
		cout << "Modelo: ";
		cin.ignore();
		getline(cin, modelo);
		cout << "Armazenamento (em GB): ";
		cin >> arm;
		produto = new Smartphone(nome, preco, codigo, modelo, arm, qtd);
		break;
	}
	case 2: { 
		double tela;
		cout << "Marca: ";
		cin.ignore();
		getline(cin, marca);
		cout << "Tamanho da Tela (em polegadas): ";
		cin >> tela;
		produto = new Laptop(nome, preco, codigo, marca, tela, qtd);
		break;
	}
	case 3: { 
		int bat;
		cout << "Marca: ";
		cin.ignore();
		cin >> marca;
		cout << "Duracao da Bateria (em horas): ";
		cin >> bat;
		produto = new Tablet(nome, preco, codigo, marca, bat, qtd);
		break;
	}
	}

	if (produto != nullptr) {
		loja.adicionarProduto(produto);
	}
}

int main() {

	Loja minhaLoja("Loja de Eletronicos POO");
	int opcao = -1;

	do {
		cout << "\n=======================================" << endl;
		cout << " BEM-VINDO A: " << minhaLoja.getNome() << endl;
		cout << "=======================================" << endl;
		cout << "1. Buscar Produto" << endl;
		cout << "2. Listar Informacoes da Loja" << endl;
		cout << "3. Adicionar Produto no Estoque" << endl;
		cout << "4. Remover Produto do Estoque" << endl;
		cout << "5. Editar Informacoes de um Produto" << endl;
		cout << "6. Ver Valor Total do Estoque" << endl;
		cout << "7. Aplicar Desconto em um Produto" << endl;
		cout << "8. Verificar Estoque (Quantidade)" << endl;
		cout << "9. Realizar Venda (Simulado)" << endl;
		cout << "10. Listar Produtos Acima de um Valor" << endl;
		cout << "0. Sair" << endl;
		cout << "---------------------------------------" << endl;
		cout << "Digite sua opcao: ";

		cin >> opcao;

		if (cin.fail()) {
			cout << "Erro: Entrada invalida. Por favor, digite um numero." << endl;
			cin.clear(); 
			cin.ignore(1000, '\n');
			opcao = -1; 
			continue; 
		}

		switch (opcao) {
		case 1: { 
			int cod;
			cout << "Digite o codigo de barras: ";
			cin >> cod;
			minhaLoja.buscarProduto(cod);
			break;
		}
		case 2: 
			minhaLoja.listarInformacoes();
			break;
		case 3: 
			adicionarNovoProduto(minhaLoja);
			break;
		case 4: { 
			int cod;
			cout << "Digite o codigo de barras: ";
			cin >> cod;
			minhaLoja.removerProduto(cod);
			break;
		}
		case 5: { 
			int cod;
			cout << "Digite o codigo de barras: ";
			cin >> cod;
			minhaLoja.editarProduto(cod);
			break;
		}
		case 6: 
			cout << "Valor Total do Estoque: R$ " << minhaLoja.getValorTotalEstoque() << endl;
			break;
		case 7: { 
			int cod;
			double perc;
			cout << "Digite o codigo de barras: ";
			cin >> cod;
			cout << "Digite o percentual de desconto (ex: 10 para 10%): ";
			cin >> perc;
			minhaLoja.aplicarDesconto(cod, perc);
			break;
		}
		case 8: { 
			int cod;
			cout << "Digite o codigo de barras: ";
			cin >> cod;
			minhaLoja.verificarEstoque(cod);
			break;
		}
		case 9: { 
			int cod;
			cout << "Digite o codigo de barras do produto a vender: ";
			cin >> cod;
			minhaLoja.realizarVenda(cod);
			break;
		}
		case 10: { 
			double val;
			cout << "Listar produtos com preco acima de: R$ ";
			cin >> val;
			minhaLoja.listarProdutosAcimaDe(val);
			break;
		}
		case 0:
			cout << "Encerrando o sistema. Obrigado!" << endl;
			break;
		default:
			cout << "Opcao invalida. Tente novamente." << endl;
			break;
		}

	} while (opcao != 0);

	return 0; 
}