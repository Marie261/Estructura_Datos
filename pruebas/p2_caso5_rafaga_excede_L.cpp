// Seccion 11, Problema 2, Caso 5: Rafaga que excede L dentro de la ventana T.
// L=3, T=1000ms. Se envian 5 paquetes muy juntos en el tiempo: los 2 ultimos deben rechazarse por tasa.
#include <iostream>
#include "../codigo/Firewall.hpp"

int main() {
    Firewall fw(/*C=*/100, /*T_ms=*/1000, /*L=*/3);

    int aceptados = 0, rechazadosTasa = 0;
    for (int i = 0; i < 5; ++i) {
        EstadoPaquete r = fw.procesarLlegadaPaquete(Paquete(i, 100, i)); // timestamps 0,1,2,3,4 ms
        if (r == EstadoPaquete::Aceptado) aceptados++;
        if (r == EstadoPaquete::RechazadoPorTasa) rechazadosTasa++;
    }

    bool ok = (aceptados == 3) && (rechazadosTasa == 2) &&
              (fw.obtenerAceptados() == 3) && (fw.obtenerRechazadosTasa() == 2);

    std::cout << "P2-Caso5 (rafaga excede L dentro de T): " << (ok ? "[PASO]" : "[FALLO]") << "\n";
    return ok ? 0 : 1;
}
