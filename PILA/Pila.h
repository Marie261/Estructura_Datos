#ifndef PILA_H
#define PILA_H

#include <vector>
#include <stdexcept>


template <typename T>
class Pila
{
    private:
            std::vector <T> elementos;
    
    public: 

    //Agrega un elemento a la pila
    void Push(T elemento)
    {
        elementos.push_back(elemento);
    }

    //Saca el ultimo elemento de la pila
    T Pop()
    {
        if(EstaVacia())
        {
            throw std::runtime_error("La pila esta vacia.");
        }

        T elemento = elementos.back();
        elementos.pop_back();
        return elemento;
    }

    //Consulta el ultimo elemento sin sacarlo
    T Peek()
    {
        if(EstaVacia())
        {
            throw std::runtime_error("La pila esta vacia. ");
        }

        return elementos.back();
    }


    //Indica si la pila esta vacia
    bool EstaVacia()
    {
        return elementos.empty();
    }

    //Indica CUntoa elementos hay
    std::size_t Tamaño()
    {
        return elementos.size();
    }

    //Vacia completamente la pila
    void Limpiar()
    {
        elementos.clear();
    }

};

#endif