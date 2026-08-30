#ifndef DOCUMENTO_UNDO_REDO_HPP
#define DOCUMENTO_UNDO_REDO_HPP

#include <string>
#include "PilaArreglo.hpp"

enum class TipoEdicion {
    INSERTAR,
    ELIMINAR,
    REEMPLAZAR
};

enum class ResultadoOperacion {
    Exitoso,
    NoOpPilaVacia,
    EdicionInvalida
};

struct Operacion {
    TipoEdicion tipo;
    int posicion;
    std::string textoAnterior;
    std::string textoNuevo;

    Operacion() 
        : tipo(TipoEdicion::INSERTAR), posicion(0), textoAnterior(""), textoNuevo("") {}
    Operacion(TipoEdicion t, int pos, std::string ant, std::string nuev) 
        : tipo(t), posicion(pos), textoAnterior(ant), textoNuevo(nuev) {}
};

class Documento {
private:
    std::string contenido;
    PilaArreglo<Operacion> pilaDeshacer;
    PilaArreglo<Operacion> pilaRehacer;

public:
    Documento();

    ResultadoOperacion ejecutarEdicion(TipoEdicion tipo, int posicion, const std::string& texto);
    ResultadoOperacion deshacer();
    ResultadoOperacion rehacer();

    std::string obtenerContenido() const { return contenido; }
    int obtenerTamañoDeshacer() const { return pilaDeshacer.obtenerTamaño(); }
    int obtenerTamañoRehacer() const { return pilaRehacer.obtenerTamaño(); }
    void reiniciar();
};

#endif
