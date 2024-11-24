#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Nodo
{
    int info;
    struct Nodo *izq;
    struct Nodo *der;
};

typedef struct Nodo NODO;

// ----------------------------------------------------------------------------------------------------------------

// Referente a funciónes AB (Hay algunas que funcionan tambien en un ABO)

NODO *CrearNodo_AB(int num)
{
    NODO *nodo = malloc(sizeof(NODO));

    if (nodo == NULL)
        printf("No existe espacio en la memoria.");

    else
    {
        nodo->info = num;
        nodo->izq = NULL;
        nodo->der = NULL;
    }

    return nodo;
}

int Maximo(int nodo_1, int nodo_2)
{
    // Retorna el numero menor entre 2 numeros. Es complemento del algortimo "Altura()".

    if (nodo_1 > nodo_2)
        return nodo_1;
    else
        return nodo_2;
}

int Altura(NODO *raiz)
{
    // Retorna la longitud de la rama mas larga del arbol, mas 1. Aplica para AB y ABO.

    if (raiz == NULL)
        return 0;
    else
        return Maximo(Altura(raiz->izq), Altura(raiz->der)) + 1;
}

// -----------------------------------------------------------------------------------------------------------------

// Funciones que me ahorraron tiempo. Pero, no son mias.

void imprimeElementosNivel(NODO *arbol, int nivel)
{
    if (arbol == NULL)
        printf("-");
    else
    {
        if (nivel == 0)
            printf("%i", arbol->info);
        else
        {
            imprimeElementosNivel(arbol->izq, nivel-1);
            printf("|");
            imprimeElementosNivel(arbol->der, nivel-1);
        }
    }
}

void imprimeArbol(NODO *arbol)
{
    int h, i;

    h = Altura(arbol);
    for(i=0;i<h;i++)
    {
        printf("\n");
        imprimeElementosNivel(arbol, i);
    }
}

// -----------------------------------------------------------------------------------------------------------------

NODO *Insertar_ABO(NODO* arbol, int nodo)
{
    // Inserta un nodo en el arbol, manteniendo el orden de este. Basicamente, retorna un ABO.

    if (arbol == NULL)
        arbol = CrearNodo_AB(nodo);

    else
    {
        if (nodo < arbol->info)
            arbol->izq = Insertar_ABO(arbol->izq, nodo);
        else
            arbol->der = Insertar_ABO(arbol->der, nodo);
    }

    return arbol;
}

bool Esta_en_AB(NODO *raiz, int nodo)
{
    // Retorna True si el nodo ingresado esta en el arbol, y False en caso contrario. Aplica para AB y ABO.

    if (raiz == NULL)
        return false;
    if (raiz->info == nodo)
        return true;

    else
        return Esta_en_AB(raiz->izq, nodo) || Esta_en_AB(raiz->der, nodo);
}

NODO *Buscar_Nodo(NODO *arbol, int nodo)
{
    // Retorna el subarbol del nodo de un arbol AB o ABO.
    // Ojo. Esta función asume que el nodo esta en el arbol.

    if (arbol->info == nodo)
        return arbol;
    
    else
        if (arbol->izq != NULL && Esta_en_AB(arbol->izq, nodo))
            return Buscar_Nodo(arbol->izq, nodo);
        if (arbol->der != NULL && Esta_en_AB(arbol->der, nodo))
            return Buscar_Nodo(arbol->der, nodo);
}

int Peso(NODO *raiz)
{
    // Retorna la cantidad de nodos que tiene un arbol. Aplica para AB y ABO.

    if (raiz == NULL)
        return 0;
    
    else
        return 1 + Peso(raiz->izq) + Peso(raiz->der);
}

int Menor(NODO *arbol)
{
    // Retorna el menor nodo existente del arbol. Aplica para ABO.

    if (arbol != NULL)
        if (arbol->izq != NULL && arbol->izq->info < arbol->info)
            return Menor(arbol->izq);
        else
            return arbol->info;
    else
        return -1; // Solo en el caso de que el arbol este vacio.
}

