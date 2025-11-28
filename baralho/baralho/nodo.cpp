
#include "nodo.h"

template <typename T>
Nodo<T>::Nodo(T& item) {
    dado = item;
    proximo = nullptr;
    anterior = nullptr;
}