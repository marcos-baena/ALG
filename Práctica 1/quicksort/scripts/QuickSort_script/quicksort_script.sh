#!/bin/bash

# Nombre del programa 
PROGRAM="./QuickSort"

# Semilla aleatoria base 
BASE_SEED=57

# Tamaños de casos desde 1000 hasta 1000000 en pasos de 25000
sizes=()
for (( i=1000; i<=1000000; i+=25000 )); do
    sizes+=($i)
done

# Ejecutar el programa 10 veces
for run in {1..10}; do
    # Archivo de salida para esta corrida
    OUTPUT="salida${run}.dat"
    
    # Usar una semilla distinta cada vez
    SEED=$((BASE_SEED + run))
    
    echo ">>> Ejecutando corrida $run con semilla $SEED, guardando en $OUTPUT"
    
    # Ejecutar el programa
    $PROGRAM $OUTPUT $SEED "${sizes[@]}"
    
    echo ">>> Terminada corrida $run"
done

echo ">>> Todas las corridas han terminado."

# --------------------------------------------------
# Calcular la media de los tiempos en medias.dat
# --------------------------------------------------

echo ">>> Calculando la media de los tiempos en medias.dat"

# Crear archivo de salida
OUTPUT_MEAN="medias.dat"
> "$OUTPUT_MEAN" # Vaciamos el archivo si existe

# Usamos el primer archivo para obtener los tamaños de caso
NUM_FILES=10

# Leer línea por línea del primer archivo
while read -r line; do
    # Obtener el tamaño del caso
    tam_caso=$(echo "$line" | cut -d' ' -f1)
    
    # Sumar los tiempos de los 10 archivos para este tamaño
    suma=0
    for i in $(seq 1 $NUM_FILES); do
        tiempo=$(grep "^$tam_caso " "salida${i}.dat" | awk '{print $2}')
        suma=$((suma + tiempo))
    done
    
    # Calcular la media
    media=$((suma / NUM_FILES))
    
    # Guardar en el archivo de medias
    echo "$tam_caso $media" >> "$OUTPUT_MEAN"
done < salida1.dat

echo ">>> Cálculo de medias finalizado. Guardado en $OUTPUT_MEAN"

