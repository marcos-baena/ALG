#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <iostream>
#include <fstream> // Para usar ficheros
#include <vector>
#include <limits>

using namespace std;
/**************************************/

int getSmallestNumber(std::vector<int> &v, int k) {
    
    int N = v.size();

    vector<int> copy(v);
    auto pos = copy.begin();
    string smallest_str = "";

    while (smallest_str.size() < k){
        int smallest = std::numeric_limits<int>::max();
        for (auto i = copy.begin(); i != copy.end(); ++i){ //encontramos minimo
            if (*i < smallest){
                smallest = *i;
                pos = i;
            }
        }
        smallest_str.append(to_string(smallest)); //append the min
        copy.erase(pos);
    }
    
    return (stoi(smallest_str));
}

int main(int argc, char *argv[])
{
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
            v[i] = rand()%9 + 1;

        cerr << "Ejecutando fuerza bruta para tam. caso: " << n << endl;

        t0 = chrono::high_resolution_clock::now();
        int k = rand() % 5 + 5;
    	int SmallestNumber = getSmallestNumber(v, k);
        tf = chrono::high_resolution_clock::now();

        unsigned long tejecucion = chrono::duration_cast<chrono::microseconds>(tf - t0).count();
        cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso " << n << endl;

        // Guardamos tamaño de caso y t_ejecucion a fichero de salida
        fsalida << n << " " << tejecucion << "\n";
    }
    return 0;
}
