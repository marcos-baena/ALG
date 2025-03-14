#!/bin/bash

# ==========================================
# Script para testear quicksort
# ==========================================


./quicksort_script.sh

# ==========================================
# Generar gráficas con gnuplot
# ==========================================

echo ">>> Generando gráficas con gnuplot..."

# Carpeta de resultados
OUT_FOLDER="Graficas"
mkdir -p "$OUT_FOLDER"

# ================================
# Graficar cada algoritmo por separado
# ================================

gnuplot << EOF
set terminal png size 800,600
set output "${OUT_FOLDER}/Quicksort.png"
set title "Tiempo de ejecucion - Quicksort"
set xlabel "Tamano del caso"
set ylabel "Tiempo (microsegundos)"
set grid
plot "QuickSortDATA/medias.dat" using 1:2 with linespoints title "QuickSort"
EOF

gnuplot << EOF
set terminal png size 800,600
set output "${OUT_FOLDER}/Quicksort_escala_LOG.png"
set title "Tiempo de ejecucion - Quicksort"
set xlabel "Tamano del caso"
set ylabel "Tiempo (microsegundos)"
set grid
set logscale x
set logscale y
plot "QuickSortDATA/medias.dat" using 1:2 with linespoints title "QuickSort"
EOF

echo ">>> Graficas generadas en la carpeta ${OUT_FOLDER}/"
echo ">>> Proceso completo!"
