#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <iostream>
#include <fstream> // Para usar ficheros
#include <vector>
using namespace std;

void QuickSort(vector<int> &v, int low, int high);
int partition(vector<int> &v, int low, int high);

int main(int argc, char *argv[]) {
    vector<int> v;
    int n, argumento;
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
    unsigned long int semilla;
    ofstream fsalida;

    if (argc <= 3) {
        cerr << "\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
        cerr << argv[0] << " NombreFicheroSalida Semilla tamCaso1 tamCaso2 ... tamCasoN\n\n";
        return 0;
    }

    // Abrimos fichero de salida
    fsalida.open(argv[1]);
    if (!fsalida.is_open()) {
        cerr << "Error: No se pudo abrir fichero para escritura " << argv[1] << "\n\n";
        return 0;
    }

    // Inicializamos generador de no. aleatorios
    semilla = atoi(argv[2]);
    srand(semilla);

    // Pasamos por cada tamaño de caso
    for (argumento = 3; argumento < argc; argumento++) {
        n = atoi(argv[argumento]);
        v.resize(n);

        // Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
        for (int i = 0; i < n; i++)
            v[i] = rand() % n;

        cerr << "Ejecutando QuickSort para tam. caso: " << n << endl;

        t0 = chrono::high_resolution_clock::now();
        QuickSort(v, 0, n - 1);
        tf = chrono::high_resolution_clock::now();

        unsigned long tejecucion = chrono::duration_cast<chrono::microseconds>(tf - t0).count();
        cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso " << n << endl;

        // Guardamos tamaño de caso y t_ejecucion a fichero de salida
        fsalida << n << " " << tejecucion << "\n";
    }

    fsalida.close();
    return 0;
}

int partition(vector<int> &vec, int low, int high) {
    int mid = low + (high - low) / 2;
    swap(vec[mid], vec[high]); // Mueve el pivote al final
    int pivot = vec[high];  
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (vec[j] <= pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }
    swap(vec[i + 1], vec[high]);
    return i + 1;
}

void QuickSort(vector<int> &vec, int low, int high) {
    if (low < high) {
        int pi = partition(vec, low, high);
        QuickSort(vec, low, pi - 1);
        QuickSort(vec, pi + 1, high);
    }
}

