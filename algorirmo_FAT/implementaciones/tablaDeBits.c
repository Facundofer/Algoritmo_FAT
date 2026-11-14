#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../encabezados/tablaDeBits.h"

#define TAMANIO_MAX 100

int tablaBits[TAMANIO_MAX] = {0}; // 0 = libre, 1 = ocupado

int* solicitarEspacio(int espacioSolicitado){
    int* vectorDeIndices = (int*) malloc(espacioSolicitado * sizeof(int));
    int j = 0;
    int i = 0;

    while(i < TAMANIO_MAX && j < espacioSolicitado){
        if (tablaBits[i] == 0){
            tablaBits[i] = 1; // Marcamos como ocupado
            vectorDeIndices[j] = i;
            j++;
        }
        i++;
    }
    return vectorDeIndices;
}

bool buscarEspacioParaDatos(int espacioSolicitado){
    int j = 0;
    int i = 0;
    bool isDisponible = false;

    while(i < TAMANIO_MAX && j < espacioSolicitado){
        if (tablaBits[i] == 0){
            j++;
        } 
        i++;
    }
    if(j == espacioSolicitado){
        isDisponible = true;
    }
    return isDisponible;
}

void agregarContenido(int posicion){
    tablaBits[posicion] = 1; // 1 = ocupado
}

void borrarContenido(int posicion){
    tablaBits[posicion] = 0; // 0 = libre
}

void mostrarTablaBits(){
    printf("\n--- TABLA DE BITS (10x10) ---\n");
    for(int i = 0; i < 10; i++){
        printf("[%2d-%2d]: ", i * 10, i * 10 + 9);
        for(int j = 0; j < 10; j++){
            printf("%d ", tablaBits[i * 10 + j]);
        }
        printf("\n");
    }
}