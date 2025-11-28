#pragma once
#include "nodo.h"

template <class T> 
class Lista {
private: 
	Nodo<T>* inicio;
	Nodo<T>* fim;
	int tamanho;
public: 
	Lista();
	~Lista();
	bool inserirNaPosicao(const T& item, int posicao);
	bool removerNaPosicao(int posicao);
	T removerPrimeiro();
	void imprimir() const;
	bool vazio() const;
	int size() const;
};

#include "lista.cpp"