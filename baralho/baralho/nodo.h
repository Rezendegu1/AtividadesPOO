#pragma once
#include <iostream>

template <class T>
class Nodo {
public: 
	T dado;
	Nodo <T>* proximo;
	Nodo <T>* anterior;

	Nodo(T& item);
};