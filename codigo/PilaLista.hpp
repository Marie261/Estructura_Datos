#ifndef OPERACION_H
#define OPERACION_H

#include <string>


class Operacion
{
public:
   std::string textoAnterior;
   std::string textoNuevo;


    Operacion(std::string anterior, std::string nuevo)
    {  
    textoAnterior = anterior;
    textoNuevo = nuevo;
    }
};

#endif