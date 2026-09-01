#ifndef COLA_CIRCULAR_HPP
#define COLA_CIRCULAR_HPP

#include <stdexcept>

template <typename T>
class ColaCircular {
private: 
    T* arreglo;
    int capacidad;
    int frente;
    int finalCola;
    int contador;

public:
    explicit ColaCircular(int cap = 1000)
        : capacidad(cap > 0 ? cap: 1000), frente(0), finalCola(0), contador(0) {
        arreglo = new T[capacidad];
        }

        ~ColaCircular() {
            delete[] arreglo;
        }

        ColaCircular(const ColaCircular& otra)
            : capacidad(otra.capacidad), frente(otra.frente), finalCola(otra.finalCola), contador(otra.contador) {
            arreglo = new T[capacidad];
            for (int i = 0; i < capacidad; ++i) {
                arreglo[i] = otra.arreglo[i];
            }
        }

        ColaCircular& operator=(const ColaCircular& otra) {
            if (this != &otra) {
                delete[] arreglo;
                capacidad = otra.capacidad;
                frente = otra.frente;
                finalCola = otra.finalCola;
                contador = otra.contador;
                arreglo = new T[capacidad];
                for (int i = 0; i < capacidad; ++i) {
                    arreglo[i] = otra.arreglo[i];
                }
            }
            return *this;
        }

        bool estaVacia() const { return contador == 0; }
        bool estaLlena() const { return contador == capacidad; }
        int obtenerContador() const { return contador; }

        void encolar(const T& elemento) {
            if (estaLlena()) {
                throw std::overflow_error("Error: La cola está llena.");
            }
            arreglo[finalCola] = elemento;
            finalCola = (finalCola + 1) % capacidad;
            contador++;
        }

        T desencolar() {
            if (estaVacia()) {
                throw std::underflow_error("Error: La cola está vacía.");
            }
            T elemento = arreglo[frente];
            frente = (frente + 1) % capacidad;
            contador--;
            return elemento;
        }

        T obtenerFrente() const {
            if (estaVacia()) {
                throw std::underflow_error("Error: La cola está vacía.");
            }
            return arreglo[frente];
        }

        void limpiar() {
            frente = 0;
            finalCola = 0;
            contador = 0;
        }
       
};

#endif