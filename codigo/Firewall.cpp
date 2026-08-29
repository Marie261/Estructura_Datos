#include "Firewall.h"

Firewall::Firewall(int C, long long T, int L)
    : capacidadMaxBytes(C), ventanaTiempoMs(T), limitePaquetes(L), bytesOcupados(0) {
}

void Firewall::purgarTimestampsExpirados(long long timestampActualMs) {
    while (!colaTimestamps.isEmpty() && (timestampActualMs - colaTimestamps.peek() > ventanaTiempoMs)) {
        colaTimestamps.dequeue();
    }
}  

EstadoPaquete Firewall::procesarLlegadaPaquete(const Paquete&& paquete) {
    purgarTimestampsExpirados(paquete.timestampMs);
    
    if (colaTimestamps.count() >= limitePaquetes) {
        return EstadoPaquete::RechazadoPorTasa;
    }

    if (bytesOcupados + paquete.tamañoBytes > capacidadMaxBytes) {
        return EstadoPaquete::RechazadoPorBuferLleno;
    }

    buferRecepcion.enqueue(paquete);
    colaTimestamps.enqueue(paquete.timestampMs);
    bytesOcupados += paquete.tamañoBytes;

    return EstadoPaquete::Aceptado;
}    

