#include <stdio.h>
#include <string.h>
#include "encabezados/tablaDeDatos.h"
#include "encabezados/tablaIndice.h"
#include "encabezados/tablaDeBits.h"

int main(){
    int opcion = 0;
    char nombreArchivo[20], contenidoArchivo[100];

    inicializarTablaIndice();

    while(opcion != 6){
    printf("\nIngrese que opcion quiere:\n 1: Ingresar Archivo.\n 2: Mostrar un archivo.\n 3: Listar todos.\n 4: Borrar un archivo.\n 5: Mostrar tabla de bits.\n 6: Salir.\n");        
    scanf("%d", &opcion);
        switch(opcion){
            case 1:
                printf("Ingrese nombre del archivo: ");
                scanf("%19s", nombreArchivo);
                printf("Ingrese contenido: ");
                scanf(" %99[^\n]", contenidoArchivo);

                int longitud = strlen(contenidoArchivo);
                int cantidadBloques = (longitud + 9) / 10;
                if (cantidadBloques == 0) cantidadBloques = 1;

                crearNuevoBloque(cantidadBloques, nombreArchivo, contenidoArchivo);
                break;

            case 2:
                printf("Ingrese el nombre del archivo que quiere ver: ");
                scanf("%19s", nombreArchivo);
                mostarArchivoDeTabla(nombreArchivo);
                break;

            case 3:
                listarTablaIndice(); 
                break;

            case 4: 
                printf("Ingrese el nombre del archivo que quiere borrar: ");
                scanf("%19s", nombreArchivo);
                eliminarArchivo(nombreArchivo);
                break;

            case 5:
                mostrarTablaBits();
                break;
            
            case 6:
                printf("Gracias por usar FAT.\n");
                break;

            default:
                printf("Ingrese un valor correcto de las opciones.\n");
                break;    
        }
    }
    return 0;
}