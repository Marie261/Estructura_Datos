// Seccion 11, Problema 1, Caso 1: Secuencia normal mixta.
// Combina INSERT, DELETE, UNDO y REDO en un orden tipico de uso real.
#include <iostream>
#include "../codigo/DocumentoUndoRedo.hpp"

int main() {
    Documento doc;
    doc.ejecutarEdicion(TipoEdicion::INSERTAR, 0, "Hola");      // "Hola"
    doc.ejecutarEdicion(TipoEdicion::INSERTAR, 4, " Mundo");    // "Hola Mundo"
    doc.deshacer();                                             // "Hola"
    doc.ejecutarEdicion(TipoEdicion::ELIMINAR, 0, "Ho");         // "la"
    doc.rehacer();                                              // no-op: Redo vacio tras la nueva edicion

    bool ok = (doc.obtenerContenido() == "la") &&
              (doc.obtenerTamañoRehacer() == 0) &&
              (doc.obtenerTamañoDeshacer() == 2);

    std::cout << "P1-Caso1 (secuencia normal mixta): " << (ok ? "[PASO]" : "[FALLO]")
              << " | contenido=\"" << doc.obtenerContenido() << "\""
              << " deshacer=" << doc.obtenerTamañoDeshacer()
              << " rehacer=" << doc.obtenerTamañoRehacer() << "\n";
    return ok ? 0 : 1;
}
