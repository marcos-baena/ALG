#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <iostream>
#include <fstream> // Para usar ficheros
#include <vector>
#include <stack>
using namespace std;

void Hanoi(int n);
                  
void moveDisk(int a, int b);

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
        Hanoi(n);
        tf = chrono::high_resolution_clock::now();

        unsigned long tejecucion = chrono::duration_cast<chrono::microseconds>(tf - t0).count();
        cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso " << n << endl;

        // Guardamos tamaño de caso y t_ejecucion a fichero de salida
        fsalida << n << " " << tejecucion << "\n";
    }

    fsalida.close();
    return 0;
}


 
char rod[]={'S', 'A', 'D'};
vector<stack<int>> stacks(3); // 3 stacks for 3 rods
 
void moveDisk(int a, int b)
{
    if (!stacks[a].empty() && (stacks[b].empty() || stacks[a].top() < stacks[b].top()))
    {
        stacks[b].push(stacks[a].top());
        stacks[a].pop();
    }
}
 
void Hanoi(int n)
{
 
    int src = 0, aux = 1, dest = 2;
    for (int i = n; i > 0; i--)
        stacks[src].push(i);
 
    int totalMoves = (1 << n) - 1;
    if (n % 2 == 0)
        swap(aux, dest);
 
    for (int i = 1; i <= totalMoves; i++)
    {
        if (i % 3 == 0)
            moveDisk(aux, dest);
        else if (i % 3 == 1)
            moveDisk(src, dest);
        else
            moveDisk(src, aux);
    }
}