int Mayor(NODO *arbol)
{
    // Retorna el mayor nodo existente del arbol. Aplica para ABO.

    if (arbol != NULL)
        if (arbol->der != NULL && arbol->der->info > arbol->info)
            Mayor(arbol->der);
        else
            return arbol->info;
    else
        return -1; // Solo en el caso de que el arbol este vacio.
}

int Nivel_De_Un_NODOAB(NODO *arbol, int nodo) // nodo = 13
{
    // Retorna el nivel de un nodo en un arbol. Aplica para AB y ABO.

    if (arbol->info != nodo)
        if (arbol->izq != NULL && Esta_en_AB(arbol->izq, nodo))
            return Nivel_De_Un_NODOAB(arbol->izq, nodo) + 1;

        if (arbol->der != NULL && Esta_en_AB(arbol->der, nodo))
            return Nivel_De_Un_NODOAB(arbol->der, nodo) + 1;
    else
        return 0;
}

int Suma_Nodos(NODO *arbol)
{
    // Retorna la suma total entre los nodos de un arbol. Aplica para AB y ABO.

    if (arbol == NULL)
        return 0;
    else
        return arbol->info + Suma_Nodos(arbol->izq) + Suma_Nodos(arbol->der);
}

void PreOrden(NODO* arbol)
{
    if (arbol != NULL)
    {
        printf("%i ", arbol->info);
        PreOrden(arbol->izq);
        PreOrden(arbol->der);
    }
}

void InOrden(NODO* arbol)
{
    if (arbol != NULL)
    {
        InOrden(arbol->izq);
        printf("%i ", arbol->info);
        InOrden(arbol->der);
    }
}

void PostOrden(NODO* arbol)
{
    if (arbol != NULL)
    {
        PreOrden(arbol->izq);
        PreOrden(arbol->der);
        printf("%i ", arbol->info);
    }
}

bool Es_Hoja(NODO *arbol, int nodo)
{
    // Retorna true si el nodo es hoja. En caso contrario retorna False. Aplica para AB y ABO.

    NODO *aux = Buscar_Nodo(arbol, nodo);

    if (aux->izq == NULL && aux->der == NULL)
        return true;
    else
        return false;
}

bool Es_Raiz_Padre(NODO *arbol, int nodo)
{
    // Retorna true si el nodo es la raiz padre del arbol. En caso contrario retorna false. Aplica para AB y ABO.

    if (arbol->info == nodo)
        return true;
    else
        return false;
}

void Padre_Nodo(NODO *arbol, int nodo) // nodo = 13
{
    // Imprime el padre de un nodo. Aplica para AB y ABO.
    
    if ((arbol->izq != NULL && arbol->izq->info == nodo) || (arbol->der != NULL && arbol->der->info == nodo))
        printf("\nPadre: %i", arbol->info);

    else
        if (Esta_en_AB(arbol->izq, nodo))
            Padre_Nodo(arbol->izq, nodo);

        else if (Esta_en_AB(arbol->der, nodo))
            Padre_Nodo(arbol->der, nodo);
}

void Antecesores_Nodo(NODO *arbol, int nodo) // nodo = 64
{
    // Imprime los antecesores de un nodo. Aplica para AB y ABO.

    if (arbol->info != nodo)

        if (arbol->izq != NULL && Esta_en_AB(arbol->izq, nodo))
        {
            printf(" %i", arbol->info);
            Antecesores_Nodo(arbol->izq, nodo);
        }

        if (arbol->der != NULL && Esta_en_AB(arbol->der, nodo))
        {
            printf(" %i", arbol->info);
            Antecesores_Nodo(arbol->der, nodo);
        }
}

void hijos_Nodo_AB(NODO *arbol, int nodo)
{
    // Retorna los hijos de un nodo. Aplica para un AB y ABO.

    NODO *aux = Buscar_Nodo(arbol, nodo);

    if (aux->izq != NULL)
        printf("\nHijo Izquierdo: %i", aux->izq->info);
    if (aux->der != NULL)
        printf("\nHijo Derecho: %i", aux->der->info);
}

