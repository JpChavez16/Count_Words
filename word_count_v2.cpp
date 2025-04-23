#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <omp.h>

using namespace std;

const int NUM_THREADS = 4;  // Ajusta según tu CPU
const string ARCHIVO = "archivo_20gb.txt";

unordered_map<string, int> combinar_mapas(const vector<unordered_map<string, int>>& mapas) {
    unordered_map<string, int> resultado;
    for (const auto& mapa : mapas) {
        for (const auto& par : mapa) {
            resultado[par.first] += par.second;
        }
    }
    return resultado;
}

void contar_bloque(size_t inicio, size_t fin, unordered_map<string, int>& mapa_local) {
    ifstream archivo(ARCHIVO, ios::in | ios::binary);
    archivo.seekg(inicio);

    string linea;
    size_t pos = archivo.tellg();

    while (pos < fin && getline(archivo, linea)) {
        istringstream ss(linea);
        string palabra;
        while (ss >> palabra) {
            ++mapa_local[palabra];
        }
        pos = archivo.tellg();
        if (archivo.eof()) break;
    }
}

int main() {
    ifstream archivo(ARCHIVO, ios::ate | ios::binary);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    size_t tam_archivo = archivo.tellg();
    archivo.close();

    vector<unordered_map<string, int>> mapas_locales(NUM_THREADS);

    #pragma omp parallel num_threads(NUM_THREADS)
    {
        int id = omp_get_thread_num();
        size_t bloque_inicio = (tam_archivo / NUM_THREADS) * id;
        size_t bloque_fin = (id == NUM_THREADS - 1) ? tam_archivo : (tam_archivo / NUM_THREADS) * (id + 1);

        // Alinear al inicio de línea
        if (bloque_inicio != 0) {
            ifstream file(ARCHIVO, ios::in | ios::binary);
            file.seekg(bloque_inicio);
            string dummy;
            getline(file, dummy);  // Salta línea incompleta
            bloque_inicio = file.tellg();
            file.close();
        }

        contar_bloque(bloque_inicio, bloque_fin, mapas_locales[id]);
    }

    unordered_map<string, int> resultado = combinar_mapas(mapas_locales);

    ofstream salida("resultado_v2.txt");
    for (const auto& par : resultado) {
        salida << par.first << " " << par.second << "\n";
    }

    return 0;
}

