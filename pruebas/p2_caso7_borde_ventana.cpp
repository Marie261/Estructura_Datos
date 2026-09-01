// Seccion 11, Problema 2, Caso 7: Paquete exactamente en el borde t = t0 + T.
// La implementacion actual de purgarTimestampsExpirados usa comparacion estricta:
//   se purga solo si (t_actual - t0) > T
// Por lo tanto, en t = t0 + T la diferencia es EXACTAMENTE T (no > T), y esa marca
// de tiempo NO se purga: el borde queda INCLUIDO dentro de la ventana.
// Este comportamiento debe quedar documentado y justificado en el informe (Seccion 5,
// "Casos limite a contemplar").
#include <iostream>
#include "../codigo/Firewall.hpp"

int main() {
    Firewall fw(/*C=*/100, /*T_ms=*/100, /*L=*/2);

    EstadoPaquete r0 = fw.procesarLlegadaPaquete(Paquete(0, 100, 0));      // t0 = 0
    EstadoPaquete r1 = fw.procesarLlegadaPaquete(Paquete(1, 100, 100));    // t = t0 + T (borde)
    EstadoPaquete r2 = fw.procesarLlegadaPaquete(Paquete(2, 100, 100));    // otro paquete en el borde

    bool ok = (r0 == EstadoPaquete::Aceptado) &&
              (r1 == EstadoPaquete::Aceptado) &&
              (r2 == EstadoPaquete::RechazadoPorTasa); // ya hay 2 marcas vigentes (borde incluido) == L

    std::cout << "P2-Caso7 (borde t = t0 + T, borde incluido en la ventana): "
              << (ok ? "[PASO]" : "[FALLO]") << "\n";
    return ok ? 0 : 1;
}
