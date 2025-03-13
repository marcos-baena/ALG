#!/bin/bash

# Nombre del programa (asumiendo que se llama quicksort)
PROGRAM="./QuickSort"

# Archivo de salida
OUTPUT="salida.dat"

# Semilla aleatoria (puedes cambiarla)
SEED=57

# Tamaños de casos desde 1000 hasta 1000000 en pasos de 25000
sizes=()
for (( i=1000; i<=10000000; i+=15000 )); do
    sizes+=($i)
done

# Ejecutar el programa con los argumentos
$PROGRAM $OUTPUT $SEED "${sizes[@]}"



