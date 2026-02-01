# SolucionSumaArreglosParalela

## Descripción
Este proyecto implementa la suma de dos arreglos A y B de tamaño N, generando un arreglo C donde:
C[i] = A[i] + B[i]

La suma se realiza de manera paralela usando OpenMP con un `#pragma omp parallel for`.

## Herramientas
- C++
- OpenMP
- OnlineGDB (compilación con GCC)

## Compilación / Ejecución
En OnlineGDB se habilita OpenMP agregando el flag:
-fopenmp

## Parámetros probados
Se realizaron al menos 2 ejecuciones cambiando:
- Número de hilos (THREADS)
- Tamaño de chunk (CHUNK)
