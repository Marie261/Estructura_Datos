#ifndef FIREWALL_H
#define FIREWALL_H

#include "Cola.h"
#include "Paquete.h"

class Firewall {
private:
    Cola<Paquete> buferRecepcion;
    Cola<long long> colaTimestamps;

    int capacidadMaxBytes;
    long long ventanaTiempoMs;
    int limitePaquetes;
    int bytesOcupados;

    void purgarTimestampsExpirados(long long timestampActualMs);

public:
    Firewall(int C, long long T, int L);

    EstadoPaquete procesarLlegadaPaquete(const Paquete&& paquete);

    bool procesarDequeue(Paquete& paqueteAtendido);

    int getBytesOcupados() const { return bytesOcupados; }

};

#endif