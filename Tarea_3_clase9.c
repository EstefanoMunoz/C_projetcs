#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "funciones.h"

struct Arco
{
    int nodo_origen;
    int nodo_destino;
    int costo;
};

typedef struct Arco ARCO;

ARCO *Arco_Mayor(int **matriz, int N)
{
    // Retorna el arco mayor de un grafo, usando su matriz de adyacencia o costo.

    ARCO *arco_mayor = malloc(sizeof(ARCO));;
    int i, j, nodos_sinvisitar;

    arco_mayor->costo = 0;
    for (i=0; i<N; i++)     // Para ir cambiando de uno en uno los nodos de origen.
    {
        for(j=0; j<N; j++)
        {
            if (matriz[i][j] != 0 && matriz[i][j] > arco_mayor->costo)
            {
                arco_mayor->nodo_origen = i;
                arco_mayor->nodo_destino = j;
                arco_mayor->costo = matriz[i][j];
            }
        }
    }

    return arco_mayor;
}

void Adyacentes_grados(int **matriz, int N)
{
    int count, i, j;
    int *adyacentes = creaArreglo(N);

    for (i=0; i<N; i++)
    {
        count = 0;
        for (j=0; j<N; j++)
        {
            if (i == j && matriz[i][j] != 0)
                printf(" %i", j);

            else if (matriz[i][j] != 0)
            {
                printf(" %i", j);
                count++;
            }
        }

        if (count == 0)
            printf(" --, gr(%i): %i", i, count);

        else
            printf(", gr(%i): %i", i, count);
    }
}

int Profundidad_Nodos(int **matriz, int N)
{
    bool *visitados;
    int i;

    visitados = creaArregloBool(N);
    reseteaVisitados(visitados, N);

    for (i=0; i<N; i++)
    {
        printf("Nodo %i: ", i);
        Profundidad(matriz, N, visitados, i);
        reseteaVisitados(visitados, N);
        printf("\n");
    }
}

int Grafo_K_Regular(int **matriz, int N)
{
    int i, j, count = 0, count_ant = 0;
    bool flag_primero = true;

    for (i=0; i<N; i++)
    {
        for (j=0; j<N; j++) // Va a contar cuantas aristas tiene el nodo origen i. Y en base a esto, compararemos si los demas modos origen tiene la misma cantidad de aristas.
        {
            if (matriz[i][j] != 0)
                count++;
        }

        if (flag_primero == true)   // Va a guardar en count_ant la cantidad de aristas que debe tener cada nodo origen siempre. Es decir, tecnicamente, cada nodo origen debe tener la misma cantidad de aristas que hay en count_ant.
        {
            count_ant = count;      // Va a guardar la cantidad de aristas que tecnicamente debe tener cada nodo origen.
            flag_primero = false;   // Es nomas para que luego ya no se ejecute este if.
            count = 0;              // Para que al pasar al siguiente nodo origen, se cuente cuantas aristas tiene.
        }
        
        else    // Si ya se tiene la cantidad de aristas que debe tener cada nodo.
        {
            if (count == count_ant) // verificar que cada nodo tenga la misma cantidad de aristas.
                count = 0;

            else
                return -1;  // Quiere decir que hay un nodo que no tiene la misma cantidad de aristas que las demas.
        }
    }

    return count_ant;   // El grafo sera k-regular = count_ant.
}

int Grafo_Desconexo(int **matriz, int N)
{
    int i, nro_componentes = 0;
    bool *visitados = creaArregloBool(N);
    reseteaVisitados(visitados, N);

    Profundidad(matriz, N, visitados, 0);   // No se como evitar que la función imprima los nodos.
    for (i=0; i<N; i++)
    {
        if (visitados[i] == false)
            nro_componentes++;
    }
    
    if (nro_componentes != 0)
        return nro_componentes;  // El grafo tiene <nro_componentes> cantidad de componentes conexas.
    
    else
        return -1;  // El grafo no tiene ningun componente.
}

void Dijkstra_Nodos(int **matriz, int N)
{
    int i;
    bool *visitados = creaArregloBool(N);   // Esto esta de mas, ahora me acabo de dar cuenta.
    reseteaVisitados(visitados, N);         // Esto esta de mas, ahora me acabo de dar cuenta.

    for (i=0; i<N; i++)
    {
        printf("Desde %i:", i);
        Dijkstra(matriz, N, i);
        printf("\n\n");
    }
}

