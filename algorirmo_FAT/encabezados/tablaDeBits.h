#ifndef BITS_H
#define BITS_H

#include <stdbool.h>

int* solicitarEspacio(int espacioSolicitado);
bool buscarEspacioParaDatos(int espacioSolicitado);
void agregarContenido(int posicion);
void borrarContenido(int posicion);
void mostrarTablaBits();

#endif