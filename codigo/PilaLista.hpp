#ifndef PILA_LISTA_HPP
#define PILA_LISTA_HPP

#include <stdexcept>

template <typename T>
class PilaLista {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;
        Nodo(const T& val, Nodo* sig = nullptr) : dato(val), siguiente(sig) {}
    };

    Nodo* cabeza;
    int contador;

public:
    PilaLista() : cabeza(nullptr), contador(0) {}

    ~PilaLista() {
        limpiar();
    }

    bool estaVacia() const { return cabeza == nullptr; }
    int obtenerTamano() const { return contador; }

    void apilar(const T& elemento) {
        cabeza = new Nodo(elemento, cabeza);
        contador++;
    }

    T desapilar() {
        if (estaVacia()) {
            throw std::underflow_error("Error: La pila esta vacia.");
        }
        Nodo* temp = cabeza;
        T valor = temp->dato;
        cabeza = cabeza->siguiente;
        delete temp;
        contador--;
        return valor;
    }

    T obtenerTope() const {
        if (estaVacia()) {
            throw std::underflow_error("Error: La pila esta vacia.");
        }
        return cabeza->dato;
    }

    void limpiar() {
        while (!estaVacia()) {
            desapilar();
        }
    }
};

#endif