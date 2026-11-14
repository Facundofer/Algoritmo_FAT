#ifndef INDICE_H
#define INDICE_H

#include <stdio.h>
#include <stdbool.h>

struct bloqueDatoIndice{
    char nombre[20];
    int bloqueInicial;
    int tamano;
    int isBorrado;
};

typedef struct bloqueDatoIndice bloqueIndice;

void inicializarTablaIndice();
bool verificarExistenciaArchivo(char *nombreArchivo);
bloqueIndice crearNuevoBloque(int cantidadDeBloques, char *nombreArchivo, char *datoArchivo);
void agregarBloque(bloqueIndice unBloque);
void eliminarArchivo(char *nombreArchivo);
void listarTablaIndice();
void mostarArchivoDeTabla(char *nombreArchivo);

#endif