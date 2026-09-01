// Seccion 11, Problema 2, Caso 2: Consulta sobre bufer vacio.
#include <iostream>
#include "../codigo/Firewall.hpp"

int main() {
    Firewall fw(/*C=*/10, /*T_ms=*/1000, /*L=*/5);
    Paquete aux;

    bool ok = (fw.obtenerAceptados() == 0) &&
              (fw.obtenerBytesOcupados() == 0) &&
              (!fw.procesarDequeue(aux)); // desencolar sobre bufer vacio debe fallar controladamente

    std::cout << "P2-Caso2 (consulta sobre bufer vacio): " << (ok ? "[PASO]" : "[FALLO]") << "\n";
    return ok ? 0 : 1;
}
