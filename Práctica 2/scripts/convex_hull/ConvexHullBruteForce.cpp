#include <iostream>
#include <set>
#include <float.h>
#include <cstdlib> // Para atoi
#include <chrono>
#include <fstream> // Para usar ficheros
#include <vector>
#include <limits>
using namespace std;
using namespace chrono;

// Estructura para representar un punto
struct Point {
    float x, y;
};

// Funcion que calcula el convex hull por fuerza bruta
vector<Point> convexHullBruteForce(const vector<Point>& points) {
    int n = points.size();
    vector<Point> hull;
    
    // Recorremos cada par de puntos
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int left = 0, right = 0;
            
            // Verificamos la posicion de cada otro punto respecto a la linea formada por points[i] y points[j]
            for (int k = 0; k < n; k++) {
                if (k == i || k == j)
                    continue;
                    
                float position = (points[j].x - points[i].x) * (points[k].y - points[i].y) -
                               (points[j].y - points[i].y) * (points[k].x - points[i].x);
                
                if (position > 0)
                    left++;
                else if (position < 0)
                    right++;
            }
            
            // Si todos los puntos se encuentran de un mismo lado (o son colineales), se añaden los puntos de la arista
            if (left == 0 || right == 0) {
                hull.push_back({points[i].x, points[i].y});
                hull.push_back({points[j].x, points[j].y});
            }
        }
    }
    
    return hull;
}

int main(int argc, char *argv[]) {
    vector<Point> points;
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
        points.resize(n);

        for (int i = 0; i < n; i++) {
            points[i].x = rand() % 101;
            points[i].y = rand() % 101;
        }

        cerr << "Ejecutando fuerza bruta CONVEX HULL para tam. caso: " << n << endl;

        t0 = chrono::high_resolution_clock::now();
        vector<Point> hull = convexHullBruteForce(points);
        tf = chrono::high_resolution_clock::now();

        unsigned long tejecucion = chrono::duration_cast<chrono::microseconds>(tf - t0).count();
        cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso " << n << endl;
        for (int i = 0; i < hull.size(); i++){
            cout << hull[i].x << "," << hull[i].y << endl;
        }

        // Guardamos tamaño de caso y t_ejecucion a fichero de salida
        fsalida << n << " " << tejecucion << "\n";
    }
    return 0;
}
