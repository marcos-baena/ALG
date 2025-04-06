#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include <set>
using namespace std;

struct Point {
    double x, y;
};

// Overload operator< to use Point in std::set (sort by x, then y)
bool operator<(const Point &a, const Point &b) {
    return (a.x < b.x) || (a.x == b.x && a.y < b.y);
}

// Comparator for sorting points
bool cmpPoint(const Point &a, const Point &b) {
    if (a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}

// Utility function: cross product of OA and OB vectors
double cross(const Point &O, const Point &A, const Point &B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Merge two convex hulls into one convex hull
vector<Point> mergeHulls(const vector<Point> &leftHull, const vector<Point> &rightHull) {
    int n1 = leftHull.size(), n2 = rightHull.size();
    // Find the rightmost point of left hull and leftmost point of right hull
    int i = 0, j = 0;
    for (int k = 0; k < n1; k++) {
        if (leftHull[k].x > leftHull[i].x)
            i = k;
    }
    for (int k = 0; k < n2; k++) {
        if (rightHull[k].x < rightHull[j].x)
            j = k;
    }

    // Find upper tangent
    int upperI = i, upperJ = j;
    bool done = false;
    while (!done) {
        done = true;
        // Move rightHull index clockwise as long as the line is not an upper tangent
        while (cross(leftHull[upperI], rightHull[upperJ], rightHull[(upperJ + 1) % n2]) > 0)
            upperJ = (upperJ + 1) % n2;
        // Move leftHull index counterclockwise as long as the line is not an upper tangent
        while (cross(rightHull[upperJ], leftHull[upperI], leftHull[(n1 + upperI - 1) % n1]) < 0) {
            upperI = (n1 + upperI - 1) % n1;
            done = false;
        }
    }

    // Find lower tangent
    int lowerI = i, lowerJ = j;
    done = false;
    while (!done) {
        done = true;
        // Move rightHull index counterclockwise as long as the line is not a lower tangent
        while (cross(leftHull[lowerI], rightHull[lowerJ], rightHull[(n2 + lowerJ - 1) % n2]) < 0)
            lowerJ = (n2 + lowerJ - 1) % n2;
        // Move leftHull index clockwise as long as the line is not a lower tangent
        while (cross(rightHull[lowerJ], leftHull[lowerI], leftHull[(lowerI + 1) % n1]) > 0) {
            lowerI = (lowerI + 1) % n1;
            done = false;
        }
    }

    // Construct the merged hull by traversing from upper tangent to lower tangent
    vector<Point> merged;
    // Traverse left hull from upperI to lowerI (inclusive)
    int idx = upperI;
    merged.push_back(leftHull[idx]);
    while (idx != lowerI) {
        idx = (idx + 1) % n1;
        merged.push_back(leftHull[idx]);
    }
    // Traverse right hull from lowerJ to upperJ (inclusive)
    idx = lowerJ;
    merged.push_back(rightHull[idx]);
    while (idx != upperJ) {
        idx = (idx + 1) % n2;
        merged.push_back(rightHull[idx]);
    }
    return merged;
}

// Divide and Conquer convex hull routine
vector<Point> convexHullDC(vector<Point> &points, int l, int r) {
    // Base case: one point
    if (l == r) {
        return {points[l]};
    }
    // Base case: two points
    if (r - l == 1) {
        if (points[l].x == points[r].x && points[l].y == points[r].y)
            return {points[l]};
        return {points[l], points[r]};
    }
    int mid = (l + r) / 2;
    vector<Point> leftHull = convexHullDC(points, l, mid);
    vector<Point> rightHull = convexHullDC(points, mid + 1, r);
    return mergeHulls(leftHull, rightHull);
}

int main(int argc, char *argv[]) {
    vector<Point> points;
    int n, argumento;
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // To measure execution time
    unsigned long int semilla;
    ofstream fsalida;

    if (argc <= 3) {
        cerr << "\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
        cerr << argv[0] << " NombreFicheroSalida Semilla tamCaso1 tamCaso2 ... tamCasoN\n\n";
        return 0;
    }

    // Open output file
    fsalida.open(argv[1]);
    if (!fsalida.is_open()) {
        cerr << "Error: No se pudo abrir fichero para escritura " << argv[1] << "\n\n";
        return 0;
    }

    // Initialize random number generator with seed
    semilla = atoi(argv[2]);
    srand(semilla);

    // Process each test case size
    for (argumento = 3; argumento < argc; argumento++) {
        n = atoi(argv[argumento]);
        points.resize(n);

        // Generate random points in range [0, 100]
        for (int i = 0; i < n; i++) {
            points[i].x = rand() % 101;
            points[i].y = rand() % 101;
        }

        // Remove duplicate points using a set
        set<Point> setHull(points.begin(), points.end());
        points.assign(setHull.begin(), setHull.end());

        cerr << "Ejecutando divide and conquer para tam. caso: " << n << endl;
        t0 = chrono::high_resolution_clock::now();

        // Sort the points using the comparator
        sort(points.begin(), points.end(), cmpPoint);

        // Compute the convex hull using the Divide and Conquer algorithm
        vector<Point> hull = convexHullDC(points, 0, points.size()-1);
        tf = chrono::high_resolution_clock::now();

        // Remove potential duplicates from the resulting hull (if any) by using a set
        set<Point> setHull_final(hull.begin(), hull.end());

        unsigned long tejecucion = chrono::duration_cast<chrono::microseconds>(tf - t0).count();
        cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso " << n << endl;
        
        // Output the convex hull points
        for (auto it = setHull_final.begin(); it != setHull_final.end(); ++it){
            cout << it->x << "," << it->y << endl;
        }

        // Save test case size and execution time to the output file
        fsalida << n << " " << tejecucion << "\n";
    }
    return 0;
}
