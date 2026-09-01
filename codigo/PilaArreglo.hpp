#ifndef PILA_ARREGLO_HPP
#define PILA_ARREGLO_HPP

#include <stdexcept>

template <typename T>
class PilaArreglo {
private: 
    T* arreglo;
    int capacidad;
    int tope;

    void redimensionar(int nuevaCapacidad) {
        T* nuevoArreglo = new T[nuevaCapacidad];
        for (int i = 0; i < tope; ++i) {
            nuevoArreglo[i] = arreglo[i];
        }
        delete[] arreglo;
        arreglo = nuevoArreglo;
        capacidad = nuevaCapacidad;
    }

public:
    explicit PilaArreglo(int capInicial = 10)
        : capacidad(capInicial > 0 ? capInicial : 10), tope(0) {
        arreglo = new T[capacidad];
        }
        
        ~PilaArreglo() {
            delete[] arreglo;
        }

        PilaArreglo(const PilaArreglo& otra) : capacidad(otra.capacidad), tope(otra.tope) {
            arreglo = new T[capacidad];
            for (int i = 0; i < tope; ++i){
                arreglo[i] = otra.arreglo[i];
            }
        }

        PilaArreglo& operator=(const PilaArreglo& otra) {
            if (this != &otra) {
                delete[] arreglo;
                capacidad = otra.capacidad;
                tope = otra.tope;
                arreglo = new T[capacidad];
                for (int i = 0; i < tope; ++i) {
                    arreglo[i] = otra.arreglo[i];
                }
            }
            return *this;
        }

        bool estaVacia() const { return tope == 0; }
        int obtenerTamaño() const { return tope; }
        int obtenerCapacidad() const { return capacidad; }

        void apilar(const T& elemento) {
            if (tope == capacidad) {
                redimensionar(capacidad * 2);
            }
            arreglo[tope++] = elemento;
        }

        T desapilar() {
            if (estaVacia()) {
                throw std::underflow_error("Error: La pila está vacía.");
            }
            return arreglo[--tope];
        }

        T obtenerTope() const {
            if (estaVacia()) {
                throw std::underflow_error("Error: La pila está vacía.");
            }
            return arreglo[tope - 1];
        }

        void limpiar() {
            tope = 0;
        }
};

#endif