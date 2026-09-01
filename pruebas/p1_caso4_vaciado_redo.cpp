// Seccion 11, Problema 1, Caso 4: Edicion inmediatamente despues de un UNDO.
// Una nueva edicion tras un UNDO debe invalidar (vaciar) por completo la pila Redo.
#include <iostream>
#include "../codigo/DocumentoUndoRedo.hpp"

int main() {
    Documento doc;
    doc.ejecutarEdicion(TipoEdicion::INSERTAR, 0, "AAA");
    doc.ejecutarEdicion(TipoEdicion::INSERTAR, 3, "BBB");
    doc.deshacer();
    doc.deshacer();
    // En este punto pilaRehacer tiene 2 elementos
    bool redo_antes_lleno = (doc.obtenerTamañoRehacer() == 2);

    doc.ejecutarEdicion(TipoEdicion::INSERTAR, 0, "CCC");
    bool redo_despues_vacio = (doc.obtenerTamañoRehacer() == 0);

    bool ok = redo_antes_lleno && redo_despues_vacio;
    std::cout << "P1-Caso4 (edicion tras UNDO vacia Redo): " << (ok ? "[PASO]" : "[FALLO]") << "\n";
    return ok ? 0 : 1;
}
