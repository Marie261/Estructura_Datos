// Seccion 11, Problema 1, Caso 2: UNDO sin ediciones previas.
// Debe ser un no-op valido, sin abortar el programa.
#include <iostream>
#include "../codigo/DocumentoUndoRedo.hpp"

int main() {
    Documento doc;
    ResultadoOperacion r = doc.deshacer();

    bool ok = (r == ResultadoOperacion::NoOpPilaVacia) &&
              (doc.obtenerContenido() == "");

    std::cout << "P1-Caso2 (UNDO sin ediciones previas): " << (ok ? "[PASO]" : "[FALLO]") << "\n";
    return ok ? 0 : 1;
}
