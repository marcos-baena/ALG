#!/bin/bash

# ===============================
# Script para medir tiempos de QuickSort
# ===============================

# Nombre del programa
PROGRAM="./bruteForce"

# Nombre de la carpeta de resultados
FOLDER="bruteForceDATA"

# Semilla pseudo-aleatoria cada vez
BASE_SEED=$(( $(date +%s) )) 

# Tamaños de casos desde 1000 hasta 100000 en pasos de 25000
sizes=()
for (( i=10; i<=400; i+=10 )); do
    sizes+=($i)
done

# ==========================
# Crear carpeta y limpiar
# ==========================

if [ -e "$FOLDER" ]; then
    if [ -d "$FOLDER" ]; then
        echo ">>> Carpeta $FOLDER ya existe. Limpiando archivos anteriores..."
        rm -f "$FOLDER"/salida*.dat
        rm -f "$FOLDER"/medias.dat
        echo ">>> Carpeta $FOLDER lista y limpia."
    else
        echo ">>> Existe un fichero llamado $FOLDER y no es una carpeta."
        echo ">>> Debes borrarlo o renombrarlo para continuar."
        exit 1
    fi
else
    mkdir "$FOLDER"
    echo ">>> Carpeta $FOLDER creada."
fi

# ==========================
# Ejecutar el programa 10 veces
# ==========================

echo ">>> Ejecutando $PROGRAM 10 veces con tamaños desde ${sizes[0]} hasta ${sizes[-1]}"

for run in {1..10}; do
    # Archivo de salida para esta corrida
    OUTPUT="$FOLDER/salida${run}.dat"

    # Usar una semilla distinta cada vez
    SEED=$((BASE_SEED + run))

    echo ">>> Iteración $run - Ejecutando $PROGRAM con semilla $SEED, guardando en $OUTPUT"

    # Ejecutar el programa
    $PROGRAM "$OUTPUT" "$SEED" "${sizes[@]}"

    echo ">>> Iteración terminada $run"
done

echo ">>> Todas las iteraciones han terminado."

# ==========================
# Calcular la media de los tiempos en medias.dat
# ==========================

echo ">>> Calculando la media de los tiempos en $FOLDER/medias.dat"

# Crear archivo de medias
OUTPUT_MEAN="$FOLDER/medias_fuera_bruta.dat"
> "$OUTPUT_MEAN" # Vaciamos el archivo si existe

NUM_FILES=10

# Usamos el primer archivo para obtener los tamaños de caso
while read -r line; do
    # Obtener el tamaño del caso
    tam_caso=$(echo "$line" | cut -d' ' -f1)

    # Sumar los tiempos de los 10 archivos para este tamaño
    suma=0
    for i in $(seq 1 $NUM_FILES); do
        file="$FOLDER/salida${i}.dat"
        tiempo=$(grep "^$tam_caso " "$file" | awk '{print $2}')
        suma=$((suma + tiempo))
    done

    # Calcular la media
    media=$((suma / NUM_FILES))

    # Guardar en el archivo de medias
    echo "$tam_caso $media" >> "$OUTPUT_MEAN"
done < "$FOLDER/salida1.dat"

echo ">>> Cálculo de medias finalizado. Guardado en $OUTPUT_MEAN"

