#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <iostream>
#include <fstream> // Para usar ficheros
#include <vector>
using namespace std;

void Hanoi(int n, char from_rod, char to_rod,
                  char aux_rod);

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

        cerr << "Ejecutando Hanoi para tam. caso: " << n << endl;

        t0 = chrono::high_resolution_clock::now();
        Hanoi(n, 'A', 'B', 'C');
        tf = chrono::high_resolution_clock::now();

        unsigned long tejecucion = chrono::duration_cast<chrono::microseconds>(tf - t0).count();
        cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso " << n << endl;

        // Guardamos tamaño de caso y t_ejecucion a fichero de salida
        fsalida << n << " " << tejecucion << "\n";
    }

    fsalida.close();
    return 0;
}


void Hanoi(int n, char from_rod, char to_rod,
                  char aux_rod)
{
    if (n == 0) {
        return;
    }
    Hanoi(n - 1, from_rod, aux_rod, to_rod);
    //cout << "Move disk " << n << " from rod " << from_rod
        // << " to rod " << to_rod << endl;
    Hanoi(n - 1, aux_rod, to_rod, from_rod);
}
