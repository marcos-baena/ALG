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
ostream& operator<<(ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

ostream& operator<<(ostream& os, const vector<Point>& points) {
    for (const auto& p : points) {
        os << p << " ";
    }
    return os;
}

void swap(Point* a, Point* b) {
    Point t = *a;
    *a = *b;
    *b = t;
}

int partition(vector<Point>& arr, int low, int high) {
    double pivot = arr[high].x;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].x < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(vector<Point>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void sort_by_x(vector<Point>& points) {
    quickSort(points, 0, points.size() - 1);
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


double closestUtil(vector<Point> &PX, int l, int r) {
    // Si el subrango es pequeño, fuerza bruta
    if (r - l <= 3) {
        return bruteForce(PX, l, r);
    }

    int mid = (l + r) / 2;
    double midX = PX[mid].x;

    // bestPair se va actualizando; 
    // para tener la mínima distancia, llamo recursivamente a izq y der
    double dl = closestUtil(PX, l, mid);
    double dr = closestUtil(PX, mid+1, r);

    double d = dl < dr ? dl : dr;
    // Construir el strip (puntos que quedan en [midX - d, midX + d])
    vector<Point> strip;
    strip.reserve(r - l + 1);
    for (int i = l; i <= r; i++) {
        if (fabs(PX[i].x - midX) < d) {
            strip.push_back(PX[i]);
        }
    }
    // Ordenar la franja por Y
    sort(strip.begin(), strip.end(), [](auto &a, auto &b){
        return a.y < b.y;
    });

    // Revisar cada punto del strip con sus siguientes
    // mientras la diferencia en Y sea < d
    for (int i = 0; i < (int)strip.size(); i++) {
        for (int j = i+1; j < (int)strip.size() && (strip[j].y - strip[i].y) < d; j++) {
            double distStrip = dist(strip[i], strip[j]);
            if (distStrip < d) {
                d = distStrip;
            }
        }
    }

    return d;
}

int main(int argc, char *argv[]) {
    vector<Point> v;
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

        for (int i = 0; i < n; i++){
            double x, y;
            
            bool validPoint = false;
            while (!validPoint) {
                x = rand() % (2 * n); // Aumentamos el rango para mayor dispersión
                y = rand() % (2 * n);
                
                validPoint = true;
                for (int j = 0; j < i; j++) {
                    if (v[j].x == x && v[j].y == y) {
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
        minDist = closestUtil(v, 0, n - 1);
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