/*void Descendientes_Nodo_v1(NODO *arbol, int nodo) // nodo = 64
{
    // Retorna los descendientes de un nodo. Aplica para un AB y ABO.
    // La función: - La idea de esta función, es que al principio se posicione/llegue al nodo que se quiere obtener sus descendientes.
    //             - Asume que el nodo a buscar si esta en el arbol. Y no imprime los descendientes en orden.
    //             - Esta es la version que puede recibir el arbol completo. Por si solo encontrar el nodo que le queremos sus descendientes.

    if (arbol == NULL)
        return;

    if (arbol->izq != NULL && Esta_en_AB(arbol->izq, nodo))
        Descendientes_Nodo_v1(arbol->izq, nodo);
    if (arbol->der != NULL && Esta_en_AB(arbol->der, nodo))
        Descendientes_Nodo_v1(arbol->der, nodo);
    
    else if (!Esta_en_AB(arbol->izq, nodo) && !Esta_en_AB(arbol->der, nodo)) // Si no lo encuentra ni por la derecha ni izquierda, entonces, quiere decir que ya lo encontro. En este punto, ya estamos posicionados en el nodo.
    {
        if (arbol->izq != NULL)
            printf(" %i", arbol->izq->info);
            Descendientes_Nodo_v1(arbol->izq, nodo);
        if (arbol->der != NULL)
            printf(" %i", arbol->der->info);
            Descendientes_Nodo_v1(arbol->der, nodo);
    }
    else
        return;
}*/

void Descendientes_Nodo_v2(NODO *subarbol) // nodo = 20
{
    // Retorna los descendientes de un nodo. Aplica para un AB y ABO.
    // La función: - Asume que el arbol recibido es el nodo pero en su versión de subarbol.
    //             - Esta versión no puede recibir el arbol completo. En cambio, tiene que recibir el nodo del que
    //               queremos obtener sus descendientes pero, en su versión de subarbol. (Usar "buscar_nodo()")

    if (subarbol->izq != NULL)
    {
        printf(" %i", subarbol->izq->info);
        Descendientes_Nodo_v2(subarbol->izq);
    }
    if (subarbol->der != NULL)
    {
        printf(" %i", subarbol->der->info);
        Descendientes_Nodo_v2(subarbol->der);
    }
}

