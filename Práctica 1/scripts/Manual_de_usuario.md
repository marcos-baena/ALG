# Manual de usuario de los scripts:

## Requisitos previos:

1. Tener compilados los programas Hanoi, Catalan y QuickSort en el mismo directorio que sus respectivos scripts:

- ./HanoiRecursivo
- ./HanoiIterativo
- ./HanoiIterativoSP

- ./NumerosCatalanRecursivo
- ./NumerosCatalanBC
- ./NumerosCatalanPD

- ./QuickSort

2. Tener instalado **gnuplot** si se quiere generar gráficos:

```bash
sudo apt install gnuplot
```

# SCRIPT 1: *hanoi_script.sh*

Qué hace:

- Ejecuta 10 pruebas del programa de Hanoi que elijas (Recursivo, Iterativo o IterativoSP).
- Guarda los resultados (salida1.dat a salida10.dat) en una carpeta con el nombre del programa:
    - HanoiRecursivoDATA/
    - HanoiIterativoDATA/
    - HanoiIterativoSPDATA/
- Calcula la media de tiempos y la guarda en medias.dat dentro de la carpeta correspondiente.

### Cómo se usa:

```bash
./run_hanoi.sh [modo]
```

Modos disponibles:

**RE**   -> HanoiRecursivo

**IT**   -> HanoiIterativo

**SP**   -> HanoiIterativoSP

Ejemplos:

./run_hanoi.sh RE   # Ejecuta HanoiRecursivo

./run_hanoi.sh IT   # Ejecuta HanoiIterativo

./run_hanoi.sh SP   # Ejecuta HanoiIterativoSP

# SCRIPT 2: *tests_completos_y_grafica.sh*

Qué hace:

- Ejecuta las tres variantes de Hanoi (RE, IT, SP) en paralelo, aprovechando los núcleos del procesador.
- Una vez terminadas las ejecuciones, genera gráficas automáticas con gnuplot:
    - Una gráfica por algoritmo.
    - Una gráfica comparativa de las tres versiones.

### Cómo se usa:

```bash
./*tests_completos_y_grafica.sh*
```

### Qué genera:

- Carpetas con los **resultados**:
    - HanoiRecursivoDATA/
    - HanoiIterativoDATA/
    - HanoiIterativoSPDATA/

- Carpeta de **gráficas**:
    - Graficas/HanoiRecursivo.png
    - Graficas/HanoiIterativo.png
    - Graficas/HanoiIterativoSP.png
    - Graficas/ComparativaHanoi.png

---

---

# SCRIPT 3: catalan_script*.sh*

Qué hace:

- Ejecuta 10 pruebas del programa de Números de Catalan que elijas (Recursivo, Binomial o PD).
- Guarda los resultados (salida1.dat a salida10.dat) en una carpeta con el nombre del programa:
    - CatalanRecursivoDATA/
    - CatalanBinomialDATA/
    - CatalanPDDATA/
- Calcula la media de tiempos y la guarda en medias.dat dentro de la carpeta correspondiente.

### Cómo se usa:

```bash
./catalan_script.sh [modo]
```

Modos disponibles:

**RE**   -> CatalanRecursivo

**BC**  -> CatalanBinomial

**PD**   -> CatalanPD

Ejemplos:

./catalan_script.sh RE   # Ejecuta CatalanRecursivo

./catalan_script.sh BC   # Ejecuta CatalanBinomial

./catalan_script.sh PD   # Ejecuta CatalanPD

# SCRIPT 4: *tests_completos_y_grafica.sh*

Qué hace:

- Ejecuta las tres variantes de Catalan (RE, BC, PD) en paralelo, aprovechando los núcleos del procesador.
- Una vez terminadas las ejecuciones, genera gráficas automáticas con gnuplot:
    - Una gráfica por algoritmo.
    - Una gráfica comparativa de las tres versiones.

### Cómo se usa:

```bash
./*tests_completos_y_grafica.sh*
```

### Qué genera:

- Carpetas con los **resultados**:
    - CatalanRecursivoDATA/
    - CatalanBinomialDATA/
    - CatalanPDDATA/
- Carpeta de **gráficas**:
    - Graficas/CatalanRecursivo.png
    - Graficas/CatalanBinomial.png
    - Graficas/CatalanPD.png
    - Graficas/ComparativaCatalan.png

---

---

# SCRIPT 5: *quicksort_script.sh*

Qué hace:

- Ejecuta 10 pruebas del programa QuickSort para vectores de tamaño 1000 a 100000, incrementando de 25000 en 25000.
- Guarda los resultados en la carpeta QuickSortDATA/:
    - salida1.dat a salida10.dat
    - medias.dat con la media de los tiempos.

### Cómo se usa:

```bash
./run_quicksort.sh
```

### Qué genera:

- Carpeta QuickSortDATA/ con todos los archivos:
    - salida1.dat ... salida10.dat
    - medias.dat

# SCRIPT 6: *graphing_script.sh*

Qué hace:

- Llama al script quicksort_script.sh y genera una gráfica usando gnuplot, que almacena en:
    - Graficas/QuickSort.png

---

---

---

# ESTRUCTURA DE CARPETAS GENERADAS

./

├── HanoiRecursivoDATA/

│   ├── salida1.dat

│   ├── ...

│   └── medias.dat

├── HanoiIterativoDATA/

│   ├── salida1.dat

│   ├── ...

│   └── medias.dat

├── HanoiIterativoSPDATA/

│   ├── salida1.dat

│   ├── ...

│   └── medias.dat

├── CatalanRecursivoDATA/

│   ├── salida1.dat

│   ├── ...

│   └── medias.dat

├── CatalanBinomialDATA/

│   ├── salida1.dat

│   ├── ...

│   └── medias.dat

├── CatalanPDDATA/

│   ├── salida1.dat

│   ├── ...

│   └── medias.dat

├── QuickSortDATA/

│   ├── salida1.dat

│   ├── ...

│   └── medias.dat

├── Graficas/

│   ├── HanoiRecursivo.png

│   ├── HanoiIterativo.png

│   ├── HanoiIterativoSP.png

│   └── ComparativaHanoi.png

│

│   ├── CatalanRecursivo.png

│   ├── CatalanBinomial.png

│   ├── CatalanPD.png

│   └── ComparativaCatalan.png

│

├── hanoi_script.sh

├── tests_completos_y_graficas.sh

│

├── cataln_script.sh

├── tests_completos_y_graficas.sh

│

├── quicksort_script.sh

└── graphing_script.sh

---

---

# NOTAS IMPORTANTES

- Semillas aleatorias: los scripts generan una semilla diferente en cada ejecución, usando la hora del sistema.
- Si quieres reproducir una ejecución concreta, puedes fijar tú mismo la semilla editando los scripts.
- Tiempo de ejecución: puede variar según tu máquina. Si usas el script paralelo (test_todas_versiones.sh), asegúrate de no saturar otros procesos en el equipo.