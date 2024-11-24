#include <stdio.h>
#include <stdlib.h>
#include "Funciones_AB_ABO.h"

NODO *Leer_Archivo(char name_file[50])
{
    FILE *archivo = fopen(name_file, "r");
    NODO *arbol = NULL;
    int nodo;

    if (archivo == NULL)
    {
        printf("No se a encontrado el archivo.");
        exit(0);
    }
    
    else
        while (fscanf(archivo, "%i", &nodo) != EOF)
            arbol = Insertar_ABO(arbol, nodo);

    fclose(archivo);
    return arbol;
}

void main()
{   
    NODO *arbol = NULL;
    char name_file[50];

    printf("Ingresa el nombre del archivo: ");
    scanf("%s", &name_file);

    arbol = Leer_Archivo(name_file);

    Analisis_AB(arbol);     // Si quisieramos analizar un Arbol Binario.
    //Analisis_ABO(arbol);    // Si quisieramos analizar un Arbol Binario Ordenado.
}
