#ifndef FIREWALL_H
#define FIREWALL_H

#include "Queue.h"
#include <string>

struct Paquete
{
    int id;
    int size;  // Tamaño del paquete en bytes
    double timestamp;  // Marca de tiempo del paquete
};

enum class CriterioCapacidad { POR_PAQUETE, POR_BYTES };

class Firewall {
    private:
        Queue<Paquete> bufferRecepcion;
        Queue<double> colaTimestamps;
        size_t capacidadMaximaC;
        double ventanaTiempoT;
        int limiteTasaL;
        size_t bytesActualesBuffer;
        CriterioCapacidad modoCapacidad;

    public:
        Firewall(size_t capacidad, double ventanaT, int limiteL, CriterioCapacidad modo = CriterioCapacidad::POR_PAQUETES);
        void purgarTimestamps(double timestampActual);
        bool procesarPaquete(const Paquete& pkg, std::string& razonRechazo);
        bool desencolarBuffer(Paquete& pkgProcesado);
        size_t getOcupacionBuffer() const;
    };

#endif // FIREWALL_H