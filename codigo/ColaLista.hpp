#ifndef PAQUETHE_H
#define PAQUETHE_H

enum class EstadoPaquete {
    Aceptado,
    RechazadoPorTasa,
    RechazadoPorBuferLleno,
};

class Paquete {
    public:
    int id;
    int tamañoBytes;
    long long timestampMs;

    Paquete(int id = 0, int tamañoBytes = 0, long long timestampMs = 0)
        : id(id), tamañoBytes(tamañoBytes), timestampMs(timestampMs) {}
};

#endif 
