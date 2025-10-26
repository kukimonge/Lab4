#include <stdio.h>

// Función para mostrar matrices.
void mostrarMatriz(int *matriz, int filas, int columnas) {
    // Recorremos cada fila 'i' de la matriz.
    for (int i = 0; i < filas; i++) {
        // Recorremos cada elemento (columna 'j') de cada fila y lo mostramos en pantalla.
        for (int j = 0; j < columnas; j++) {
            printf("%d ", *matriz++); // Usamos aritmética de punteros para acceder a los elementos de la matriz.
        }
        printf("\n");
    }
}

int main() {
    // Definimos una matriz de ejemplo.
    int matrizEjemplo[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    // Llamamos a la función para mostrar la matriz.
    mostrarMatriz(matrizEjemplo, 3, 4);

    return 0;
}
