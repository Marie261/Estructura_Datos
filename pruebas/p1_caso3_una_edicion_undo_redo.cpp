// Seccion 11, Problema 1, Caso 3: Una edicion, UNDO, REDO.
#include <iostream>
#include "../codigo/DocumentoUndoRedo.hpp"

int main() {
    Documento doc;
    doc.ejecutarEdicion(TipoEdicion::INSERTAR, 0, "EAFIT");
    doc.deshacer();
    bool tras_undo_vacio = (doc.obtenerContenido() == "");
    doc.rehacer();
    bool tras_redo_restaurado = (doc.obtenerContenido() == "EAFIT");

    bool ok = tras_undo_vacio && tras_redo_restaurado;
    std::cout << "P1-Caso3 (una edicion, UNDO, REDO): " << (ok ? "[PASO]" : "[FALLO]") << "\n";
    return ok ? 0 : 1;
}
