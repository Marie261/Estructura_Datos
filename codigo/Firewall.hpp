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

    int capacidadMaxBytes;
    long long ventanaTiempoMs;
    int limitePaquetes;
    int bytesOcupados;

    int aceptados;
    int rechazadosTasa;
    int rechazadosBuffer;
    int maximoBytesAlcanzados;

public: 
    Firewall(int C_bytes, long long T_ms, int L_limite);

    void purgarTimestampsExpirados(long long timestampActualMs);
    EstadoPaquete procesarLlegadaPaquete(const Paquete& paquete);
    bool procesarDequeue(Paquete& paqueteAtendido);

    int obtenerBytesOcupados() const { return bytesOcupados; }
    int obtenerMaximosBytes() const { return maximoBytesAlcanzados; }
    int obtenerAceptados() const { return aceptados; }
    int obtenerRechazadosTasa() const { return rechazadosTasa; }
    int obtenerRechazadosBuffer() const { return rechazadosBuffer; }

    void reiniciar();
};

#endif