int Amplitud_Nodos(int **matriz, int N)
{
    bool *visitados;
    int i;

    visitados = creaArregloBool(N);
    reseteaVisitados(visitados, N);

    for (i=0; i<N; i++)
    {
        printf("Nodo %i: ", i);
        Amplitud(matriz, N, visitados, i);
        reseteaVisitados(visitados, N);
        printf("\n");
    }
}

int **Grafo_Complemento(int **Matriz, int N, int tipo)   // Aplica tanto para grafos diriginos y no dirigidos.
{
    int i, j, **matriz_complemento = creaMatriz(N);

    for (i=0; i<N; i++) // Dentro de este for se hara lo siguiente: Por cada numero 1 (Matriz de grafo no valuado) o mayor a 0 (matriz de grafo valuado) en la matriz del grafo G1; sera un 0 en la matriz complemento G2.
    {
        for (j=0; j<N; j++)
        {
            if (i == j)
                matriz_complemento[i][j] = 0;

            else
            {
                if (tipo == 1 && Matriz[i][j] != 0)  // Grafo dirigido.
                {
                    matriz_complemento[i][j] = 0;
                    matriz_complemento[j][i] = 0;
                }

                else if (tipo == 2 && Matriz[i][j] != 0)    // Grafo no-dirigido.
                    matriz_complemento[i][j] = 0;
            }
        }
    }

    for (i=0; i<N; i++) // Dentro de este for se hara lo siguiente: Por cada 0 en la matriz del grafo G1; sera un 1 en la matriz complemento G2.
    {
        for (j=0; j<N; j++)
        {
            if (i == j)
                continue;

            else
            {
                if (tipo == 1 && Matriz[i][j] == 0)  // Grafo dirigido.
                    matriz_complemento[i][j] = 1;

                else if (tipo == 2 && Matriz[i][j] == 0)    // Grafo no-dirigido.
                    matriz_complemento[i][j] = 1;
            }
        }
    }

    return matriz_complemento;
}

bool Grafo_Completo(int **Matriz, int N, int tipo)
{
    int i, j;
    bool nodo_fuente = true;

    if (tipo == 1)      // Si el grafo es dirigido, segun la definición de grafo completo, este no puede ser completo.
        return false;

    for (i=0; i<N; i++)
    {
        for (j=0; j<N; j++)
        {
            if (Matriz[i][j] != 0 || i == j)
                continue;
            
            else
                return false;   // El grafo no es completo.
        }
    }

    return true;    // El grafo si es completo.
}

void Nodos_Sucesores_Grado(int **matriz, int N)
{
    int i, j, count_suce;   // Ojo: "i" para ver los sucesores "j" de cada nodo. "j" para ver los antecesores "i" de cada nodo. 

    for (i=0; i<N; i++)
    {
        count_suce = 0;
        printf("Nodo %i:", i);
        
        for (j=0; j<N; j++)
        {
            if (matriz[i][j] != 0)  // Si en cada casilla de una fila/nodo hay un numero diferente de 0, entonces, "j" es un sucesor del nodo "i".
            { 
                printf(" %i", j);
                count_suce++;
            }
        }

        if (count_suce == 0)
            printf(" --, gr+(%i): %i\n", i, count_suce);

        else
            printf(", gr+(%i): %i\n", i, count_suce);
    }
}

void Nodos_Antecesores_Grado(int **matriz, int N)
{
    int i, j, count_ante;   // Ojo: "i" para ver los sucesores "j" de cada nodo. "j" para ver los antecesores "i" de cada nodo. 

    for (i=0; i<N; i++)
    {
        count_ante = 0;
        printf("Nodo %i:", i);
        
        for (j=0; j<N; j++)
        {
            if (matriz[j][i] != 0)  // Si en cada casilla de una columna/nodo hay un numero diferente de 0, entonces, "j" es un antecesor del nodo "i".
            { 
                printf(" %i", j);
                count_ante++;
            }
        }

        if (count_ante == 0)
            printf(" --, gr-(%i): %i\n", i, count_ante);

        else
            printf(", gr-(%i): %i\n", i, count_ante);
    }
}

