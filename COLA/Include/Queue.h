#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>

template   <typename T>
class Queue {
    private:
        struct Nodo {
            T dato;
            Nodo* siguiente;
            Nodo(const T& value) : dato(value), siguiente(nullptr) {}
        };

        Nodo* frente;
        Nodo* final;
        size_t tamañoActual;
    
    public:
        Queue() : frente(nullptr), final(nullptr), tamañoActual(0) {}
        ~Queue() { clear(); }

        void enqueue(const T& elemento) {
            Nodo* nuevo = new Nodo(elemento);
            if (isEmpty()) { 
                frente = final = nuevo; 
            } else {
                final->siguiente = nuevo;
                final = nuevo;
                tamañoActual++;
            }

            T& front() {
                if (isEmpty()) {
                    throw std::underflow_error("Cola vacía");
                    return frente->dato;
                }

                bool isEmpty() const {
                    return frente == nullptr;}
                }

                size_t size() const {
                    return tamañoActual;
                }
                void clear() {
                    while (!isEmpty()) {
                        dequeue();
                    }
                }

                
            }
}

#endif // QUEUE_H