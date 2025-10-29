#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Definimos una constante para el máximo de caracteres en una palabra.
#define MAX_LONGITUD_PALABRA 256

// Función auxiliar para mostrar una guía de uso del programa.
void mostrarAyuda(const char *nombrePrograma) {
    printf("Este programa permite buscar y reemplazar palabras en un archivo de texto.\n");
    printf("- Uso:     %s <nombre_archivo> <palabra_a_buscar> <palabra_a_reemplazar>\n", nombrePrograma);
    printf("- Ejemplo: %s prueba.txt día noche\n\n", nombrePrograma);
}

// Función para procesar una palabra en el archivo que se está leyendo.
// NOTA: Para cada palabra leída en el archivo, esta función elimina temporalmente los signos de puntuación adyacentes y convierte la palabra a minúsculas, para facilitar la comparación con la palabra buscada. Finalmente, se devuelve la palabra procesada.
char *procesarPalabra(const char *palabraSinProcesar) {
    // Definimos una variable para almacenar la longitud de la palabra sin procesar.
    // NOTA: Esto nos ayudará a reservar memoria para la palabra procesada.
    int longitudEntrada = strlen(palabraSinProcesar);

    // Definimos una variable para almacenar la palabra procesada.
    // NOTA: Reservamos memoria dinámica para la palabra procesada, incluyendo el carácter nulo.
    char *palabraProcesada = malloc((longitudEntrada + 1) * sizeof(char));

    // Definimos una variable para controlar el índice de la palabra procesada.
    // NOTA: Esta variable se usa para controlar dónde se agrega el siguiente carácter en la palabra procesada.
    int indicePalabraProcesada = 0;

    // Verificamos que la memoria se haya reservado correctamente.
    if (palabraProcesada == NULL) {
        fprintf(stderr, "ERROR: No se pudo reservar memoria para procesar la palabra.\n");
        exit(1); // Detenemos la ejecución del programa con un código de error.
    }

    // Una vez reservada la memoria, procesamos la palabra.
    // NOTA: Usamos un índice separado para la palabra procesada, ya que la longitud puede ser menor que la de la palabra original debido a la eliminación de signos de puntuación.
    for (int i = 0; i < longitudEntrada; i++) {
        // Verificamos si el carácter actual es alfanumérico (ignoramos signos de puntuación).
        // NOTA: isalnum verifica si el carácter es alfanumérico (letra o número). Usamos unsigned char para castear y evitar comportamientos indefinidos con caracteres que son interpretados como negativos, como los acentos.
        if (isalnum((unsigned char)palabraSinProcesar[i])) {
            // Si es alfanumérico, lo convertimos a minúscula y lo agregamos a la palabra procesada.
            palabraProcesada[indicePalabraProcesada] = tolower((unsigned char)palabraSinProcesar[i]);
            indicePalabraProcesada++; // Incrementamos el índice de la palabra procesada.
        }
    }

    // Agregamos el carácter nulo al final de la palabra procesada.
    palabraProcesada[indicePalabraProcesada] = '\0';

    return palabraProcesada;
}