int main()
{
    int N, nro_aristas, tipo;   // N: Numero de nodos; nro_aristas: El numero de aristas; tipo: El tipo de grafo (Dirigido "1" o No-dirigido "2")
    int **matriz, **matriz_complemento;               // Declaro el tipo de variable de puntero a puntero que apuntara a las filas y columnas de la matriz MxN
    char nombre_archivo[50];    // Declaro la variable donde se almacenara el nombre del archivo a leer.
    ARCO *arco_mayor;

    printf("Nombre del archivo: ");
    scanf("%s", nombre_archivo);

    matriz = leeArchivo(nombre_archivo, &N, &nro_aristas, &tipo);

    // Imprimir la matriz del grafo.

    printf("Matriz del grafo:\n\n");
    imprimeMatrizGrafo(matriz, N);

    // Imprimir el arco de mayor costo y su costo.

    arco_mayor = Arco_Mayor(matriz, N);
    printf("\nArco de costo mayor: (%i, %i), costo: %i", arco_mayor->nodo_origen, arco_mayor->nodo_destino, arco_mayor->costo);

    // Imprimir los adyancentes y grado para cada nodo del grafo.

    printf("\n\nNodos Adyacentes y sus Grados:\n");
    Adyacentes_grados(matriz, N);

    // Imprimir el recorrido en profundidad desde cada nodo.

    printf("\n\nRecorrido en profuncidad de cada nodo:\n\n");
    Profundidad_Nodos(matriz, N);

    // Imprimir si se trata de un grafo k-regular o no. Si es k-regular debes imprimir el valor de k.

    printf("\nVerificacion de grafo k-regular:\n");

    if (Grafo_K_Regular(matriz, N) != -1)
        printf("    - El grafo si es k-regular. Su valor es: %i\n", Grafo_K_Regular(matriz, N));
    
    else
        printf("    - El grafo no es k-regular.\n");

    // Imprimir si se trata de un grafo conexo o desconexo. Si es desconexo debe indicar ademas el numero de componentes conexas.

    printf("\nVerificacion grafo conexo o desconexo:\n");

    if (Grafo_Desconexo(matriz, N) == -1)
        printf("    - El grafo es conexo.\n\n");
    
    else
        printf("    - El grafo es desconexo.\nNro Componentes conexa: %i\n\n", Grafo_Desconexo(matriz, N));

    // Imprimir los caminos de costo minimo desde cada nodo (usando Dijstra) a todos los otros. Si no existe un camino el programa debe imprimir un mensaje.

    printf("CAMINOS MINIMOS (Dijkstra):\n\n");
    Dijkstra_Nodos(matriz, N);

    // Imprimir el recorrido en amplitud desde cada nodo.

    printf("Recorrido en amplitud de cada nodo:\n\n");
    Amplitud_Nodos(matriz, N);

    // Generar e imprimir grafo complemento.

    printf("\nGrafo complemento G2 de G1:\n\n");

    matriz_complemento = Grafo_Complemento(matriz, N, tipo);
    imprimeMatrizGrafo(matriz_complemento, N);

    // Imprimir si se trata de un grafo completo o no.

    printf("\nVerificacion del grafo complemento si es completo o no:\n");
    
    if (Grafo_Completo(matriz_complemento, N, tipo) == true)
        printf("    - El grafo si es completo.\n");
    
    else
        printf("    - El grafo no es completo.\n");

    // Imprimir los sucesores y grado de salida para cada nodo del grafo.

    printf("\nNodos Sucesores y Grado de Salida de cada nodo:\n\n");
    Nodos_Sucesores_Grado(matriz, N);

    // Imprimir los antecesores y grado de entrada para cada nodo del grafo.

    printf("\nNodos Antecesores y Grado de Entrada de cada nodo:\n\n");
    Nodos_Antecesores_Grado(matriz, N);

    return 0;
}   

/*
Funciones por hacer:

    - Función que cuenta la cantidad de componentes que hay en un grafo desconexo.
        - Función adicional: "Crear una función que modifique el arroglo conectados para para arreglar el problema en la
          verificaión grafo conexo o desconexo. Se parece a la de profundidad/amplitud, solo que no debe imprimir nada."

    - Función que verifique que un grafo sea aciclico. "La clave esta en verificar si se puede iniciar en un nodo y llegar
      al mismo nodo sin problema."
*/

// Desafio: Crear una función que calcule el factorial de cada costo de un grafo (dirigido o no dirigido) que tenga adyacencia