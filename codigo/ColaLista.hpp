#ifndef COLA_LISTA_HPP
#define COLA_LISTA_HPP

#include <stdexcept>

template <typename T>
class ColaLista {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;
        Nodo(const T& val, Nodo* sig = nullptr) : dato(val), siguiente(sig) {}
    };

    Nodo* cabeza;
    Nodo* cola;
    int contador;

public:
    ColaLista() : cabeza(nullptr), cola(nullptr), contador(0) {}

    ~ColaLista() {
        limpiar();
    }

    bool estaVacia() const { return contador == 0; }
    int obtenerContador() const { return contador; }

    void encolar(const T& elemento) {
        Nodo* nuevo = new Nodo(elemento);
        if (estaVacia()) {
            cabeza = cola = nuevo;
        } else {
            cola->siguiente = nuevo;
            cola = nuevo;
    }
    contador++;
    }

    T desencolar() {
        if (estaVacia()) {
            throw std::underflow_error("Error: La cola está vacía.");
        }
        Nodo* temp = cabeza;
        T valor = temp->dato;
        cabeza = cabeza->siguiente;
        if (cabeza == nullptr) cola = nullptr;
        delete temp;
        contador--;
        return valor;
    }

    T obtenerFrente() const {
        if (estaVacia()) {
            throw std::underflow_error("Error: La cola está vacía.");
        }
        return cabeza->dato;
    }

    void limpiar() {
        while (!estaVacia()) {
            desencolar();
        }
    }
    
};

#endif 