// Función principal
// NOTA: argc es el número de argumentos y argv es un arreglo de strings con los argumentos.
int main(int argc, char *argv[]) {
    // Verificamos que se hayan pasado exactamente 3 argumentos (además del nombre del programa).
    if (argc != 4) {
        printf("ERROR: Debe proporcionar exactamente 3 argumentos.\n");
        mostrarAyuda(argv[0]);
        return 1;
    }

    // Definimos tres variables para procesar los argumentos pasados al programa.
    const char *nombreArchivo = argv[1];
    const char *palabraBusqueda = argv[2];
    const char *palabraReemplazo = argv[3];

    // Abrimos el archivo especificado por el usuario en modo lectura y verificamos que se haya abierto correctamente.
    FILE *archivoEntrada = fopen(nombreArchivo, "r");
    if (archivoEntrada == NULL) {
        printf("ERROR: No se pudo abrir el archivo '%s'.\n", nombreArchivo);
        mostrarAyuda(argv[0]);
        return 1;
    }

    // Verificamos que la palabra a buscar no esté vacía.
    if (strlen(palabraBusqueda) == 0) {
        fprintf(stderr, "ERROR: La palabra a buscar no puede estar vacía.\n");
        mostrarAyuda(argv[0]);
        fclose(archivoEntrada); // Cerramos el archivo antes de detener la ejecución.
        return 1;
    }

    // Creamos (o abrimos) el archivo de salida en modo escritura y verificamos que se haya abierto correctamente.
    // NOTA: Esto sobrescribirá el archivo si ya existe.
    FILE *archivoSalida = fopen("archivoEditado.txt", "w");
    if (archivoSalida == NULL) {
        printf("ERROR: No se pudo crear o abrir el archivo de salida 'archivoEditado.txt'.\n");
        fclose(archivoEntrada); // Cerramos el archivo de entrada antes de detener la ejecución.
        return 1;
    }

    // Procesamos la palabra a buscar para compararla en minúsculas y sin signos de puntuación.
    char *busquedaProcesada = procesarPalabra(palabraBusqueda);

    // Definimos una variable para almacenar temporalmente cada palabra leída del archivo.
    char palabraLeida[MAX_LONGITUD_PALABRA];

    // Definimos una variable para almacenar temporalmente el índice de la palabra leída, que usaremos para construir la palabra carácter por carácter.
    int indicePalabraLeida = 0;

    // Definimos una variable para almacenar temporalmente el carácter actual leído del archivo.
    // NOTA: Usamos int en lugar de char para poder comparar con EOF correctamente.
    int caracterActual;

    // Leemos el archivo carácter por carácter para manejar correctamente los espacios, la puntuación y los saltos de línea.
    while ((caracterActual = fgetc(archivoEntrada)) != EOF) {
        // Si el carácter leído es alfanumérico, lo agregamos a la palabra leída, construyéndola carácter por carácter.
        if (isalnum((unsigned char)caracterActual)) {
            // Validamos que no excedamos el tamaño del buffer de la palabra leída.
            if (indicePalabraLeida >= sizeof(palabraLeida) - 1) {
                fprintf(stderr, "ERROR: La palabra en el archivo es demasiado larga.\n");
                fclose(archivoEntrada);
                fclose(archivoSalida);
                free(busquedaProcesada);
                return 1;
            }
            palabraLeida[indicePalabraLeida] = (char)caracterActual;
            indicePalabraLeida++;
        } else {
            // Si el carácter leído no es alfanumérico, significa que hemos llegado al final de una palabra, por lo que procesamos la palabra leída.
            // NOTA: Si el archivo no tiene palabras (si solo contiene espacios o puntuación), no hacemos nada.
            if (indicePalabraLeida > 0) {
                palabraLeida[indicePalabraLeida] = '\0'; // Agregamos el carácter nulo al final de la palabra leída.

                // Procesamos la palabra leída antes de compararla con la palabra de búsqueda.
                char *palabraProcesada = procesarPalabra(palabraLeida);

                // Comparamos con la palabra de búsqueda procesada.
                // NOTA: Usamos strcmp para comparar las cadenas. Si son iguales, strcmp devuelve 0.
                if (strcmp(palabraProcesada, busquedaProcesada) == 0) {
                    // Si coinciden, escribimos la palabra de reemplazo en el archivo de salida.
                    fprintf(archivoSalida, "%s", palabraReemplazo);
                } else {
                    // Si no coinciden, escribimos la palabra original en el archivo de salida.
                    fprintf(archivoSalida, "%s", palabraLeida);
                }
                // Liberamos la memoria asignada para la palabra procesada.
                free(palabraProcesada);

                // Reiniciamos el índice de la palabra leída para la siguiente palabra.
                indicePalabraLeida = 0;
            }
            // Una vez procesada la palabra, escribimos el carácter no alfanumérico actual (espacio, puntuación, salto de línea, etc.) directamente en el archivo de salida.
            fputc(caracterActual, archivoSalida);
        }
    }
    // Si al finalizar el while loop hay una palabra pendiente por procesar (en caso de que el archivo no termine con un carácter no alfanumérico), la procesamos aquí.
    if (indicePalabraLeida > 0) {
        palabraLeida[indicePalabraLeida] = '\0'; // Agregamos el carácter nulo al final de la palabra leída.
        char *palabraProcesada = procesarPalabra(palabraLeida);
        if (strcmp(palabraProcesada, busquedaProcesada) == 0) {
            fprintf(archivoSalida, "%s", palabraReemplazo);
        } else {
            fprintf(archivoSalida, "%s", palabraLeida);
        }
        free(palabraProcesada);
    }

    // Liberamos memoria y cerramos los archivos de entrada y salida al finalizar.
    free(busquedaProcesada);
    fclose(archivoEntrada);
    fclose(archivoSalida);

    printf("Archivo procesado exitosamente. Resultados guardados en 'archivoEditado.txt'\n\n");

    return 0;
}
