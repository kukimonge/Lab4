#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Función para mostrar matrices.
void mostrarMatriz(int *matriz, int filas, int columnas) {
    // Recorremos cada fila 'i' de la matriz
    for (int i = 0; i < filas; i++) {
        // Recorremos cada elemento (columna 'j') de cada fila y lo mostramos en pantalla.
        for (int j = 0; j < columnas; j++) {
            printf("%d ", *(matriz + i * columnas + j)); // Usamos aritmética de punteros para acceder al elemento (i, j) y lo desreferenciamos para obtener su valor.
        }
        printf("\n");
    }
}

// Función para generar una matriz con números aleatorios.
void generarMatrizAleatoria(int *matriz, int filas, int columnas) {
    // Declaramos una variable para almacenar el total de elementos en la matriz.
    int numeroElementos = filas * columnas;
    // Recorremos cada elemento de la matriz pasada como puntero. La matriz se trata como un arreglo unidimensional de tamaño 'filas * columnas'.
    for (int i = 0; i < numeroElementos; i++) {
        // Desreferenciamos el puntero asociado al elemento actual y le asignamos un número aleatorio entre -99 y 99.
        *(matriz + i) = (rand() % 199) - 99;
    }
}

// Función para ordenar los elementos de una matriz, usando el algoritmo BubbleSort.
void ordenarMatriz(int *matriz, int filas, int columnas) {
    // Declaramos una variable para almacenar el total de elementos en la matriz.
    int numeroElementos = filas * columnas;
    // Declaramos una variable para verificar si se realizaron intercambios al recorrer el arreglo.
    int intercambio = 1;

    // Comparamos cada elemento del arreglo con cada uno de sus vecinos, hasta que no se realicen más intercambios.
    while (intercambio) {
        intercambio = 0;
        // Comparamos elementos adyacentes del arreglo 1D.
        for (int i = 0; i < numeroElementos - 1; i++) {
            // Si el elemento actual es mayor al siguiente, los intercambiamos.
            if (*(matriz + i) > *(matriz + i + 1)) {
                // Intercambiamos los elementos usando una variable temporal.
                int temp = *(matriz + i);
                *(matriz + i) = *(matriz + i + 1);
                *(matriz + i + 1) = temp;
                intercambio = 1;
            }
        }
    }
}

// Función principal
int main() {
    // Usamos la función 'srand' para definir la semilla usada al generar números aleatorios con la función 'rand'.
    srand(time(NULL));

    // Declaramos matrices de diferentes dimensiones y las inicializamos en cero.
    int matrizEjemplo1[3][4] = {0};
    int matrizEjemplo2[5][5] = {0};
    int matrizEjemplo3[6][2] = {0};

    // Llenamos las matrices con números aleatorios
    generarMatrizAleatoria(&matrizEjemplo1[0][0], 3, 4);
    generarMatrizAleatoria(&matrizEjemplo2[0][0], 5, 5);
    generarMatrizAleatoria(&matrizEjemplo3[0][0], 6, 2);

    // Mostramos las matrices generadas aleatoriamente
    printf("\nMatriz Ejemplo 1 (3x4) - Antes de ordenar:\n");
    mostrarMatriz(&matrizEjemplo1[0][0], 3, 4);
    printf("\nMatriz Ejemplo 2 (5x5) - Antes de ordenar:\n");
    mostrarMatriz(&matrizEjemplo2[0][0], 5, 5);
    printf("\nMatriz Ejemplo 3 (6x2) - Antes de ordenar:\n");
    mostrarMatriz(&matrizEjemplo3[0][0], 6, 2);

    return 0;
}
