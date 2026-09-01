// Seccion 11, Problema 1, Caso 5: N ediciones seguidas de N deshacer consecutivos.
// Al final el documento debe quedar vacio y ambas pilas en su estado esperado.
#include <iostream>
#include "../codigo/DocumentoUndoRedo.hpp"

int main() {
    Documento doc;
    const int N = 50;

    for (int i = 0; i < N; ++i) {
        doc.ejecutarEdicion(TipoEdicion::INSERTAR, doc.obtenerContenido().size(), "x");
    }
    bool tras_ediciones = (doc.obtenerContenido().size() == static_cast<size_t>(N)) &&
                           (doc.obtenerTamañoDeshacer() == N);

    for (int i = 0; i < N; ++i) {
        doc.deshacer();
    }
    bool tras_undos = (doc.obtenerContenido() == "") &&
                       (doc.obtenerTamañoDeshacer() == 0) &&
                       (doc.obtenerTamañoRehacer() == N);

    bool ok = tras_ediciones && tras_undos;
    std::cout << "P1-Caso5 (N ediciones + N UNDO consecutivos, N=" << N << "): "
              << (ok ? "[PASO]" : "[FALLO]") << "\n";
    return ok ? 0 : 1;
}
