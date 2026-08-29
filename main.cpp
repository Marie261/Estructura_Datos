#include <iostream>
#include <exception>

#include "PILA/Pila.h"
#include "PILA/Operacion.h"
#include "PILA/Documento.h"


void ProbarPila()
{
    Pila<int> pila;
    int opcion;

    do
    {
        std::cout << "\n=========================\n";
        std::cout << "          PILA\n";
        std::cout << "=========================\n";
        std::cout << "1. Push\n";
        std::cout << "2. Pop\n";
        std::cout << "3. Peek\n";
        std::cout << "4. Mostrar tamano\n";
        std::cout << "5. Verificar si esta vacia\n";
        std::cout << "6. Limpiar\n";
        std::cout << "0. Volver\n";
        std::cout << "Seleccione una opcion: ";

        std::cin >> opcion;


        try
        {
            if (opcion == 1)
            {
                int numero;

                std::cout << "Ingrese un numero: ";
                std::cin >> numero;

                pila.Push(numero);

                std::cout << "Elemento agregado correctamente.\n";
            }
            else if (opcion == 2)
            {
                std::cout << " Elemento eliminado"
                    <<pila.Pop() 
                    << std::endl;
            }
            else if (opcion == 3)
            {
                std::cout << " Elemento superior"
                    <<pila.Peek() 
                    << std::endl;
            }
            else if (opcion == 4)
            {
                std::cout << "Tamaño de la pila: "
                    <<pila.Tamaño() 
                    << std::endl;
            }
            else if (opcion == 5)
            {
                if (pila.EstaVacia())                
                std::cout << "La pila esta vacia.\n";
                else
                std::cout << "La pila tiene elementos.\n";
            }                                    
            else if (opcion == 6)
            {
                pila.Limpiar();
                std::cout << "Pila limpiada correctamente.\n";

            }
            else if (opcion != 0)
            {
                std::cout << "Opcion no valida,\n";
            }
        }  
        catch(const std::exception& e)
        {
            std::cout << "Error: " << e.what() 
            << std::endl;
        }
            
        
    } 
    while (opcion != 0);    
}

int main()
{
    ProbarPila();

    return 0;
}

