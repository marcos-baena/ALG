#!/bin/bash

# ===============================
# Script para medir tiempos de Hanoi
# ===============================

# Chequear que el usuario haya pasado el parámetro de algoritmo
if [ "$#" -ne 1 ]; then
    echo "Uso: $0 [RE|IT|SP]"
    echo "  RE -> HanoiRecursivo"
    echo "  IT -> HanoiIterativo"
    echo "  SP -> HanoiIterativoSP"
    exit 1
fi

# Parámetro del usuario: qué programa ejecutar
modo="$1"

# Decidir el ejecutable según el modo
case "$modo" in
    RE)
        PROGRAM="./HanoiRecursivo"
        FOLDER="HanoiRecursivoData"
        ;;
    IT)
        PROGRAM="./HanoiIterativo"
        FOLDER="HanoiIterativoData"
        ;;
    SP)
        PROGRAM="./HanoiIterativoSP"
        FOLDER="HanoiIterativoSPData"
        ;;
    *)
        echo "Modo no reconocido: $modo"
        echo "Usa RE (Recursivo), IT (Iterativo) o SP (IterativoSP)"
        exit 1
        ;;
esac

# ======================
# Variables base
# ======================

BASE_SEED=47

# Tamaños de los casos: de 5 a 50, en incrementos de 5
sizes=()
for (( i=5; i<=30; i+=3 )); do
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
# Ejecución de 10 iteraciones
# ==========================

echo ">>> Ejecutando $PROGRAM 10 veces con tamaños de ${sizes[0]} a ${sizes[-1]}"

for run in {1..10}; do
    OUTPUT="$FOLDER/salida${run}.dat"
    SEED=$((BASE_SEED + run))

    echo ">>> Iteración $run - Ejecutando $PROGRAM con semilla $SEED, guardando en $OUTPUT"

    $PROGRAM $OUTPUT $SEED "${sizes[@]}"

    echo ">>> Terminada iteración $run"
done

echo ">>> Todas las iteraciones han terminado."

# ==========================
# Cálculo de medias
# ==========================

MEDIA_FILE="$FOLDER/medias.dat"

echo ">>> Calculando medias y guardando en $MEDIA_FILE"
> "$MEDIA_FILE"

for size in "${sizes[@]}"; do
    sum=0
    count=0

    for run in {1..10}; do
        file="$FOLDER/salida${run}.dat"
        time=$(awk -v sz="$size" '$1 == sz {print $2}' "$file")

        if [[ ! -z "$time" ]]; then
            sum=$((sum + time))
            count=$((count + 1))
        fi
    done

    if [[ $count -gt 0 ]]; then
        avg=$((sum / count))
        echo "$size $avg" >> "$MEDIA_FILE"
    fi
done

echo ">>> Media de tiempos calculada en $MEDIA_FILE"
echo ">>> Proceso completo para $PROGRAM. Archivos en la carpeta $FOLDER"