void Analisis_AB(NODO* arbol)
{
    int nodo;
    bool nodo_valido;
    
    // ----------------------------------------------------------------------------------

    // Información del Arbol.

    printf("\nINFORMACION DEL ARBOL:");

    printf("\n\nPeso: %i", Peso(arbol));         // Imprimiir el Peso del arbol.
    printf("\nAltura: %i", Altura(arbol));       // Imprimir la Altura del arbol.

    // Mostrar el Menor nodo de un ABO.

    if (Menor(arbol) != -1)
        printf("\nMenor: %i", Menor(arbol));
    else
        printf("El arbol esta vacio.");

    // Imprimir el Mayor nodo de un ABO.

    if (Mayor(arbol) != -1)
        printf("\nMayor: %i", Mayor(arbol));
    else
        printf("El arbol esta vacio.");

    printf("\nSuma elementos: %i", Suma_Nodos(arbol));   // Imprimir la suma total de todos los nodos del arbol.

    // Imprimir el arbol AB o ABO.

    if (Altura(arbol) > 10)
        printf("\n\nEl arbol no se imprimira: tiene mas de 10 niveles.");

    else
    {
        printf("\n\nEl arbol es:\n");
        imprimeArbol(arbol);
    }

    // Recorrer el arbol en PreOrden.

    printf("\n\nPreOrden: ");
    PreOrden(arbol);

    // Recorrer el arbol en InOrden.

    printf("\nInOrden: ");
    InOrden(arbol);

    // Recorrer el arbol en PreOrden.

    printf("\nPostOrden: ");
    PostOrden(arbol);

    // ------------------------------------------------------------------------------------------------------------

    nodo_valido = false;
    while (!nodo_valido)
    {
        printf("\n\nIngresa un elemento del arbol: ");
        scanf("%i", &nodo);
        
        if (!Esta_en_AB(arbol, nodo))
            printf("El elemento %i no esta en el arbol. Ingrese otro.", nodo);
        else
            nodo_valido = true;
    }

    // Información de un elemento/nodo.

    printf("\nINFORMACION DEL ELEMENTO:");

    // Imprimir el nivel donde se encuentra el nodo.

    if (Esta_en_AB(arbol, nodo))
        printf("\n\nNivel: %i", Nivel_De_Un_NODOAB(arbol, nodo));
    else
        printf("\n\nEl nodo no esta en el arbol.");
    
    // Imprimir el padre y los antecesores de un nodo.

    if (Es_Raiz_Padre(arbol, nodo))
        printf("\nEs la raiz (sin padre ni antecesores)");
    else
    {
        Padre_Nodo(arbol, nodo);
        printf("\nAntecesores:");
        Antecesores_Nodo(arbol, nodo);
    }

    // Imprimir los hijos de un nodo y descendientes.

    if (Es_Hoja(arbol, nodo))
        printf("\nEs una hoja (sin hijos ni descendientes)");
    else
    {
        hijos_Nodo_AB(arbol, nodo);
        printf("\nDescendientes:");
        Descendientes_Nodo_v2(Buscar_Nodo(arbol, nodo));
    }
}

// ------------------------------------------------------------------------------------------------------------------

// Referente a funciónes de un ABO.

int Nivel_De_Un_NODOABO(NODO *arbol, int nodo) // nodo = 17
{
    // Retorna el nivel de un nodo en un arbol. Solo aplica para ABO.
    
    if (arbol->info != nodo)
    {
        if (nodo < arbol->info)
            return Nivel_De_Un_NODOAB(arbol->izq, nodo) + 1;
        else
            return Nivel_De_Un_NODOABO(arbol->der, nodo) + 1;
    }
    
    if (arbol->info == nodo)
        return 0;
}

void Padre_Nodo_ABO(NODO *arbol, int nodo)  // nodo = 13
{
    // Imprime el padre de un nodo. Aplica solo para ABO.

    if (arbol == NULL)
        return;

    if ((arbol->izq != NULL && arbol->izq->info == nodo) || (arbol->der != NULL && arbol->der->info == nodo))
    {
        printf("\nPadre: %i", arbol->info);
        return;
    }

    else
    {
        if (nodo < arbol->info)
            Padre_Nodo_ABO(arbol->izq, nodo);
        else
            Padre_Nodo_ABO(arbol->der, nodo);
    }
}

void Antecesores_Nodo_ABO(NODO *arbol, int nodo)
{
    // Imprime los antecesores de un nodo. Aplica solo para ABO.

    if (arbol->info != nodo)    // Esto es como un: "mientras no hayas llegado al nodo..."
    {
        if (nodo < arbol->info)
        {
            printf(" %i", arbol->info);
            Antecesores_Nodo_ABO(arbol->izq, nodo);
        }
        if (nodo > arbol->info)
        {
            printf(" %i", arbol->info);
            Antecesores_Nodo_ABO(arbol->der, nodo);
        }
    }
}

bool Es_Hoja_ABO(NODO *arbol)
{
    // Retorna true si el nodo recibido es hoja. En caso contrario, retorna false. Solo es una función complemento.

    if (arbol->izq == NULL && arbol->der == NULL)
        return true;
    else
        return false;
}

