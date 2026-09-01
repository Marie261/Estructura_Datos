#ifndef FIREWALL_HPP
#define FIREWALL_HPP

#include "ColaCircular.hpp"

enum class EstadoPaquete {
    Aceptado,
    RechazadoPorTasa,
    RechazadoPorBufferLleno,
};

struct Paquete {
    int id;
    int tamañoBytes;
    long long timestampMs;

    Paquete(int i = 0, int tam = 0, long long ts = 0)
        : id(i), tamañoBytes(tam), timestampMs(ts) {}
};

class Firewall {
private:
    ColaCircular<Paquete> bufferRecepcion;
    ColaCircular<long long> colaTimestamps;

    long long ventanaTiempoMs;
    int limitePaquetes;
    int bytesOcupados;          // estadistica informativa, no decide aceptacion

    int aceptados;
    int rechazadosTasa;
    int rechazadosBuffer;
    int maximoBytesAlcanzados;
    int maximaOcupacionPaquetes;

public: 
    // C = capacidad fija del bufer en NUMERO DE PAQUETES (tamaño real del arreglo circular)
    Firewall(int C, long long T_ms, int L_limite);

    void purgarTimestampsExpirados(long long timestampActualMs);
    EstadoPaquete procesarLlegadaPaquete(const Paquete& paquete);
    bool procesarDequeue(Paquete& paqueteAtendido);

    int obtenerBytesOcupados() const { return bytesOcupados; }
    int obtenerMaximosBytes() const { return maximoBytesAlcanzados; }
    int obtenerMaximaOcupacionPaquetes() const { return maximaOcupacionPaquetes; }
    int obtenerAceptados() const { return aceptados; }
    int obtenerRechazadosTasa() const { return rechazadosTasa; }
    int obtenerRechazadosBuffer() const { return rechazadosBuffer; }

    void reiniciar();
};

#endif