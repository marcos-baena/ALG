#include <iostream>
#include <vector>
#include <set>
#include <float.h>
#include <cstdlib>   // Para atoi y rand
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;

// Estructura para representar un punto
struct Point {
    float x, y;
};

typedef pair<int, int> ParPuntos;

// Función auxiliar para intercambiar dos puntos
void swap(Point &a, Point &b) {
    Point temp = a;
    a = b;
    b = temp;
}

// Función auxiliar partition para QuickSort (ordena según la coordenada x)
int partition(vector<Point>& arr, int low, int high) {
    float pivot = arr[high].x; // Elegimos el último elemento como pivote
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j].x < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Implementación de QuickSort para ordenar los puntos según su coordenada x
void quickSort(vector<Point>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Función que calcula el convex hull por fuerza bruta
set<ParPuntos> convexHullBruteForce(const vector<Point>& points) {
    int n = points.size();
    set<ParPuntos> hull;
    
    // Recorremos cada par de puntos
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int left = 0, right = 0;
            
            // Verificamos la posición de cada otro punto respecto a la línea formada por points[i] y points[j]
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
                hull.insert({static_cast<int>(points[i].x), static_cast<int>(points[i].y)});
                hull.insert({static_cast<int>(points[j].x), static_cast<int>(points[j].y)});
            }
        }
    }
    
    return hull;
}

// Función convexHullDivideAndConquer usando recursión y QuickSort para ordenar
set<ParPuntos> convexHullDivideAndConquer(const vector<Point>& points) {
    // Caso base: para pocos puntos, se usa fuerza bruta
    if (points.size() <= 5)
        return convexHullBruteForce(points);
    
    // Copia de los puntos para poder ordenarlos con QuickSort
    vector<Point> sortedPoints = points;
    quickSort(sortedPoints, 0, sortedPoints.size() - 1); // Usando QuickSort
    
    int mid = sortedPoints.size() / 2;
    vector<Point> leftPoints(sortedPoints.begin(), sortedPoints.begin() + mid);
    vector<Point> rightPoints(sortedPoints.begin() + mid, sortedPoints.end());
    
    // Calculamos recursivamente el convex hull para cada mitad
    set<ParPuntos> leftHull = convexHullDivideAndConquer(leftPoints);
    set<ParPuntos> rightHull = convexHullDivideAndConquer(rightPoints);
    
    // Fusionamos los puntos de ambos convex hulls
    vector<Point> mergedPoints;
    for (const auto &p : leftHull) {
        mergedPoints.push_back({static_cast<float>(p.first), static_cast<float>(p.second)});
    }
    for (const auto &p : rightHull) {
        mergedPoints.push_back({static_cast<float>(p.first), static_cast<float>(p.second)});
    }
    
    // Se aplica fuerza bruta a la unión de los puntos para obtener la envolvente final
    return convexHullBruteForce(mergedPoints);
}

// Ejemplo de uso en main
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
    
    srand(time(0));
    vector<Point> points(n);
    // Generamos puntos aleatorios en el rango [0, 100]
    for (int i = 0; i < n; i++) {
        points[i].x = rand() % 101;
        points[i].y = rand() % 101;
    }
    
    // Medimos el tiempo de ejecución de convexHullDivideAndConquer
    auto start = high_resolution_clock::now();
    set<ParPuntos> hull = convexHullDivideAndConquer(points);
    auto end = high_resolution_clock::now();
    
    // Calculamos la duración en milisegundos
    auto duration = duration_cast<milliseconds>(end - start);
    
    cout<<n<<" "<<duration.count()<< endl;

    return 0;
}