bool hijos_Nodo_ABO(NODO *arbol, int nodo)
{
    // Retorna true si el nodo tiene hijos, e imprime los hijos de un nodo. En caso contrario, si no tiene hijos, es
    // hoja, por lo que no los imprime y retorna false. Aplica solo para ABO.

    if (Es_Hoja_ABO(arbol))
        return false;

    if (arbol->info == nodo)
    {
        if (arbol->izq != NULL)
            printf("\nHijo Izquierdo: %i", arbol->izq->info);
        if (arbol->der != NULL)
            printf("\nHijo Derecho: %i", arbol->der->info);
        return true;
    }
    
    else
    {
        if (nodo < arbol->info)
            hijos_Nodo_ABO(arbol->izq, nodo);
        else
            hijos_Nodo_ABO(arbol->der, nodo);
    }
}

void Descendientes_Nodo_ABO(NODO *arbol, int nodo)  // Me llamo la antención el algoritmo de esta función.
{
    // Imprime los descendientes de un nodo. Aplica solo para ABO.

    if (arbol->info == nodo)
    {
        printf("\nDescendientes: ");
        InOrden(arbol->izq);
        InOrden(arbol->der);
        return;
    }

    if (nodo < arbol->info)
        Descendientes_Nodo_ABO(arbol->izq, nodo);
    else
        Descendientes_Nodo_ABO(arbol->der, nodo);
}

void Analisis_ABO(NODO *arbol)
{
    int nodo;
    bool nodo_valido;

    // ------------------------------------------------------------------------------------------------------------

    // Información del Arbol.

    printf("\nINFORMACION DEL ARBOL:");

    printf("\n\nPeso: %i", Peso(arbol));         // Imprimiir el Peso del arbol.
    printf("\nAltura: %i", Altura(arbol));       // Imprimir la Altura del arbol.

    // Mostrar el Menor nodo de un ABO.

    if (Menor(arbol) != -1)
        printf("\nMenor: %i", Menor(arbol));
    else
        printf("El arbol esta vacio.");

    // Imprimir el Mayor nodo de un ABO.

    if (Mayor(arbol) != -1)
        printf("\nMayor: %i", Mayor(arbol));
    else
        printf("El arbol esta vacio.");

    printf("\nSuma elementos: %i", Suma_Nodos(arbol));   // Imprimir la suma total de todos los nodos del arbol.

    // Recorrer el arbol en PreOrden.

    printf("\n\nPreOrden: ");
    PreOrden(arbol);

    // Recorrer el arbol en InOrden.

    printf("\nInOrden: ");
    InOrden(arbol);

    // Recorrer el arbol en PreOrden.

    printf("\nPostOrden: ");
    PostOrden(arbol);

    // Imprimir el arbol ABO.

    if (Altura(arbol) > 10)
        printf("\n\nEl arbol no se imprimira: tiene mas de 10 niveles.");

    else
    {
        printf("\n\nEl arbol es:\n");
        imprimeArbol(arbol);
    }

    // ------------------------------------------------------------------------------------------------------------

    nodo_valido = false;
    while (!nodo_valido)
    {
        printf("\n\nIngresa un elemento del arbol: ");
        scanf("%i", &nodo);
        
        if (!Esta_en_AB(arbol, nodo))
            printf("\n\nEl elemento %i no esta en el arbol. Ingrese otro.", nodo);
        else
            nodo_valido = true;
    }

    // Información de un elemento/nodo.

    printf("\nNivel: %i", Nivel_De_Un_NODOABO(arbol, nodo));      // Imprimir el nivel de un nodo.

    // Imprimir el padre y los antecesores de un nodo.

    if (Es_Raiz_Padre(arbol, nodo))
        printf("\nEs la raiz (sin padre ni antecesores)");
    else
    {
        Padre_Nodo_ABO(arbol, nodo);
        printf("\nAntecesores:");
        Antecesores_Nodo_ABO(arbol, nodo);
    }

    // Imprimir los hijos del nodo y los descendientes.

    if (!hijos_Nodo_ABO(arbol, nodo))
        printf("\nEs una hoja (sin hijos ni descendientes)");
    else
        Descendientes_Nodo_ABO(arbol, nodo);
}