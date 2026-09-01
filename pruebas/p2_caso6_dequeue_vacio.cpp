// Seccion 11, Problema 2, Caso 6: Dequeue sobre bufer vacio.
// Se vacia el bufer con dequeues legitimos y luego se intenta uno de mas: debe fallar controladamente.
#include <iostream>
#include "../codigo/Firewall.hpp"

int main() {
    Firewall fw(/*C=*/10, /*T_ms=*/1000, /*L=*/50);
    fw.procesarLlegadaPaquete(Paquete(1, 100, 0));
    fw.procesarLlegadaPaquete(Paquete(2, 100, 1));

    Paquete aux;
    bool d1 = fw.procesarDequeue(aux); // ok
    bool d2 = fw.procesarDequeue(aux); // ok, bufer queda vacio
    bool d3 = fw.procesarDequeue(aux); // debe fallar (bufer vacio), no debe abortar

    bool ok = d1 && d2 && (!d3);
    std::cout << "P2-Caso6 (dequeue sobre bufer vacio): " << (ok ? "[PASO]" : "[FALLO]") << "\n";
    return ok ? 0 : 1;
}
