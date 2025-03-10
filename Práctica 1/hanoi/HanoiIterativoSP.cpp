#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <iostream>
#include <fstream> // Para usar ficheros
#include <vector>
#include <climits>
#include <cmath>

using namespace std;

struct Stack {
    unsigned capacity;
    int top;
    int *array;
};

// Funciones de la pila
struct Stack* createStack(unsigned capacity);
void push(struct Stack *stack, int item);
int pop(struct Stack* stack);
bool isEmpty(struct Stack* stack);
void moveDisksBetweenTwoPoles(struct Stack *src, struct Stack *dest, char s, char d);
void tohIterative(int num_of_disks, struct Stack *src, struct Stack *aux, struct Stack *dest);

int main(int argc, char *argv[]) {
    if (argc <= 3) {
        cerr << "\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
        cerr << argv[0] << " NombreFicheroSalida Semilla tamCaso1 tamCaso2 ... tamCasoN\n\n";
        return 1;
    }

    ofstream fsalida(argv[1]);
    if (!fsalida.is_open()) {
        cerr << "Error: No se pudo abrir fichero para escritura " << argv[1] << "\n\n";
        return 1;
    }

    unsigned long int semilla = atoi(argv[2]);
    srand(semilla);

    for (int argumento = 3; argumento < argc; argumento++) {
        int num_of_disks = atoi(argv[argumento]);

        cout << "Ejecutando Hanoi para tam. caso: " << num_of_disks << endl;

        struct Stack *src = createStack(num_of_disks);
        struct Stack *aux = createStack(num_of_disks);
        struct Stack *dest = createStack(num_of_disks);

        auto t0 = chrono::high_resolution_clock::now();
        tohIterative(num_of_disks, src, aux, dest);
        auto tf = chrono::high_resolution_clock::now();

        unsigned long tejecucion = chrono::duration_cast<chrono::microseconds>(tf - t0).count();
        cout << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso " << num_of_disks << endl;

        fsalida << num_of_disks << " " << tejecucion << "\n";

        // Liberar memoria
        free(src->array); free(src);
        free(aux->array); free(aux);
        free(dest->array); free(dest);
    }

    fsalida.close();
    return 0;
}

// Función para crear una pila
struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

// Funciones auxiliares de la pila
void push(struct Stack *stack, int item) {
    if (stack->top < (int)stack->capacity - 1)
        stack->array[++stack->top] = item;
}

int pop(struct Stack* stack) {
    return isEmpty(stack) ? INT_MIN : stack->array[stack->top--];
}

bool isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Función para mover discos entre dos pilas
void moveDisksBetweenTwoPoles(struct Stack *src, struct Stack *dest, char s, char d) {
    int pole1TopDisk = pop(src);
    int pole2TopDisk = pop(dest);

    if (pole1TopDisk == INT_MIN) {
        push(src, pole2TopDisk);
    } else if (pole2TopDisk == INT_MIN) {
        push(dest, pole1TopDisk);
    } else if (pole1TopDisk > pole2TopDisk) {
        push(src, pole1TopDisk);
        push(src, pole2TopDisk);
    } else {
        push(dest, pole2TopDisk);
        push(dest, pole1TopDisk);
    }
}

// Implementación iterativa de la Torre de Hanói
void tohIterative(int num_of_disks, struct Stack *src, struct Stack *aux, struct Stack *dest) {
    char s = 'S', d = 'D', a = 'A';
    if (num_of_disks % 2 == 0) swap(d, a);

    int total_num_of_moves = pow(2, num_of_disks) - 1;
    for (int i = num_of_disks; i >= 1; i--) push(src, i);

    for (int i = 1; i <= total_num_of_moves; i++) {
        if (i % 3 == 1) moveDisksBetweenTwoPoles(src, dest, s, d);
        else if (i % 3 == 2) moveDisksBetweenTwoPoles(src, aux, s, a);
        else moveDisksBetweenTwoPoles(aux, dest, a, d);
    }
}

