// Seccion 11, Problema 1, Caso 7: Crecimiento de capacidad de la version de arreglo.
// PilaArreglo inicia con capacidad 10 y duplica al llenarse (politica implementada en PilaArreglo.hpp).
#include <iostream>
#include "../codigo/PilaArreglo.hpp"

int main() {
    PilaArreglo<int> p(4); // capacidad inicial pequeña para forzar varios redimensionamientos

    bool ok = true;
    int capacidadAnterior = p.obtenerCapacidad();
    ok = ok && (capacidadAnterior == 4);

    // Al apilar el 5to elemento debe duplicar: 4 -> 8
    for (int i = 0; i < 5; ++i) p.apilar(i);
    ok = ok && (p.obtenerCapacidad() == 8) && (p.obtenerTamaño() == 5);

    // Al apilar el 9no elemento debe duplicar otra vez: 8 -> 16
    for (int i = 5; i < 9; ++i) p.apilar(i);
    ok = ok && (p.obtenerCapacidad() == 16) && (p.obtenerTamaño() == 9);

    // Verifica que los datos sobreviven al redimensionamiento (no se corrompen)
    for (int i = 8; i >= 0; --i) {
        int val = p.desapilar();
        ok = ok && (val == i);
    }
    ok = ok && p.estaVacia();

    std::cout << "P1-Caso7 (crecimiento de capacidad por duplicacion): " << (ok ? "[PASO]" : "[FALLO]") << "\n";
    return ok ? 0 : 1;
}
