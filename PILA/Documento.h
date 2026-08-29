#ifndef DOCUMENTO_H
#define DOCUMENTO_H

#include <string>
#include "Pila.h"
#include "Operacion.h"


class Documento
{
private:
    std::string contenido;

    Pila<Operacion> pilaDeshacer;
    Pila<Operacion> pilaRehacer;

public:
    Documento()
    {
        contenido = "";
    } 

void Escribir(std::string nuevoContenido)
{
    Operacion operacion(contenido, nuevoContenido);
    pilaDeshacer.Push(operacion);
    //Cuando se hace una nueva operacio,
    //se elimina la posibilidad de rehacer.
    pilaRehacer.Limpiar();

    contenido = nuevoContenido;
}

void Deshacer()
{
    if (pilaDeshacer.EstaVacia())
    {
        return;
    }
    
    Operacion operacion = pilaDeshacer.Pop();
    pilaRehacer.Push(operacion);
    contenido = operacion.textoAnterior;
}

void Rehacer()
{
    if (pilaRehacer.EstaVacia())
    {
        return;
    }

    Operacion operacion = pilaRehacer.Pop();
    pilaDeshacer.Push(operacion);
    contenido = operacion.textoNuevo;
}

std::string ObtenerContenido()
{
    return contenido;
}

};

#endif
