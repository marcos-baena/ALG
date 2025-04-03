#include <iostream>
#include <vector>
#include <set>
#include <float.h>
#include <cstdlib> // Para atoi
#include <chrono>
using namespace std;
using namespace chrono;

// Estructura para representar un punto
struct Point {
    float x, y;
};

typedef pair<int, int> ParPuntos;

// Funcion que calcula el convex hull por fuerza bruta
set<ParPuntos> convexHullBruteForce(const vector<Point>& points) {
    int n = points.size();
    set<ParPuntos> hull;
    
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
                hull.insert({points[i].x, points[i].y});
                hull.insert({points[j].x, points[j].y});
            }
        }
    }
    
    return hull;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Uso: " << argv[0] << " <numero_de_puntos>" << endl;
        return 1;
    }
    
    int n = atoi(argv[1]);
    if (n <= 0) {
        cout << "El número de puntos debe ser un entero positivo." << endl;
        return 1;
    }

    srand(time(0)); // Semilla para números aleatorios

    // Generamos los puntos aleatorios en un rango [0,100]
    vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        points[i].x = rand() % 101;
        points[i].y = rand() % 101;
    }

    // Medimos el tiempo de ejecución de convexHullBruteForce
    auto start = high_resolution_clock::now();
    set<pair<int, int>> hull = convexHullBruteForce(points);
    auto end = high_resolution_clock::now();

    // Calculamos la duración en milisegundos
    auto duration = duration_cast<milliseconds>(end - start);
    
    cout<<n<<" "<<duration.count()<< endl;

    return 0;
}
