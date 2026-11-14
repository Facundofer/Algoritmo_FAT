#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../encabezados/tablaIndice.h"
#include "../encabezados/tablaDeBits.h"
#include "../encabezados/tablaDeDatos.h"

#define TAMANIO_MAX 100

bloqueIndice tablaIndice[TAMANIO_MAX];

void inicializarTablaIndice(){
    for(int i = 0; i < TAMANIO_MAX; i++){
        tablaIndice[i].isBorrado = 1; // 1 = libre / borrado, 0 = ocupado
        tablaIndice[i].nombre[0] = '\0';
        tablaIndice[i].bloqueInicial = -1;
        tablaIndice[i].tamano = 0;
    }
}

bool verificarExistenciaArchivo(char *nombreArchivo){
    bool resultado = false;
    int i = 0;
    
    while(i < TAMANIO_MAX && !resultado){
        if(tablaIndice[i].isBorrado == 0 && strcmp(tablaIndice[i].nombre, nombreArchivo) == 0){
            resultado = true;
        }
        i++;
    }   
    return resultado;
}

bloqueIndice crearNuevoBloque(int cantidadDeBloques, char *nombreArchivo, char *datoArchivo){
    bloqueIndice unBloqueIndice;
    unBloqueIndice.isBorrado = 1; // Por defecto inválido hasta que se confirme todo

    // 1. Controlar que el archivo NO exista (negamos con !)
    if(!verificarExistenciaArchivo(nombreArchivo)){
        // 2. Controlar que haya espacio suficiente
        if(buscarEspacioParaDatos(cantidadDeBloques)){
            // Pedimos los índices libres y partimos el texto en bloques
            int *vectorIndices = solicitarEspacio(cantidadDeBloques);
            char **vectorBloques = separarEnBloques(datoArchivo);

            // Inicializamos los datos del bloque índice
            strcpy(unBloqueIndice.nombre, nombreArchivo);
            unBloqueIndice.bloqueInicial = vectorIndices[0];
            unBloqueIndice.tamano = cantidadDeBloques;
            unBloqueIndice.isBorrado = 0;

            // Guardamos el contenido en la tabla de datos y lo registramos en la tabla índice
            agregarDato(cantidadDeBloques, vectorBloques, vectorIndices);
            agregarBloque(unBloqueIndice);
            printf("Bloque grabado con exito.\n");

            // Liberamos la memoria dinámica auxiliar
            for(int i = 0; i < cantidadDeBloques; i++){
                free(vectorBloques[i]);
            }
            free(vectorBloques);
            free(vectorIndices);
        } else {
            printf("No hay suficiente espacio para este archivo.\n");
        }
    } else {
        printf("El archivo ya existe.\n");
    }

    return unBloqueIndice;
}

void agregarBloque(bloqueIndice unBloque){
    bool agregado = false;
    int i = 0;

    while(i < TAMANIO_MAX && !agregado){
        if(tablaIndice[i].isBorrado == 1){
            tablaIndice[i] = unBloque; 
            agregado = true;
        }
        i++;
    }

    if(agregado){
        printf("Bloque AGREGADO con exito.\n"); 
    } else {
        printf("Error: La tabla indice esta llena.\n");
    }
}

void eliminarArchivo(char *nombreArchivo){
    bool eliminado = false;
    int i = 0;

    while(i < TAMANIO_MAX && !eliminado){
        if(tablaIndice[i].isBorrado == 0 && strcmp(tablaIndice[i].nombre, nombreArchivo) == 0){
            tablaIndice[i].isBorrado = 1;
            eliminarDato(tablaIndice[i].bloqueInicial); // Libera los bloques en datos y bits
            eliminado = true;
        }
        i++;
    }

    if(eliminado){
        printf("Archivo '%s' eliminado con exito.\n", nombreArchivo);
    } else {
        printf("El archivo no existe.\n");
    }
}

void listarTablaIndice(){
    bool hayArchivos = false;
    printf("\n--- TABLA INDICE ---\n");
    for(int i = 0; i < TAMANIO_MAX; i++){
        if(tablaIndice[i].isBorrado == 0){
            printf("Archivo: %s | Bloque inicial: %d | Bloques: %d\n", 
                   tablaIndice[i].nombre, tablaIndice[i].bloqueInicial, tablaIndice[i].tamano);
            hayArchivos = true;
        }
    }
    if(!hayArchivos){
        printf("No hay archivos cargados en el sistema.\n");
    }
}

void mostarArchivoDeTabla(char *nombreArchivo){
    bool encontrado = false;
    int i = 0;

    while(i < TAMANIO_MAX && !encontrado){
        if(tablaIndice[i].isBorrado == 0 && strcmp(tablaIndice[i].nombre, nombreArchivo) == 0){
            printf("Tu archivo '%s' inicia en el bloque %d y tiene %d bloques.\n", 
                   tablaIndice[i].nombre, tablaIndice[i].bloqueInicial, tablaIndice[i].tamano);
            encontrado = true;
        }
        i++;
    }

    if(!encontrado){
        printf("El archivo no existe.\n");
    }else{
        mostrarContenido(tablaIndice[i -1].bloqueInicial);
    }
}