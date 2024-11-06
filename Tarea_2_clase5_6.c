#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Nodo
{
    int info;
    struct Nodo *sig;
};

typedef struct Nodo NODO;

NODO *CrearNodo(int valor)
{
  NODO *p;
  
  p = malloc(sizeof(NODO));

  if (p == NULL)
  {
    printf("No hay memoria suficiente, Este programa se cerrara.");
    exit(0);
  }

  else
  {
    p->info = valor;
    p->sig = NULL;
  }

  return p;
}

NODO *Insertar_Final(NODO *lista, int valor)
{
  // Recibe un entero llamado dato, y crea y retorna un puntero a un nuevo nodo creado, cuyo info almacenara a dato y el puntero sig apunta a NULL.

  NODO *nuevo_nodo, *aux;

  nuevo_nodo = CrearNodo(valor);
  if (lista == NULL) // La lista esta vacia.
  {
    lista = nuevo_nodo;
  }

  else // La lista no esta vacia.
  {
    aux = lista;
    while (aux->sig != NULL)
    {
      aux = aux->sig;
    }

    aux->sig = nuevo_nodo;
    nuevo_nodo = NULL;
    aux = NULL;
  }

  return lista;
}

NODO *LeerArchivo(char nombre[50])
{
  // Recibe un nombre de archivo, y almacena los enteros que posee el archivo en el mismo orden en una lista que luego retorna.

  FILE *archivo;
  NODO *lista;
  int valor;

  archivo = fopen(nombre, "r");

  if (archivo == NULL)
    printf("No se pudo abrir el archivo. Por favor, revisar la ubicación del archivo.");

  else
  {
    lista = NULL;
    while (fscanf(archivo, "%i", &valor) != EOF)
    {
        lista = Insertar_Final(lista, valor);
    }
    fclose(archivo);
  }
  return lista;
}

void Imprimir_Lista(NODO *lista)
{
  // Recibe una lista e imprime los numeros que almacena separados por un espacio. Si la lista estuviese vacia, debe imprimir un "-".

  NODO *aux;

  if (lista == NULL) // Lista vacia.
    printf("-");

  else // Lista no vacia.
  {
    aux = lista;
    while (aux != NULL)
    {
      printf("%i ", aux->info);
      aux = aux->sig;
    }
    printf("\n");
  }
}

NODO *Insertar_Inicio(NODO *lista, int valor)
{
  // Recibe una lista y un entero dato, y genera un nuevo nodo que almacena a dato, e inserta el nuevo nodo al principio de la lista, retornandola.

  NODO *nuevo_nodo;

  nuevo_nodo = CrearNodo(valor);
  if (lista == NULL)
    lista = nuevo_nodo;

  else
  {
    nuevo_nodo->sig = lista;
    lista = nuevo_nodo;
    nuevo_nodo = NULL;
  }

  return lista;
}

NODO *Insertar_Lista_Ordenada(NODO *lista, int valor) // Suponiendo que la lista que entra esta ordenada... :
{
  // Recibe una lista y un entero dato, y genera un nuevo nodo aux->info que almacena a dato, e inserta el nuevo nodo en forma ordenada en la lista, retornandola.

  NODO *aux, *nuevo_nodo;

  if (valor < lista->info)  // Compara si "valor" es menor que el primer valor de la lista.
      return Insertar_Inicio(lista, valor); // Para insertar al inicio.

  // Si no lo es, entra al while.
  nuevo_nodo = CrearNodo(valor);
  aux = lista;
  while (aux->sig != NULL)
  {
    if ((valor > aux->info) && (valor < aux->sig->info))  // Debe ser ((V) && (V)) para insertar el nodo en el medio de los dos nodos.
    {
      nuevo_nodo->sig = aux->sig;   // Son para insertar en el
      aux->sig = nuevo_nodo;        // medio de los dos nodos.

      return lista; // Para cortar el loop while.
    }
    
    else
      aux = aux->sig; // Para pasar al siguiente nodo de la lista.
  }

  aux->sig = nuevo_nodo;
  nuevo_nodo = NULL;

  return lista;
}

bool Pertenecer_Lista(NODO *lista, int valor)
{
  NODO *aux = lista;

  if (lista == NULL)  // Si la lista que se ingresa esta vacia (es decir, apunta a nulo), retorna
    return false;     // false porque no existe el numero en aquella lista.

  else
  {
    while (aux != NULL)
    {
      if (aux->info == valor)
        return true; // Se encontró el número "valor" en la lista.
      
      aux = aux->sig;
    }
    return false; // Si anteriormente no se encontró el número "valor" en la lista.
  }
}

