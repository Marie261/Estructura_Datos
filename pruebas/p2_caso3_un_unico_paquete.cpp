// Seccion 11, Problema 2, Caso 3: Un unico paquete.
#include <iostream>
#include "../codigo/Firewall.hpp"

int main() {
    Firewall fw(/*C=*/10, /*T_ms=*/1000, /*L=*/5);

    EstadoPaquete r = fw.procesarLlegadaPaquete(Paquete(1, 512, 0));
    bool tras_llegada = (r == EstadoPaquete::Aceptado) &&
                         (fw.obtenerAceptados() == 1) &&
                         (fw.obtenerBytesOcupados() == 512);

    Paquete atendido;
    bool desencolado = fw.procesarDequeue(atendido);
    bool tras_dequeue = desencolado && (atendido.id == 1) && (fw.obtenerBytesOcupados() == 0);

    bool ok = tras_llegada && tras_dequeue;
    std::cout << "P2-Caso3 (un unico paquete): " << (ok ? "[PASO]" : "[FALLO]") << "\n";
    return ok ? 0 : 1;
}
