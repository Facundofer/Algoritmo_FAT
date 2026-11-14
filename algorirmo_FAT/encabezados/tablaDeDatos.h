#ifndef DATOS_H
#define DATOS_H

struct Datos{
    char dato[11]; 
    int bloqueSiguiente;
};

typedef struct Datos tablaDatos;

void agregarDato(int cantidadDeBloques, char **datosEnBloques, int *vectorDeIndices);
char** separarEnBloques(char *datostring);
void eliminarDato(int posicion);
void mostrarContenido(int posicionInicial);

#endif