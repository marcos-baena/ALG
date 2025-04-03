#include <iostream>
#include <vector>
#include <float.h>
#include <algorithm>
#include <assert.h>
#include <cmath>
#include <set>
#include <chrono>
#include <cstdlib> // Para atoi
#include <fstream> 

using namespace std;


struct Point {
    double x, y;
};

double dist(Point p1, Point p2) {
    return sqrt( (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y) );
}


double bruteForce(const vector<Point>& P, int l, int r) {
    double minDist = DBL_MAX;
    for (int i = l; i <= r; i++) {
        for (int j = i+1; j <= r; j++) {
            double d = dist(P[i], P[j]);
            if (d < minDist) {
                minDist = d;
            }
        }
    }
    return minDist;
}


int main(int argc, char *argv[]) {
    vector<Point> v;
    int n, argumento;
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
    unsigned long int semilla;
    ofstream fsalida;

    if (argc < 2) {
        cerr << "\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
        cerr << argv[0] << " NombreFicheroSalida Semilla tamCaso1 tamCaso2 ... tamCasoN\n\n";
        return 0;
    }

    /*
    // Abrimos fichero de salida
    fsalida.open(argv[1]);
    if (!fsalida.is_open()) {
        cerr << "Error: No se pudo abrir fichero para escritura " << argv[1] << "\n\n";
        return 0;
    }*/

    // Inicializamos generador de no. aleatorios
    semilla = atoi(argv[1]);
    srand(semilla);

    // Pasamos por cada tamaño de caso
    for (argumento = 2; argumento < argc; argumento++) {
        n = atoi(argv[argumento]);
        v.resize(n);

        double minDist = 10.0;
        for (int i = 0; i < n; i++){
            double x, y;
            bool validPoint = false;
            while (!validPoint) {
            x = rand() % (2 * n); // Aumentamos el rango para mayor dispersión
            y = rand() % (2 * n);

            validPoint = true;
            for (int j = 0; j < i; j++) {
                if (dist(v[j], {x, y}) < minDist) {
                validPoint = false;
                break;
                }
            }
            }
            v[i].x = x;
            v[i].y = y;
        }
        double minDist;
        t0 = chrono::high_resolution_clock::now();
        minDist = bruteForce(v, 0, n - 1);
        tf = chrono::high_resolution_clock::now();

        unsigned long tejecucion = chrono::duration_cast<chrono::microseconds>(tf - t0).count();
        cerr << "Mínima distancia " << minDist << endl;
        cerr << n << " " << tejecucion << endl;

        // Guardamos tamaño de caso y t_ejecucion a fichero de salida
        fsalida << n << " " << tejecucion << "\n";
    }

    fsalida.close();
    return 0;
}
