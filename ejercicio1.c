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

// Función para llenar una matriz con números aleatorios.
void llenarMatriz(int *matriz, int filas, int columnas) {
    // Declaramos una variable para almacenar el total de elementos en la matriz.
    int numeroElementos = filas * columnas;

    // Recorremos cada elemento de la matriz pasada como puntero. La matriz se trata como un arreglo unidimensional de tamaño 'filas * columnas'.
    for (int i = 0; i < numeroElementos; i++) {
        *(matriz + i) = (rand() % 199) - 99; // Desreferenciamos el puntero asociado al elemento actual y le asignamos un número aleatorio entre -99 y 99, usando la función 'rand'.
    }
}

// Función para ordenar los elementos de una matriz, usando el algoritmo BubbleSort.
void ordenarMatriz(int *matriz, int filas, int columnas) {
    // Declaramos una variable para almacenar el total de elementos en la matriz.
    int numeroElementos = filas * columnas;

    // Declaramos una variable para verificar si se realizaron intercambios al recorrer el arreglo, y la inicializamos en 1 para entrar al 'while'.
    int intercambio = 1;

    // Usamos un ciclo 'while' que se ejecuta mientras se realicen intercambios en el arreglo (es decir, mientras no esté ordenado).
    while (intercambio != 0) {
        intercambio = 0; // Reiniciamos la variable de intercambio a 0 al inicio de cada recorrido, lo que indica que no se han realizado intercambios aún.

        // Recorremos cada elemento del arreglo, excepto el último (ya que no tiene vecino a la derecha). [3 6 1 5]
        for (int i = 0; i < numeroElementos - 1; i++) {
            // Si el elemento actual es mayor que su vecino, los intercambiamos.
            if (*(matriz + i) > *(matriz + i + 1)) {
                // Realizamos el intercambio usando una variable temporal.
                int temp = *(matriz + i);
                *(matriz + i) = *(matriz + i + 1); // Asignamos el valor del vecino al elemento actual.
                *(matriz + i + 1) = temp; // Asignamos el valor temporal (original del elemento actual) al vecino.
                intercambio = 1; // Indicamos que se realizó un intercambio.
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
    llenarMatriz(&matrizEjemplo1[0][0], 3, 4);
    llenarMatriz(&matrizEjemplo2[0][0], 5, 5);
    llenarMatriz(&matrizEjemplo3[0][0], 6, 2);

    // Mostramos las matrices generadas aleatoriamente
    printf("\nMatriz Ejemplo 1 (3x4) - Antes de ordenar:\n");
    mostrarMatriz(&matrizEjemplo1[0][0], 3, 4);
    printf("\nMatriz Ejemplo 2 (5x5) - Antes de ordenar:\n");
    mostrarMatriz(&matrizEjemplo2[0][0], 5, 5);
    printf("\nMatriz Ejemplo 3 (6x2) - Antes de ordenar:\n");
    mostrarMatriz(&matrizEjemplo3[0][0], 6, 2);

    // Ordenamos las matrices
    ordenarMatriz(&matrizEjemplo1[0][0], 3, 4);
    ordenarMatriz(&matrizEjemplo2[0][0], 5, 5);
    ordenarMatriz(&matrizEjemplo3[0][0], 6, 2);

    printf("\n====================================\n");

    // Mostramos las matrices ordenadas
    printf("\nMatriz Ejemplo 1 (3x4) - Después de ordenar:\n");
    mostrarMatriz(&matrizEjemplo1[0][0], 3, 4);
    printf("\nMatriz Ejemplo 2 (5x5) - Después de ordenar:\n");
    mostrarMatriz(&matrizEjemplo2[0][0], 5, 5);
    printf("\nMatriz Ejemplo 3 (6x2) - Después de ordenar:\n");
    mostrarMatriz(&matrizEjemplo3[0][0], 6, 2);
    printf ("\n");

    // Finalizamos el programa con un valor de retorno 0 para indicar que se ejecutó correctamente.
    return 0;
}
