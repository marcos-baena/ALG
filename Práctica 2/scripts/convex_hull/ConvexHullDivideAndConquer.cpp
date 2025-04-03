#include <iostream>
#include <vector>
#include <set>
#include <float.h>
#include <cstdlib>   // Para atoi y rand
#include <chrono>
#include <algorithm>
#include <fstream>

using namespace std;
using namespace chrono;

// Estructura para representar un punto
struct Point {
    float x, y;
};

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
// Checks whether the line is crossing the polygon
int orientation(Point Point1, Point Point2,
                Point Point3)
{
    int res = (Point2.y-Point1.y)*(Point3.x-Point2.x) -
            (Point3.y-Point2.y)*(Point2.x-Point1.y);

    if (res == 0)
        return 0;
    if (res > 0)
        return 1;
    return -1;
}


// Create polygons and find tangents
vector<Point> merger(vector<Point> Points1,
                            vector<Point> Points2)
{
    int n1 = Points1.size(), n2 = Points2.size();

    int right_most_left_point = 0, left_most_right_point = 0;
    for (int i=1; i<n1; i++)
        if (Points1[i].x > Points1[right_most_left_point].x)
            right_most_left_point = i;

    // left_most_right_point -> leftmost point of b
    for (int i=1; i<n2; i++)
        if (Points2[i].x < Points2[left_most_right_point].x)
            left_most_right_point=i;

    // finding the upper tangent
    int index_1 = right_most_left_point, index_2 = left_most_right_point;
    bool done = 0;
    while (!done)
    {
        done = 1;
        while (orientation(Points2[index_2], Points1[index_1], Points1[(index_1+1)%n1]) >=0)
            index_1 = (index_1 + 1) % n1;

        while (orientation(Points1[index_1], Points2[index_2], Points2[(n2+index_2-1)%n2]) <=0)
        {
            index_2 = (n2+index_2-1)%n2;
            done = 0;
        }
    }

    int upper1 = index_1, upper2 = index_2;
    index_1 = right_most_left_point, index_2=left_most_right_point;
    done = 0;
    int g = 0;
    while (!done)//finding the lower tangent
    {
        done = 1;
        while (orientation(Points1[index_1], Points2[index_2], Points2[(index_2+1)%n2])>=0)
            index_2=(index_2+1)%n2;

        while (orientation(Points2[index_2], Points1[index_1], Points1[(n1+index_1-1)%n1])<=0)
        {
            index_1=(n1+index_1-1)%n1;
            done=0;
        }
    }

    int lower1 = index_1, lower2 = index_2;
    vector<Point> ret;


    int ind = upper1;
    ret.push_back(Points1[upper1]);
    while (ind != lower1)
    {
        ind = (ind+1)%n1;
        ret.push_back(Points1[ind]);
    }

    ind = lower2;
    ret.push_back(Points2[lower2]);
    while (ind != upper2)
    {
        ind = (ind+1)%n2;
        ret.push_back(Points2[ind]);
    }
    return ret;
}

