#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include <cmath>
#include <iomanip>
#include <filesystem>

#include "PilaArreglo.hpp"
#include "PilaLista.hpp"
#include "ColaCircular.hpp"
#include "ColaLista.hpp"
#include "DocumentoUndoRedo.hpp"
#include "Firewall.hpp"

namespace fs = std::filesystem;


void crearCarpeta(const std::string& ruta) {
    if (!fs::exists(ruta)){
        fs::create_directories(ruta);
    }
    
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

        if (op <= 5 || longitudDoc == 0) { //INSERTAR
            std::uniform_int_distribution<int> distOp(0, longitudDoc);
            int pos = distOp(gen);
            int len = distLen(gen);
            std::string txt = "";
            for (int k = 0; k < len; ++k) txt += abc[gen() % abc.size()];

            out << "EDIT INSERT " <<pos << " " << txt << "\n";
            longitudDoc += len;
        }
        else if (op <= 7) {//UNDO
            out << "UNDO\n";
        }
        else if (op <= 8) {//REDO
            out << "REDO\n";
        }
        else {//ELIMINAR
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

void generarSinteticoP2(const std::string& ruta, int N, unsigned int semilla = 42){
    std::ofstream out(ruta);
    if (!out.is_open()) return;
    
    std::mt19937 gen(semilla);
    std::uniform_int_distribution<int> disDeltaT(0, 12);
    std::uniform_int_distribution<int> distBytes(64, 1500);
    std::uniform_int_distribution<int> distDeq(0, 8);

    long long tsActual = 0;

    for (int i = 0; i < N; ++i){
        tsActual+= disDeltaT(gen);
        int bytes = distBytes(gen);

        if (distDeq(gen) == 0 && i>0){
            out << "DEQUEUE\n";
        }else {
            out << "PAQUETE " << tsActual << " " << bytes << "\n";
        } 
    }

    out.close();  
}

struct EventoP1 {
    std::string cmd;
    TipoEdicion tipo;
    int pos;
    std::string txt;
};

struct EventoP2 {
    bool esDequeue;
    long long ts;
    int bytes;
};

void probarCasosLimite(){
    std::cout << "==================================================\n";
    std::cout << "       VALIDACION DE CASOS LIMITE (SEC. 11)       \n";
    std::cout << "==================================================\n";
    
    Documento doc;
    std::cout <<"1.UNDO en pila vacia: "
              <<(doc.deshacer() == ResultadoOperacion::NoOpPilaVacia ? "[PASO]" : "[FALLO]")<<"\n";
    doc.ejecutarEdicion(TipoEdicion::INSERTAR, 0, "EAFIT");
    doc.deshacer();
    doc.rehacer();
    std::cout << "2. Edicion + UNDO + REDO: "
              << (doc.obtenerContenido() == "EAFIT" ? "[PASO]" : "[FALLO]") << "\n";
    doc.deshacer();
    doc.ejecutarEdicion(TipoEdicion::INSERTAR, 0, "Estructuras");
    std::cout << "3. Vaciado de Redo tras nueva edicion: "
              << (doc.obtenerTamañoRehacer() == 0 ? "[PASO]" : "[FALLO]") << "\n";
    Firewall fw(1000, 100, 2);
    Paquete pAux;
    std::cout << "4. Dequeue en buffer vacío: "
              << (!fw.procesarDequeue(pAux) ? "[PASO]" : "[FALLO]") << "\n";
    
    fw.procesarLlegadaPaquete(Paquete(1, 100, 10));
    fw.procesarLlegadaPaquete(Paquete(2, 100, 20));
    EstadoPaquete stRafa = fw.procesarLlegadaPaquete(Paquete(3, 100, 30));
    std::cout << "5. Rechazo por exceso de Tasa (L=2): "
              << (stRafa == EstadoPaquete::RechazadoPorTasa ? "[PASO]" : "[FALLO]") << "\n\n";
}

void ejecutarExperimentos() {
    crearCarpeta("datos");
    crearCarpeta("resultados");
    std::cout << "==================================================\n";
    std::cout << "        EJECUTANDO MEDICIONES Y TIMINGS           \n";
    std::cout << "==================================================\n\n";
    std::vector<int> tamaños = {1000, 10000, 100000, 1000000};
    int repeticiones = 5;
    std::ofstream res("resultados/reporte_tiempos.txt");
    std::cout << "--- PROBLEMA 1: UNDO / REDO ---\n";
    res << "---PROBLEMA 1 ---\n";

    for (int N : tamaños) {
        std::string archivo = "datos/p1_n" + std::to_string(N) + ".txt";
        generarSinteticoP1(archivo, N, 42);

        std::vector<EventoP1>  eventos;
        eventos.reserve(N);
        std::fstream in(archivo);
        std::string cmd;
        while (in >> cmd) {
            EventoP1 ev;
            ev.cmd = cmd;
            if (cmd == "EDIT") {
                std::string tStr;
                in >> tStr >> ev.pos >> ev.txt;
                if (tStr == "INSERT") ev.tipo = TipoEdicion::INSERTAR;
                else if (tStr == "DELETE") ev.tipo = TipoEdicion::ELIMINAR;
                else if (tStr == "REPLACE") ev.tipo = TipoEdicion::REEMPLAZAR;
            }
            eventos.push_back(ev);
        }
        std::vector<double> tiempos;
        Documento doc;
        for (int r = 0; r < repeticiones; ++r) {
            doc.reiniciar();
            auto inicio = std::chrono::high_resolution_clock::now();
            for (const auto& ev : eventos) {
                if (ev.cmd == "EDIT") doc.ejecutarEdicion(ev.tipo, ev.pos, ev.txt);
                else if (ev.cmd == "UNDO") doc.deshacer();
                else if (ev.cmd == "REDO") doc.rehacer();
            }
            auto fin = std::chrono::high_resolution_clock::now(); 
            tiempos.push_back(std::chrono::duration<double, std::milli>(fin -inicio).count());
        }
        double suma = 0;
        for (double t : tiempos) suma += t;
        double promedio = suma / repeticiones;
        double sumaVar = 0;
        for (double t : tiempos) sumaVar += (t - promedio) * (t - promedio);
        double desvStd = std::sqrt(sumaVar / repeticiones);

        std::cout << "N = " <<std::setw(7) << N << " | Promedio: "
                  << std::setw(8) << std::fixed << std::setprecision(2) << promedio
                  << " ms | DesvStd: " << desvStd << "ms\n";
        res << "N=" << N << " Promedio=" << promedio << "ms DesvStd=" << desvStd << "ms\n";
    }

    std::cout << "\n--- PROBLEMA 2: FIREWALL ---\n";
    res << "\n--- PROBLEMA 2 ---\n";
    for (int N : tamaños) {
        std::string archivo = "datos/p2_n" + std::to_string(N) + ".txt";
        generarSinteticoP2(archivo, N, 42);

        std::vector<EventoP2> eventos;
        eventos.reserve(N);
        std::ifstream in(archivo);
        std::string cmd;
        while (in >> cmd) {
            EventoP2 ev;
            if (cmd == "DEQUEUE") {
                ev.esDequeue = true;
            } else {
                ev.esDequeue = false;
                in >> ev.ts >> ev.bytes;
            }
            eventos.push_back(ev);
        }
        std::vector<double> tiempos;
        Firewall fw(65536, 1000, 100);
        for (int r = 0; r < repeticiones; ++r) {
            fw.reiniciar();
            auto inicio = std::chrono::high_resolution_clock::now();
            int id = 1;
            Paquete pAux;
            for (const auto& ev : eventos) {
                if (ev.esDequeue) fw.procesarDequeue(pAux);
                else fw.procesarLlegadaPaquete(Paquete(id++, ev.bytes, ev.ts));;
            }
            auto fin = std::chrono::high_resolution_clock::now();
            tiempos.push_back(std::chrono::duration<double, std::milli>(fin -inicio).count());
        }
        double suma = 0;
        for (double t : tiempos)suma += t;
        double promedio = suma / repeticiones;
        double sumaVar = 0;
        for (double t : tiempos) sumaVar += (t - promedio) * (t- promedio);
        double desvStd = std::sqrt(sumaVar / repeticiones);
        std::cout << "N = " << std::setw(7) << N << " | Promedio: "
                  << std::setw(8) << std::fixed << std::setprecision(2) << promedio
                  << " ms | DesvStd: " << desvStd << " ms\n";
    }
    res.close();
    std::cout << "\nResultados generados correctamente en 'resultados/reporte_tiempos.txt'.\n";
}
// Comparacion explicita de costos: PilaArreglo (arreglo dinamico) vs PilaLista (lista enlazada)
// Cumple el requisito obligatorio de la Seccion 7: exponer la misma interfaz (TAD Pila)
// sobre dos representaciones internas distintas y medir sus costos.
void compararRepresentacionesPila() {
    std::cout << "\n==================================================\n";
    std::cout << "   COMPARACION: PilaArreglo vs PilaLista (push+pop) \n";
    std::cout << "==================================================\n";

    std::vector<int> tamaños = {1000, 10000, 100000, 1000000};
    int repeticiones = 5;
    std::ofstream res("resultados/comparacion_pilas.txt");
    res << "N;RepArreglo_ms;RepArreglo_std;RepLista_ms;RepLista_std\n";

    for (int N : tamaños) {
        std::vector<double> tArreglo, tLista;

        for (int r = 0; r < repeticiones; ++r) {
            PilaArreglo<int> pa;
            auto t0 = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < N; ++i) pa.apilar(i);
            for (int i = 0; i < N; ++i) pa.desapilar();
            auto t1 = std::chrono::high_resolution_clock::now();
            tArreglo.push_back(std::chrono::duration<double, std::milli>(t1 - t0).count());

            PilaLista<int> pl;
            auto t2 = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < N; ++i) pl.apilar(i);
            for (int i = 0; i < N; ++i) pl.desapilar();
            auto t3 = std::chrono::high_resolution_clock::now();
            tLista.push_back(std::chrono::duration<double, std::milli>(t3 - t2).count());
        }

        auto media = [](const std::vector<double>& v) {
            double s = 0; for (double x : v) s += x; return s / v.size();
        };
        auto desv = [&](const std::vector<double>& v, double m) {
            double s = 0; for (double x : v) s += (x - m) * (x - m);
            return std::sqrt(s / v.size());
        };

        double mA = media(tArreglo), dA = desv(tArreglo, mA);
        double mL = media(tLista), dL = desv(tLista, mL);

        std::cout << "N = " << std::setw(7) << N
                  << " | Arreglo: " << std::fixed << std::setprecision(2) << mA << " ms (+-" << dA
                  << ") | Lista: " << mL << " ms (+-" << dL << ")\n";
        res << N << ";" << mA << ";" << dA << ";" << mL << ";" << dL << "\n";
    }
    res.close();
    std::cout << "Resultados en 'resultados/comparacion_pilas.txt'.\n";
}

int main() {
    probarCasosLimite();
    ejecutarExperimentos();
    compararRepresentacionesPila();
    return 0;
}