int Largo_Lista(NODO *lista)
{
  // Recibe una lista y retorna la cantidad de elementos que almacena.

  NODO *aux = lista;
  int contar = 0;

  if (lista == NULL)
    return contar;  // EL largo de la lista es 0, es decir, hay 0 nodos.

  else
  {
    while (aux != NULL)
    {
      contar++;  // Por cada nodo que apunte "aux", se contara 1 en "contar".
      aux = aux->sig;  
    }
  }

  return contar;
}

int Mayor_Lista(NODO *lista)
{
  // Recibe una lista y retorna el mayor valor que almacena.

  NODO *aux;
  int mayor = lista->info;  // Toma el primer valor de la lista.

  aux = lista->sig;
  while (aux != NULL)
  {
    if (aux->info > mayor)
    {
      mayor = aux->info;
      aux = aux->sig;
    }

    else
      aux = aux->sig;
  }
  return mayor;
}

NODO *Ordenar_Lista(NODO *lista)
{
  // Recibe una lista y, a partir de ella, genera una nueva lista pero con sus valores ordenados. Retorna la nueva lista.

  NODO *lista_ordenada = NULL, *aux;
  int menor, mayor, size, i;

  size = Largo_Lista(lista);  // Tamaño de la lista.
  mayor = Mayor_Lista(lista); // El numero mayor de la lista.
  
  for (i=1; i<=size; i++)     // Este loop "for" ayuda a que el while (lo que hace dentro de este) se realize la misma cantidad de veces que el tamaño de la lista.
  {
    menor = mayor;            // "menor", primero, sera el mayor numero de la lista, y ya luego se ira actualizando a un numero mas pequeño.
    aux = lista;
    while (aux != NULL)       // Este while (lo que esta dentro de él) buscara cada numero menor de la lista para ingresarla a una nueva lista (usando el "Inserta_Inicio()") de manera ordenada.
    {
      if ((aux->info < menor) && (Pertenecer_Lista(lista_ordenada, aux->info) == false))  // "Pertenecer_Lista(lista_ordenada, menor)" se lee como: "¿"menor" esta contenido en la lista "lista_ordeanda"?"
        menor = aux->info;
      
      aux = aux->sig;
    }
    lista_ordenada = Insertar_Final(lista_ordenada, menor);
  }

  return lista_ordenada;
}

int Menor_Lista(NODO *lista)
{
  // Recibe una lista y retorna el menor valor que almacena.

  NODO *aux;
  int menor = lista->info;  // Toma el primer valor de la lista.

  aux = lista->sig;
  while (aux != NULL)
  {
    if (aux->info < menor)
    {
      menor = aux->info;
      aux = aux->sig;
    }

    else
      aux = aux->sig;
  }
  return menor;
}

int Sumar_Lista(NODO *lista)
{
  NODO *aux;
  int suma = 0;

  aux = lista;
  while (aux != NULL)
  {
    suma += aux->info;
    aux = aux->sig;
  }

  return suma;
}

NODO *Invertir_Lista(NODO *lista)
{
  NODO *aux, *lista_invertida = NULL;

  aux = lista;
  while (aux != NULL)
  {
    lista_invertida = Insertar_Inicio(lista_invertida, aux->info);
    aux = aux->sig;
  }

  return lista_invertida;
}

NODO *Union_Listas(NODO *L , NODO *M)
{
  // Recibe dos listas y, a partir de ellas, genera una nueva lista con los elementos de ambas listas, pero sin elementos repetidos. Retorna la nueva lista.

  NODO *join = NULL, *aux; 

  aux = L;
  while (aux != NULL)
  {
    if (Pertenecer_Lista(M, aux->info) == false)    // Verifica si el numero en el nodo al cual apunta "aux" de la lista L, no se encuentra en la lista M. Si es asi, Pertenece_lista() arroja false, lo que nos dice que el numero no esta en ambas listas. (Union)
      join = Insertar_Final(join, aux->info);       // El numero que cumplio la condición se guarda como un nuevo nodo en la lista "join". 
    
    aux = aux->sig;
  }

  return join;
}

NODO *Interseccion_Listas(NODO *L, NODO *M)
{
  // Recibe dos listas y, a partir de ellas, genera una nueva lista con los elementos en comun de ambas listas. Retorna la nueva lista.

  NODO *interseccion = NULL, *aux;

  aux = L;
  while (aux != NULL)
  {
    if (Pertenecer_Lista(M, aux->info) == true)                 // Verifica si el numero en el nodo al cual apunta "aux" de la lista L, tambien se encuentra en la lista M. Si es asi, Pertenece_lista() arroja true, lo que nos dice que el numero esta en ambas listas. (Intersección)
      interseccion = Insertar_Final(interseccion, aux->info);   // El numero que cumplio la condición se guarda como un nuevo nodo en la lista "interseccion".
    
    aux = aux->sig;
  }

  return interseccion;
}

