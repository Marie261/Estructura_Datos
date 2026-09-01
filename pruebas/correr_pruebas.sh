#!/bin/bash
# Compila y ejecuta los 14 casos de prueba de la Seccion 11.
# Uso: bash pruebas/correr_pruebas.sh   (ejecutar desde la raiz del repo)
set -e
mkdir -p /tmp/ada_p1_tests
fail=0

echo "=== Problema 1: Undo/Redo ==="
for f in pruebas/p1_*.cpp; do
  name=$(basename "$f" .cpp)
  g++ -std=c++17 -O2 -o /tmp/ada_p1_tests/$name "$f" codigo/DocumentoUndoRedo.cpp
  /tmp/ada_p1_tests/$name || fail=1
done

echo ""
echo "=== Problema 2: Firewall ==="
for f in pruebas/p2_*.cpp; do
  name=$(basename "$f" .cpp)
  g++ -std=c++17 -O2 -o /tmp/ada_p1_tests/$name "$f" codigo/Firewall.cpp
  /tmp/ada_p1_tests/$name || fail=1
done

if [ $fail -eq 0 ]; then
  echo ""
  echo "TODOS LOS CASOS PASARON."
else
  echo ""
  echo "HAY CASOS FALLIDOS. Revisar salida arriba."
  exit 1
fi
