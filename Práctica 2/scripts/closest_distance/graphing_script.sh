#!/bin/bash

# 1. Run the brute force script
echo "Running bruteForceCD.sh..."
./bruteForceCD.sh

# 3. Run the divide script
echo "Running divideCD.sh..."
./divideCD.sh

# Carpeta de resultados
OUT_FOLDER="Graficas"
mkdir -p "$OUT_FOLDER"

# 5. Use gnuplot to generate a comparison plot
gnuplot <<EOF
    set terminal png size 800,600
    set output "${OUT_FOLDER}/comparison_closest_distance.png"
    set title "Comparación de fuerza bruta y divide y vencerás"
    set xlabel "Tamaño vector"
    set ylabel "Tiempo (microsegundos)"
    set grid
    plot "./bruteForceCPDATA/medias_fuera_bruta.dat" using 1:2 with lines title "Brute Force", \
         "./divideAndConquerCDDATA/medias_divide_y_venceras.dat" using 1:2 with lines title "Divide"
EOF

echo ">>> Graficas generadas en la carpeta ${OUT_FOLDER}/"
echo ">>> Proceso completo!"

