#!/bin/bash

# ==========================================
# Script para testear en paralelo las 3 versiones de Hanoi
# y generar gráficas con gnuplot automáticamente
# ==========================================

SCRIPT="./catalan_script.sh"

# Comprobamos si el script principal existe
if [ ! -f "$SCRIPT" ]; then
    echo ">>> Error: No se encuentra el script $SCRIPT"
    exit 1
fi

# ==========================================
# Ejecutar las 3 versiones en paralelo
# ==========================================

echo ">>> Ejecutando las 3 versiones de Hanoi en paralelo..."

$SCRIPT RE &    # Recursiva en segundo plano
PID_RE=$!

$SCRIPT BC &    # Iterativa en segundo plano
PID_IT=$!

$SCRIPT PD &    # IterativaSP en segundo plano
PID_PD=$!

# Esperamos a que terminen las 3 ejecuciones
wait $PID_RE
echo ">>> Finalizada versión Recursiva (RE)"

wait $PID_IT
echo ">>> Finalizada versión Binomial (Bi)"

wait $PID_PD
echo ">>> Finalizada versión PD"

echo ">>> Todas las ejecuciones han terminado."

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
set output "${OUT_FOLDER}/CatalanRecursivo.png"
set title "Tiempo de ejecucion - Catalan Recursivo"
set xlabel "Tamano del caso"
set ylabel "Tiempo (microsegundos)"
set grid
plot "CatalanRecursivoDATA/medias.dat" using 1:2 with linespoints title "Recursivo"
EOF

gnuplot << EOF
set terminal png size 800,600
set output "${OUT_FOLDER}/CatalanBinomial.png"
set title "Tiempo de ejecucion - Catalan Binomial"
set xlabel "Tamano del caso"
set ylabel "Tiempo (microsegundos)"
set grid
plot "CatalanBinomialDATA/medias.dat" using 1:2 with linespoints title "Binomial"
EOF

gnuplot << EOF
set terminal png size 800,600
set output "${OUT_FOLDER}/CatalanPD.png"
set title "Tiempo de ejecucion - Catalan PD"
set xlabel "Tamano del caso"
set ylabel "Tiempo (microsegundos)"
set grid
plot "CatalanPDDATA/medias.dat" using 1:2 with linespoints title "PD"
EOF

# ================================
# Graficar comparativa en una sola gráfica
# ================================

gnuplot << EOF
set terminal png size 800,600
set output "${OUT_FOLDER}/ComparativaCatalan.png"
set title "Comparativa Tiempo de Ejecucion - Catalan"
set xlabel "Tamano del caso"
set ylabel "Tiempo (microsegundos)"
set grid
plot \
    "CatalanRecursivoDATA/medias.dat" using 1:2 with linespoints title "Recursivo", \
    "CatalanBinomialDATA/medias.dat" using 1:2 with linespoints title "Binomial", \
    "CatalanPDDATA/medias.dat" using 1:2 with linespoints title "PD"
EOF

echo ">>> Graficas generadas en la carpeta ${OUT_FOLDER}/"
echo ">>> Proceso completo!"

