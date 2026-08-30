#include "DocumentoUndoRedo.hpp"

Documento::Documento() : contenido("") {}

ResultadoOperacion Documento::ejecutarEdicion(TipoEdicion tipo, int posicion, const std::string& texto) {
    int tamanoActual = static_cast<int>(contenido.length());

    if (tipo == TipoEdicion::INSERTAR) {
        if (posicion < 0 || posicion > tamanoActual) return ResultadoOperacion::EdicionInvalida;
        
        contenido.insert(posicion, texto);
        pilaDeshacer.apilar(Operacion(tipo, posicion, "", texto));
        pilaRehacer.limpiar(); // Una nueva edición invalida el historial de rehacer
        return ResultadoOperacion::Exitoso;
    }
    else if (tipo == TipoEdicion::ELIMINAR) {
        int numBorrar = static_cast<int>(texto.length());
        if (posicion < 0 || posicion + numBorrar > tamanoActual) return ResultadoOperacion::EdicionInvalida;

        std::string borrado = contenido.substr(posicion, numBorrar);
        contenido.erase(posicion, numBorrar);
        pilaDeshacer.apilar(Operacion(tipo, posicion, borrado, ""));
        pilaRehacer.limpiar();
        return ResultadoOperacion::Exitoso;
    }
    else if (tipo == TipoEdicion::REEMPLAZAR) {
        int numReemplazar = static_cast<int>(texto.length());
        if (posicion < 0 || posicion + numReemplazar > tamanoActual) return ResultadoOperacion::EdicionInvalida;

        std::string anterior = contenido.substr(posicion, numReemplazar);
        contenido.replace(posicion, numReemplazar, texto);
        pilaDeshacer.apilar(Operacion(tipo, posicion, anterior, texto));
        pilaRehacer.limpiar();
        return ResultadoOperacion::Exitoso;
    }

    return ResultadoOperacion::EdicionInvalida;
}

ResultadoOperacion Documento::deshacer() {
    if (pilaDeshacer.estaVacia()) return ResultadoOperacion::NoOpPilaVacia;

    Operacion op = pilaDeshacer.desapilar();

    if (op.tipo == TipoEdicion::INSERTAR) {
        contenido.erase(op.posicion, op.textoNuevo.length());
    } else if (op.tipo == TipoEdicion::ELIMINAR) {
        contenido.insert(op.posicion, op.textoAnterior);
    } else if (op.tipo == TipoEdicion::REEMPLAZAR) {
        contenido.replace(op.posicion, op.textoNuevo.length(), op.textoAnterior);
    }

    pilaRehacer.apilar(op);
    return ResultadoOperacion::Exitoso;
}

ResultadoOperacion Documento::rehacer() {
    if (pilaRehacer.estaVacia()) return ResultadoOperacion::NoOpPilaVacia;

    Operacion op = pilaRehacer.desapilar();

    if (op.tipo == TipoEdicion::INSERTAR) {
        contenido.insert(op.posicion, op.textoNuevo);
    } else if (op.tipo == TipoEdicion::ELIMINAR) {
        contenido.erase(op.posicion, op.textoAnterior.length());
    } else if (op.tipo == TipoEdicion::REEMPLAZAR) {
        contenido.replace(op.posicion, op.textoAnterior.length(), op.textoNuevo);
    }

    pilaDeshacer.apilar(op);
    return ResultadoOperacion::Exitoso;
}

void Documento::reiniciar() {
    contenido = "";
    pilaDeshacer.limpiar();
    pilaRehacer.limpiar();
}