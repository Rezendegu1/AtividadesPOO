#include "Loja.h"
#include <iostream>
#include "Smartphone.h"
#include "Laptop.h"
#include "Tablet.h"

Loja::Loja(string nome) {
	this->nome = nome;
	this->numProdutos = 0;

	for (int i = 0; i < MAX_ESTOQUE; i++) {
		this->estoque[i] = nullptr;
	}
}

Loja::~Loja() {
	for (int i = 0; i < numProdutos; i++) {
		delete estoque[i];
	}
}

int Loja::buscarIndicePeloCodigo(int codigoDeBarras) const {
	for (int i = 0; i < numProdutos; i++) {
		if(estoque[i]->getCodigoDeBarras() == codigoDeBarras) {
			return i;
		}
	}
	return -1;
}

void Loja::buscarProduto(int codigoDeBarras) {
	int indice = buscarIndicePeloCodigo(codigoDeBarras); 
	if (indice != -1) {
		estoque[indice]->imprimirDados(); 
	}
	else {
		cout << "Produto nao encontrado. " << endl; 
	}
}
int Loja::getQuantidadeTotalItens() const {
	int total = 0;
	for (int i = 0; i < numProdutos; i++) {
		total += estoque[i]->getQuantidade();
	}
	return total;
}

void Loja::listarInformacoes() const {
	cout << "Loja: " << nome << endl;
	cout << "Tipos de produtos: " << numProdutos << " produtos" << endl;
	cout << "Quantidade total de produtos no estoque: " << getQuantidadeTotalItens() << endl;
	cout << "---Lista de produtos---" << endl;
	for (int i = 0; i < numProdutos; i++) {
		estoque[i]->imprimirDados(); 
	}
}

void Loja::adicionarProduto(Produto* novoProduto) {
	if (numProdutos >= MAX_ESTOQUE) {
		cout << "Estoque cheio. Nao e possivel adicionar mais produtos. " << endl;
		delete novoProduto;
		return;
	}
	if (buscarIndicePeloCodigo(novoProduto->getCodigoDeBarras()) != -1) {
		cout << "Produto com esse codigo de barras ja existe. " << endl;
		delete novoProduto;
	}
	else {
		estoque[numProdutos] = novoProduto;
		numProdutos++; 
		cout << "Produto " << novoProduto->getNome() << " adicionado ao estoque. " << endl;
	}
}

void Loja::editarProduto(int codigoDeBarras) {
	int indice = buscarIndicePeloCodigo(codigoDeBarras);
	if (indice == -1) {
		cout << "Produto nao encontrado. " << endl;
		return;
	}

	Produto* produto = estoque[indice];
	cout << "Editando produto: " << produto->getNome() << endl;

	string novoNome;
	double novoPreco;
	cout << "Novo nome (atual: " << produto->getNome() << "): ";
	getline(cin >> ws, novoNome);
	produto->setNome(novoNome);

	cout << "Novo preco (atual: " << produto->getPreco() << "): ";
	cin >> novoPreco;
	produto->setPreco(novoPreco);

	if (Smartphone* smartphone = dynamic_cast<Smartphone*>(produto)) {
		string modelo; 
		int armazenamento;
		cout << "Novo modelo (atual: " << smartphone->getModelo() << "): "; 
		cin.ignore();
		getline(cin, modelo);
		smartphone->setModelo(modelo);
		cout << "Novo armazenamento (atual: " << smartphone->getArmazenamento() << "): ";
		cin >> armazenamento;
		smartphone->setArmazenamento(armazenamento);
	}
	else if (Laptop* laptop = dynamic_cast<Laptop*>(produto)) {
		string marca;
		double tela;
		cout << "Nova marca (atual: " << laptop->getMarca() << "): ";
		cin.ignore();
		getline(cin, marca);
		laptop->setMarca(marca);
		cout << "Novo tamanho de tela (atual: " << laptop->getTamanhoTela() << "\"): ";
		cin >> tela;
		laptop->setTamanhoTela(tela);
	}
	else if (Tablet* tablet = dynamic_cast<Tablet*>(produto)) {
		string marca;
		int bat;
		cout << "Nova marca (atual: " << tablet->getMarca() << "): ";
		cin.ignore();
		getline(cin, marca);
		tablet->setMarca(marca);
		cout << "Nova duracao de bateria (atual: " << tablet->getDuracaoBateria() << "h): ";
		cin >> bat;
		tablet->setDuracaoBateria(bat);
	}

	cout << "Produto atualizado com sucesso. " << endl;
}

double Loja::getValorTotalEstoque() const {
	double total = 0.0; 
	for (int i = 0; i < numProdutos; i++) {
		total += (estoque[i]->getPreco() * estoque[i]->getQuantidade());
	}
	return total;
}

void Loja::aplicarDesconto(int codigoDeBarras, double percentual) {
	int indice = buscarIndicePeloCodigo(codigoDeBarras); 
	if (indice != -1) {
		Produto* produto = estoque[indice]; 
		double precoOriginal = produto->getPreco();
		double valorDesconto = precoOriginal * (percentual / 100.0);
		produto->setPreco(precoOriginal - valorDesconto); 
		cout << "Desconto aplicado. Novo preco: R$ " << produto->getPreco() << endl; 
	}
	else {
		cout << "Produto nao encontrado. " << endl;
	}
}

void Loja::verificarEstoque(int codigoDeBarras) const {
	int indice = buscarIndicePeloCodigo(codigoDeBarras); 
	if (indice != -1) {
		Produto* produto = estoque[indice];
		cout << "Quantidade em estoque do produto " << produto->getNome() << ": " << produto->getQuantidade() << endl; 
	}
	else {
		cout << "Produto nao encontrado. " << endl; 
	}
}

void Loja::realizarVenda(int codigoDeBarras) {
	int indice = buscarIndicePeloCodigo(codigoDeBarras);
	if (indice == -1) {
		cout << "Produto nao encontrado. " << endl;
		return; 
	}

	Produto* produto = estoque[indice];

	if (produto->getQuantidade() > 0) {
		produto->setQuantidade(produto->getQuantidade() - 1);
		cout << "--- Venda Realizada ---" << endl;
		cout << "Produto: " << produto->getNome() << endl;
		cout << "Preco: R$ " << produto->getPreco() << endl;
		cout << "Valor Total: R$ " << produto->getPreco() << endl;
		cout << "Estoque restante: " << produto->getQuantidade() << endl;
	}
	else { 
		cout << "Erro: Produto '" << produto->getNome() << "' esta esgotado." << endl;
	}
}

void Loja::listarProdutosAcimaDe(double valor) const {
	cout << "--- Produtos com preco superior a R$ " << valor << " ---" << endl;
	int count = 0;
		for (int i = 0; i < numProdutos; ++i) {
			if (estoque[i]->getPreco() > valor) {
				estoque[i]->imprimirDados();
				count++;
			}
		}
	if (count == 0) {
		cout << "Nenhum produto encontrado acima desse valor." << endl;
	}
}

string Loja::getNome() {
	return this->nome;
}

void Loja::removerProduto(int codigoDeBarras) {
	int indice = buscarIndicePeloCodigo(codigoDeBarras);
	if (indice == -1) {
		cout << "Produto nao encontrado para remocao" << endl;
		return;
	}

	cout << "Removendo " << estoque[indice]->getNome() << " do estoque" << endl;

	delete estoque[indice];

	for (int i = indice; i < numProdutos - 1; i++) {
		estoque[i] = estoque[i + 1];
	}
	numProdutos--;
	estoque[numProdutos] = nullptr;
}


