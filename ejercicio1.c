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
    int total = filas * columnas;
    // Recorremos cada elemento de la matriz pasada como puntero. La matriz se trata como un arreglo unidimensional de tamaño 'filas * columnas'.
    for (int i = 0; i < total; i++) {
        // Desreferenciamos el puntero asociado al elemento actual y le asignamos un número aleatorio entre -99 y 99.
        *(matriz + i) = (rand() % 199) - 99;
    }
}

// Función principal
int main() {
    // Usamos la función 'srand' para definir la semilla usada al generar números aleatorios con la función 'rand'.
    srand(time(NULL));

    // Declaramos una matriz de 3 filas y 4 columnas inicializada en cero, y la llenamos con números aleatorios usando la función generarMatrizAleatoria.
    int matrizEjemplo1[3][4] = {0};
    generarMatrizAleatoria(&matrizEjemplo1[0][0], 3, 4);
    mostrarMatriz(&matrizEjemplo1[0][0], 3, 4);

    return 0;
}
