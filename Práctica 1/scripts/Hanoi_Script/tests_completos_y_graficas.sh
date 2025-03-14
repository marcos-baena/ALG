#!/bin/bash

# ==========================================
# Script para testear en paralelo las 3 versiones de Hanoi
# y generar gráficas con gnuplot automáticamente
# ==========================================

SCRIPT="./hanoi_script.sh"

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

$SCRIPT IT &    # Iterativa en segundo plano
PID_IT=$!

$SCRIPT SP &    # Sin Pila en segundo plano
PID_SP=$!

# Esperamos a que terminen las 3 ejecuciones
wait $PID_RE
echo ">>> Finalizada versión Recursiva (RE)"

wait $PID_IT
echo ">>> Finalizada versión Iterativa (IT)"

wait $PID_SP
echo ">>> Finalizada versión Iterativa SP (SP)"

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
set output "${OUT_FOLDER}/HanoiRecursivo.png"
set title "Tiempo de ejecucion - Hanoi Recursivo"
set xlabel "Tamano del caso"
set ylabel "Tiempo (microsegundos)"
set grid
plot "HanoiRecursivoDATA/medias.dat" using 1:2 with linespoints title "Recursivo"
EOF

gnuplot << EOF
set terminal png size 800,600
set output "${OUT_FOLDER}/HanoiIterativo.png"
set title "Tiempo de ejecucion - Hanoi Iterativo"
set xlabel "Tamano del caso"
set ylabel "Tiempo (microsegundos)"
set grid
plot "HanoiIterativoDATA/medias.dat" using 1:2 with linespoints title "Iterativo"
EOF

gnuplot << EOF
set terminal png size 800,600
set output "${OUT_FOLDER}/HanoiIterativoSP.png"
set title "Tiempo de ejecucion - Hanoi Iterativo SP"
set xlabel "Tamano del caso"
set ylabel "Tiempo (microsegundos)"
set grid
plot "HanoiIterativoSPDATA/medias.dat" using 1:2 with linespoints title "Iterativo SP"
EOF

gnuplot << EOF
set terminal png size 800,600
set output "${OUT_FOLDER}/HanoiRecursivo_LOG_SCALE.png"
set title "Tiempo de ejecucion - Hanoi Recursivo"
set xlabel "Tamano del caso"
set ylabel "Tiempo (microsegundos)"
set grid
set logscale y
plot "HanoiRecursivoDATA/medias.dat" using 1:2 with linespoints title "Recursivo"
EOF

gnuplot << EOF
set terminal png size 800,600
set output "${OUT_FOLDER}/HanoiIterativo_LOG_SCALE.png"
set title "Tiempo de ejecucion - Hanoi Iterativo"
set xlabel "Tamano del caso"
set ylabel "Tiempo (microsegundos)"
set grid
set logscale y
plot "HanoiIterativoDATA/medias.dat" using 1:2 with linespoints title "Iterativo"
EOF

gnuplot << EOF
set terminal png size 800,600
set output "${OUT_FOLDER}/HanoiIterativoSP_LOG_SCALE.png"
set title "Tiempo de ejecucion - Hanoi Iterativo SP"
set xlabel "Tamano del caso"
set ylabel "Tiempo (microsegundos)"
set grid
set logscale y
plot "HanoiIterativoSPDATA/medias.dat" using 1:2 with linespoints title "Iterativo SP"
EOF

# ================================
# Graficar comparativa en una sola gráfica
# ================================

gnuplot << EOF
set terminal png size 800,600
set output "${OUT_FOLDER}/ComparativaHanoi.png"
set title "Comparativa Tiempo de Ejecucion - Hanoi"
set xlabel "Tamano del caso"
set ylabel "Tiempo (microsegundos)"
set grid
plot \
    "HanoiRecursivoDATA/medias.dat" using 1:2 with linespoints title "Recursivo", \
    "HanoiIterativoDATA/medias.dat" using 1:2 with linespoints title "Iterativo", \
    "HanoiIterativoSPDATA/medias.dat" using 1:2 with linespoints title "Iterativo SP"
EOF

gnuplot << EOF
set terminal png size 800,600
set output "${OUT_FOLDER}/ComparativaHanoi_LOGSCALE.png"
set title "Comparativa Tiempo de Ejecucion - Hanoi"
set xlabel "Tamano del caso"
set ylabel "Tiempo (microsegundos)"
set grid
set logscale y
plot \
    "HanoiRecursivoDATA/medias.dat" using 1:2 with linespoints title "Recursivo", \
    "HanoiIterativoDATA/medias.dat" using 1:2 with linespoints title "Iterativo", \
    "HanoiIterativoSPDATA/medias.dat" using 1:2 with linespoints title "Iterativo SP"
EOF

echo ">>> Graficas generadas en la carpeta ${OUT_FOLDER}/"
echo ">>> Todo terminado."

