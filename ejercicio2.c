#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Función auxiliar para mostrar una guía de uso del programa.
void mostrar_ayuda(const char *nombre_programa) {
    printf("Uso: %s <nombre_archivo> <palabra_a_buscar> <palabra_a_reemplazar>\n", nombre_programa);
    printf("Ejemplo: %s prueba.txt día noche\n\n", nombre_programa);
}

// Función principal
// NOTA: argc es el número de argumentos y argv es un arreglo de strings con los argumentos.
int main(int argc, char *argv[]) {
    // Verificamos que se hayan pasado exactamente 4 argumentos (nombre del programa + 3 argumentos).
    if (argc != 4) {
        mostrar_ayuda(argv[0]);
        return 1; // Salimos con código de error 1.
    }

    // Definimos tres variables para procesar los argumentos pasados al programa.
    const char *nombreArchivo = argv[1];
    const char *palabraBuscada = argv[2];
    const char *reemplazoPalabra = argv[3];

    // Verificamos que la palabra a buscar no esté vacía.
    if (strlen(palabraBuscada) == 0) {
        fprintf(stderr, "Error: La palabra a buscar no puede estar vacía.\n");
        return 1;
    }
    
    return 0;
}
