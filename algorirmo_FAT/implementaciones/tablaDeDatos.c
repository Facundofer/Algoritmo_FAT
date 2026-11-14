#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../encabezados/tablaDeDatos.h"
#include "../encabezados/tablaDeBits.h"

#define TAMANIO_MAX 100

tablaDatos vectordeDatos[TAMANIO_MAX]  = {0};


/*void crearTablaDeDatos(){
    tablaDatos vectordeDatos[TAMANIO_MAX];
}*/




void agregarDato(int cantidadDeBloques, char **datosEnBloques, int *vectorDeIndices){
    for (int i = 0; i < cantidadDeBloques; i++) {
        // Copiamos el bloque de texto en el dato de la tabla
        strcpy(vectordeDatos[vectorDeIndices[i]].dato, datosEnBloques[i]);
        
        // Si no es el último bloque, lo enlazamos con el índice que sigue
        if (i < cantidadDeBloques - 1) {
            vectordeDatos[vectorDeIndices[i]].bloqueSiguiente = vectorDeIndices[i + 1];
        } else {
            // Es el último bloque, no hay siguiente
            vectordeDatos[vectorDeIndices[i]].bloqueSiguiente = -1;
        }
    }
}

//hacer una funcion de separarBloques para llamar desde tablaIndice
char** separarEnBloques(char *datostring){
    int longitud = strlen(datostring);
    char bloque[11];    
    int cantidadBloques = (longitud + 9) / 10; // Calcula el total redondeando hacia arriba
    if (cantidadBloques == 0) cantidadBloques = 1;
    char** vectorBloquesDatos = (char**) malloc(cantidadBloques * sizeof(char*)); //tengo que usar malloc para no perder la info una vez fuera de la funcion
    
    /*if((longitud % 10) != 0 ){
        cantidadBloques = (longitud / 10) +1;    
    }
    else cantidadBloques = longitud / 10;*/

    //char vectorBloquesDatos[(cantidadBloques)];
    
    /*for (int i = 0; i < longitud; i += 10) {
        
        strncpy(bloque, &datostring[i], 10); 
        bloque[10] = '\0'; 
    
        if (longitud - i < 10) {
            bloque[longitud - i] = '\0';
        }
        strcpy(vectorBloquesDatos[i], bloque);
        //vectorBloquesDatos[i] = bloque;
    }*/

    int j = 0;
    for (int i = 0; i < longitud; i += 10) {
        // Reservamos espacio para los 10 caracteres + '\0' de este bloque
        vectorBloquesDatos[j] = (char*) malloc(11 * sizeof(char));
        

        strncpy(vectorBloquesDatos[j], &datostring[i], 10);
        vectorBloquesDatos[j][10] = '\0'; 
        j++;
    }
    return vectorBloquesDatos;
}


//AGREGUE FUNCION NUVEVA ELIMINAR DATO LOGICO
void eliminarDato(int posicion){
    int i = posicion;
    while(vectordeDatos[i].bloqueSiguiente != -1){
        i = posicion;
        borrarContenido(posicion);
        posicion = vectordeDatos[i].bloqueSiguiente;
    }
    borrarContenido(posicion);
}


void mostrarContenido(int posicionInicial){
    int i = posicionInicial;
    while(i != -1){
        printf("%s ", vectordeDatos[i].dato);
        i = vectordeDatos[i].bloqueSiguiente;
    }
}