vector<Point> convexHullBruteForce(const vector<Point> points) {
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

// Returns the convex hull for the given set of points
vector<Point> divide_and_conquer(vector<Point> points, int l, int r)
{
    if ((r-l+1)<= 5)
        return convexHullBruteForce({points.begin() + l, points.begin() + r + 1});

    // left contains the left half points
    // right contains the right half points
    int half = (l + r)/2;

    vector<Point> left(points.begin() + l, points.begin() + half + 1);
    vector<Point> right(points.begin() + half + 1, points.begin() + r + 1);

    // Recurse on each half
    vector<Point> left_hull  = divide_and_conquer(points, l,half);
    vector<Point> right_hull = divide_and_conquer(points, half+1, r);

    // merging the convex hulls
    return merger(left_hull, right_hull);
}

*/



////////////////////////////////////////////////////////////////////////////////////////////////////////
pair<int, int> mid;

// determines the quadrant of a point
// (used in compare())
int quad(pair<int, int> p)
{
    if (p.first >= 0 && p.second >= 0)
        return 1;
    if (p.first <= 0 && p.second >= 0)
        return 2;
    if (p.first <= 0 && p.second <= 0)
        return 3;
    return 4;
}

// Checks whether the line is crossing the polygon
int orientation(pair<int, int> a, pair<int, int> b,
                pair<int, int> c)
{
    int res = (b.second-a.second)*(c.first-b.first) -
            (c.second-b.second)*(b.first-a.first);

    if (res == 0)
        return 0;
    if (res > 0)
        return 1;
    return -1;
}

// compare function for sorting
bool compare(pair<int, int> p1, pair<int, int> q1)
{
    pair<int, int> p = make_pair(p1.first - mid.first,
                                p1.second - mid.second);
    pair<int, int> q = make_pair(q1.first - mid.first,
                                q1.second - mid.second);

    int one = quad(p);
    int two = quad(q);

    if (one != two)
        return (one < two);
    return (p.second*q.first < q.second*p.first);
}

// Finds upper tangent of two polygons 'a' and 'b'
// represented as two vectors.
vector<pair<int, int>> merger(vector<pair<int, int> > a,
                            vector<pair<int, int> > b)
{
    // n1 -> number of points in polygon a
    // n2 -> number of points in polygon b
    int n1 = a.size(), n2 = b.size();

    int ia = 0, ib = 0;
    for (int i=1; i<n1; i++)
        if (a[i].first > a[ia].first)
            ia = i;

    // ib -> leftmost point of b
    for (int i=1; i<n2; i++)
        if (b[i].first < b[ib].first)
            ib=i;

    // finding the upper tangent
    int inda = ia, indb = ib;
    bool done = 0;
    while (!done)
    {
        done = 1;
        while (orientation(b[indb], a[inda], a[(inda+1)%n1]) >=0)
            inda = (inda + 1) % n1;

        while (orientation(a[inda], b[indb], b[(n2+indb-1)%n2]) <=0)
        {
            indb = (n2+indb-1)%n2;
            done = 0;
        }
    }

    int uppera = inda, upperb = indb;
    inda = ia, indb=ib;
    done = 0;
    int g = 0;
    while (!done)//finding the lower tangent
    {
        done = 1;
        while (orientation(a[inda], b[indb], b[(indb+1)%n2])>=0)
            indb=(indb+1)%n2;

        while (orientation(b[indb], a[inda], a[(n1+inda-1)%n1])<=0)
        {
            inda=(n1+inda-1)%n1;
            done=0;
        }
    }

    int lowera = inda, lowerb = indb;
    vector<pair<int, int>> ret;

    //ret contains the convex hull after merging the two convex hulls
    //with the points sorted in anti-clockwise order
    int ind = uppera;
    ret.push_back(a[uppera]);
    while (ind != lowera)
    {
        ind = (ind+1)%n1;
        ret.push_back(a[ind]);
    }

    ind = lowerb;
    ret.push_back(b[lowerb]);
    while (ind != upperb)
    {
        ind = (ind+1)%n2;
        ret.push_back(b[ind]);
    }
    return ret;

}

// Brute force algorithm to find convex hull for a set
// of less than 6 points
vector<pair<int, int>> bruteHull(vector<pair<int, int>> a)
{
    // Take any pair of points from the set and check
    // whether it is the edge of the convex hull or not.
    // if all the remaining points are on the same side
    // of the line then the line is the edge of convex
    // hull otherwise not
    set<pair<int, int> >s;

    for (int i=0; i<a.size(); i++)
    {
        for (int j=i+1; j<a.size(); j++)
        {
            int x1 = a[i].first, x2 = a[j].first;
            int y1 = a[i].second, y2 = a[j].second;

            int a1 = y1-y2;
            int b1 = x2-x1;
            int c1 = x1*y2-y1*x2;
            int pos = 0, neg = 0;
            for (int k=0; k<a.size(); k++)
            {
                if (a1*a[k].first+b1*a[k].second+c1 <= 0)
                    neg++;
                if (a1*a[k].first+b1*a[k].second+c1 >= 0)
                    pos++;
            }
            if (pos == a.size() || neg == a.size())
            {
                s.insert(a[i]);
                s.insert(a[j]);
            }
        }
    }

    vector<pair<int, int>>ret;
    for (auto e:s)
        ret.push_back(e);

    // Sorting the points in the anti-clockwise order
    mid = {0, 0};
    int n = ret.size();
    for (int i=0; i<n; i++)
    {
        mid.first += ret[i].first;
        mid.second += ret[i].second;
        ret[i].first *= n;
        ret[i].second *= n;
    }
    sort(ret.begin(), ret.end(), compare);
    for (int i=0; i<n; i++)
        ret[i] = make_pair(ret[i].first/n, ret[i].second/n);

    return ret;
}

// Returns the convex hull for the given set of points
vector<pair<int, int>> divide(vector<pair<int, int>> a)
{
    // If the number of points is less than 6 then the
    // function uses the brute algorithm to find the
    // convex hull
    if (a.size() <= 5)
        return bruteHull(a);

    // left contains the left half points
    // right contains the right half points
    vector<pair<int, int>>left, right;
    for (int i=0; i<a.size()/2; i++)
        left.push_back(a[i]);
    for (int i=a.size()/2; i<a.size(); i++)
        right.push_back(a[i]);

    // convex hull for the left and right sets
    vector<pair<int, int>>left_hull = divide(left);
    vector<pair<int, int>>right_hull = divide(right);

    // merging the convex hulls
    return merger(left_hull, right_hull);
}


// Ejemplo de uso en main
int main(int argc, char *argv[]) {
    vector<pair<int, int>> points;
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
            points.push_back(make_pair(rand()%101,rand()%101));
        }

        cerr << "Ejecutando fuerza bruta CONVEX HULL para tam. caso: " << n << endl;

        t0 = chrono::high_resolution_clock::now();

        quickSort(points,0,points.size()-1);

        vector<Point> hull = divide_and_conquer(points,0,points.size()-1);

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

