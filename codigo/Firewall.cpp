#include "Firewall.hpp"

Firewall::Firewall(int C, long long T_ms, int L_limite)
    : bufferRecepcion(C),                 // capacidad real del arreglo circular = C
      colaTimestamps(L_limite + 1),       // nunca supera L_limite tras cada insercion (ver logica abajo)
      ventanaTiempoMs(T_ms),
      limitePaquetes(L_limite),
      bytesOcupados(0),
      aceptados(0),
      rechazadosTasa(0),
      rechazadosBuffer(0),
      maximoBytesAlcanzados(0),
      maximaOcupacionPaquetes(0) {}


void Firewall::purgarTimestampsExpirados(long long timestampActualMs) {
    while (!colaTimestamps.estaVacia() && (timestampActualMs - colaTimestamps.obtenerFrente() > ventanaTiempoMs)) {
        colaTimestamps.desencolar();
    }
}  

EstadoPaquete Firewall::procesarLlegadaPaquete(const Paquete& paquete) {
    purgarTimestampsExpirados(paquete.timestampMs);
    
    if (colaTimestamps.obtenerContador() >= limitePaquetes) {
        rechazadosTasa++;
        return EstadoPaquete::RechazadoPorTasa;
    }

    if (bufferRecepcion.estaLlena()) {
        rechazadosBuffer++;
        return EstadoPaquete::RechazadoPorBufferLleno;
    }

    bufferRecepcion.encolar(paquete);
    colaTimestamps.encolar(paquete.timestampMs);
    bytesOcupados += paquete.tamañoBytes;

    if (bytesOcupados > maximoBytesAlcanzados) {
        maximoBytesAlcanzados = bytesOcupados;
    }
    if (bufferRecepcion.obtenerContador() > maximaOcupacionPaquetes) {
        maximaOcupacionPaquetes = bufferRecepcion.obtenerContador();
    }

    aceptados++;
    return EstadoPaquete::Aceptado;
}

bool Firewall::procesarDequeue(Paquete& paqueteAtendido) {
    if (bufferRecepcion.estaVacia()) {
        return false;
    }

    paqueteAtendido = bufferRecepcion.desencolar();
    bytesOcupados -= paqueteAtendido.tamañoBytes;
    if (bytesOcupados < 0) bytesOcupados = 0;

    return true;
}

void Firewall::reiniciar() {
    bufferRecepcion.limpiar();
    colaTimestamps.limpiar();
    bytesOcupados = 0;
    aceptados = 0;
    rechazadosTasa = 0;
    rechazadosBuffer = 0;
    maximoBytesAlcanzados = 0;
}

