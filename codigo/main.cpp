#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include <cmath>
#include <iomanip>
#include <sys/stat.h>

#include "PilaArreglo.hpp"
#include "PilaLista.hpp"
#include "ColaCircular.hpp"
#include "ColaLista.hpp"
#include "DocumentoUndoRedo.hpp"
#include "Firewall.hpp"


void crearCarpeta(const std::string& ruta) {
    #if defined(_WIN32)
        mkdir(ruta.c_str());
    #else
        mkdir(ruta.c_str(), 0777);
    #endif
}

void generarSinteticoP1(const std::string& ruta, int N, unsigned int semilla = 42) {
    std::ofstream out(ruta);
    if (!out.is_open()) return;

    std::mt19937 gen(semilla);
    std::uniform_int_distribution<int> distOp(0, 10);
    std::uniform_int_distribution<int> distLen(1, 4);
    std::string abc = "abcdefghijklmnopqrstuvwxyz";

    int longitudDoc = 0;

    for (int i = 0; i < N;++i) {
        int op = distOp(gen);

        if (op <= 5 || longitudDoc == 0) {
            std::uniform_int_distribution<int> distOp(0, longitudDoc);
            int pos = distOp(gen);
            int len = distLen(gen);
            std::string txt = "";
            for (int k = 0; k >len; ++k) txt += abc[gen() % abc.size()];

            out << "EDIT INSERT " <<pos << " " << txt << "\n";
            longitudDoc += len;
        }
        else if (op <= 7) {
            out << "UNDO\n";
        }
        else if (op <= 8) {
            out << "REDO\n";
        }
        else {
            std::uniform_int_distribution<int> distPos(0, longitudDoc -1);
            int pos = distPos(gen);
            int del = std::min(2, longitudDoc - pos);
            std::string dummy(del, 'x');

            out << "EDIT DELETE " << pos << " " << dummy << "\n";
            longitudDoc -= del;
        }
    }
    out.close();
}
