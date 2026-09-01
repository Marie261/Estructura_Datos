// Seccion 11, Problema 2, Caso 1: Flujo normal por debajo de C y L.
// Todos los paquetes deben ser aceptados.
#include <iostream>
#include "../codigo/Firewall.hpp"

int main() {
    Firewall fw(/*C=*/100, /*T_ms=*/1000, /*L=*/50);

    bool ok = true;
    for (int i = 0; i < 10; ++i) {
        EstadoPaquete r = fw.procesarLlegadaPaquete(Paquete(i, 200, i * 10));
        ok = ok && (r == EstadoPaquete::Aceptado);
    }
    ok = ok && (fw.obtenerAceptados() == 10) &&
               (fw.obtenerRechazadosBuffer() == 0) &&
               (fw.obtenerRechazadosTasa() == 0);

    std::cout << "P2-Caso1 (flujo normal bajo C y L): " << (ok ? "[PASO]" : "[FALLO]") << "\n";
    return ok ? 0 : 1;
}
