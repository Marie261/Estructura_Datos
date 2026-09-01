// Seccion 11, Problema 1, Caso 6: Mas REDO que elementos disponibles.
// Los REDO sobrantes deben ser no-ops validos, sin abortar el programa.
#include <iostream>
#include "../codigo/DocumentoUndoRedo.hpp"

int main() {
    Documento doc;
    doc.ejecutarEdicion(TipoEdicion::INSERTAR, 0, "AB");
    doc.deshacer(); // pilaRehacer tiene 1 elemento

    ResultadoOperacion r1 = doc.rehacer(); // exitoso, restaura "AB"
    ResultadoOperacion r2 = doc.rehacer(); // pilaRehacer vacia -> no-op
    ResultadoOperacion r3 = doc.rehacer(); // sigue vacia -> no-op

    bool ok = (r1 == ResultadoOperacion::Exitoso) &&
              (r2 == ResultadoOperacion::NoOpPilaVacia) &&
              (r3 == ResultadoOperacion::NoOpPilaVacia) &&
              (doc.obtenerContenido() == "AB");

    std::cout << "P1-Caso6 (mas REDO que disponibles): " << (ok ? "[PASO]" : "[FALLO]") << "\n";
    return ok ? 0 : 1;
}