NODO *Restar_Listas(NODO *L, NODO *M)
{
  // Recibe dos listas L y M y, a partir de ellas, genera una nueva lista con los elementos que pertenecen a L pero no pertenecen a M. Retorna la nueva lista.

  NODO *aux, *lista_resta = NULL;

  aux = L;
  while (aux != NULL)
  {
    if (Pertenecer_Lista(M, aux->info) == false)
      lista_resta = Insertar_Final(lista_resta, aux->info);
  
    aux = aux->sig;
  }

  return lista_resta;
}

NODO *Borrar_Lista(NODO *lista)
{
  // Recibe una lista y libera la memoria de cada nodo que posee, retornando finalmente NULL.

  NODO *aux_eliminar;

  while (lista != NULL)
  {
    aux_eliminar = lista;       // "aux_eliminar" apunta primer nodo.
    lista = lista->sig;         // "lista" apunta al siguiente nodo.
    aux_eliminar->sig = NULL;   // El nodo al que apunta "aux_eliminar" ahora no apunta a NULL (es decir, apunta a nada)
    free(aux_eliminar);         // Ahora que el nodo de "aux_eliminar" no apunta a nada, podemos liberar memoria.
  }

  return lista;

}

void Informacion_lista_L(NODO *L)
{ 
  // Imprimir la primera lista
 
  printf("\nPRIMERA LISTA: ");
  Imprimir_Lista(L);

  // Imprimir el largo de la primera lista

  printf("Largo: %i\n", Largo_Lista(L));

  // Imprimir el menor elemento de la primera lista

  printf("Menor elemento: %i\n", Menor_Lista(L));

  // Imprimir el mayor elemento de la primera lista

  printf("Mayor elemento: %i\n", Mayor_Lista(L));

  // Imprimir la suma de los elementos

  printf("Suma de los elementos: %i\n", Sumar_Lista(L));

  // Imprimir la lista invertida

  printf("Lista invertida: ");
  Imprimir_Lista(Invertir_Lista(L));

  // Imprimir la lista ordenada

  printf("Lista ordenada: ");
  Imprimir_Lista(Ordenar_Lista(L));
}

void Informacion_lista_M(NODO *M)
{
  printf("\nSEGUNDA LISTA: ");
  Imprimir_Lista(M);

  // Imprimir el largo de la primera lista

  printf("Largo: %i\n", Largo_Lista(M));

  // Imprimir el menor elemento de la primera lista

  printf("Menor elemento: %i\n", Menor_Lista(M));

  // Imprimir el mayor elemento de la primera lista

  printf("Mayor elemento: %i\n", Mayor_Lista(M));

  // Imprimir la suma de los elementos

  printf("Suma de los elementos: %i\n", Sumar_Lista(M));

  // Imprimir la lista invertida

  printf("Lista invertida: ");
  Imprimir_Lista(Invertir_Lista(M));

  // Imprimir la lista ordenada

  printf("Lista ordenada: ");
  Imprimir_Lista(Ordenar_Lista(M));
}

void Informacion_L_M(NODO *L, NODO *M)
{
   NODO *resta_listas = NULL;

  // Imprimir la Union de L y M

  printf("\nUNION: ");
  Imprimir_Lista(Union_Listas(L, M));

  // Imprimir la Union de L y M ordenadas

  printf("UNION ORDENADA: ");
  Imprimir_Lista(Union_Listas(L, M));

  // Imprimir la Intersección de L y M

  printf("INTERSECCION: ");
  Imprimir_Lista(Interseccion_Listas(L, M));

  // Imprimir la Intersección de L y M ordenadas

  printf("INTERSECCION ORDENADA: ");
  Imprimir_Lista(Interseccion_Listas(L, M));

  // Resta

  printf("RESTA: ");
  Imprimir_Lista(Restar_Listas(L, M));


  // Resta Ordenada

  printf("RESTA ORDENADA: ");
  resta_listas = Restar_Listas(L, M);
  Imprimir_Lista(Ordenar_Lista(resta_listas));
}

int main()
{
  NODO *L, *M;
  char archivo_1[50], archivo_2[50];

  printf("Ingresa el nombre del primer archivo: ");
  scanf("%s", archivo_1);

  L = LeerArchivo(archivo_1);

  printf("Ingresa el nombre del segundo archivo: ");
  scanf("%s", archivo_2);

  M = LeerArchivo(archivo_2);

  // Lista 1:

  Informacion_lista_L(L);

  // Lista 2:

  Informacion_lista_M(M);

  // Información entre listas L y M

  Informacion_L_M(L, M);

  // Liberar memoria de cada lista.

  L = Borrar_Lista(L);
  M = Borrar_Lista(M);

  printf("\n");

  return 0;
}