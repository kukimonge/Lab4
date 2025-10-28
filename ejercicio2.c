#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Función auxiliar para mostrar una guía de uso del programa.
void mostrar_ayuda(const char *nombre_programa) {
    printf("- Uso:     %s <nombre_archivo> <palabra_a_buscar> <palabra_a_reemplazar>\n", nombre_programa);
    printf("- Ejemplo: %s prueba.txt día noche\n\n", nombre_programa);
}

// Función principal
// NOTA: argc es el número de argumentos y argv es un arreglo de strings con los argumentos.
int main(int argc, char *argv[]) {
    // Verificamos que se hayan pasado exactamente 3 argumentos (además del nombre del programa).
    if (argc != 4) {
        printf("Error: Debe proporcionar exactamente 3 argumentos.\n");
        mostrar_ayuda(argv[0]);
        return 1; // Detenemos la ejecución del programa con un código de error.
    }

    // Definimos tres variables para procesar los argumentos pasados al programa.
    const char *nombreArchivo = argv[1];
    const char *palabraBuscada = argv[2];

    // Abrimos el archivo especificado por el usuario en modo lectura.
    FILE *archivo = fopen(nombreArchivo, "r");
    // Verificamos que el archivo se haya abierto correctamente.
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo '%s'.\n", nombreArchivo);
        mostrar_ayuda(argv[0]);
        return 1; // Detenemos la ejecución del programa con un código de error.
    }

    // Verificamos que la palabra a buscar no esté vacía.
    if (strlen(palabraBuscada) == 0) {
        fprintf(stderr, "Error: La palabra a buscar no puede estar vacía.\n");
        mostrar_ayuda(argv[0]);
        fclose(archivo); // Cerramos el archivo antes de detener la ejecución.
        return 1; // Detenemos la ejecución del programa con un código de error.
    }

    // Creamos (o abrimos) el archivo de salida en modo escritura.
    // NOTA: Esto sobrescribirá el archivo si ya existe.
    FILE *archivoSalida = fopen("archivoEditado.txt", "w");
    if (archivoSalida == NULL) {
        printf("Error: No se pudo crear o abrir el archivo de salida 'archivoEditado.txt'.\n");
        fclose(archivo); // Cerramos el archivo de entrada antes de detener la ejecución.
        return 1; // Detenemos la ejecución del programa con un código de error.
    }

    // Cerramos el archivo de entrada y salida al finalizar.
    fclose(archivo);
    fclose(archivoSalida);

    return 0;
}
