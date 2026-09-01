// Seccion 11, Problema 2, Caso 4: Bufer exactamente lleno + un paquete adicional.
// C=5 paquetes de capacidad; L y T se dejan holgados para que la tasa no interfiera.
#include <iostream>
#include "../codigo/Firewall.hpp"

int main() {
    Firewall fw(/*C=*/5, /*T_ms=*/100000, /*L=*/1000);

    bool ok = true;
    for (int i = 0; i < 5; ++i) {
        EstadoPaquete r = fw.procesarLlegadaPaquete(Paquete(i, 100, i));
        ok = ok && (r == EstadoPaquete::Aceptado);
    }
    // El bufer ya esta exactamente lleno (5/5). El siguiente debe rechazarse.
    EstadoPaquete rExtra = fw.procesarLlegadaPaquete(Paquete(99, 100, 5));
    ok = ok && (rExtra == EstadoPaquete::RechazadoPorBufferLleno) &&
               (fw.obtenerAceptados() == 5) &&
               (fw.obtenerRechazadosBuffer() == 1);

    std::cout << "P2-Caso4 (bufer exactamente lleno + 1 adicional): " << (ok ? "[PASO]" : "[FALLO]") << "\n";
    return ok ? 0 : 1;
}
