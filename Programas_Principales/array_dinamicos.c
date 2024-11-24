#include <stdio.h>
#include <stdlib.h> // Solo pasar usar la función exit()
#define max 200

int LeerArchivo(char nombre[50], float datos[max])  // Defino los "objetos" que manipulara la función.
{
    // Leera el archivo (si existe o no) y arrojara la cantidad de elementos.

    int n, i;
    FILE *p_arch;

    p_arch = fopen(nombre, "r");    // El puntero 'p_arch' ahora apunta a la dirección de memoria donde se encuentra el archivo (nombre) mediante la apertura ('fopen()'). Tendremos acceso al archivo gracias a "p_arch".

    if (p_arch == NULL)             // Si el puntero 'p_arch' apunta a una dirección de memoria nula, quiere decir que el archivo no existe.
        printf("No se puede abrir el archivo.\nRevisa su ubicacion.\n\n");
        //exit(0);                    // Para cerrar el programa anticipadamente. (Y asi no se imprime lo que sigue en main.)

    fscanf(p_arch, "%i", &n);       // Preguntar al profe como fscanf() y fgets() recorren automaticamente las lineas de un archivo. Y consultar la logia de esta linea.

    // Almacenar los datos del archivo en el array datos. (Aprovecharemos que sabremos la cantidad de datos en el archivo.)

    i = 0;
    while (i < n)                   // Limitara que fscanf() recorra las lineas del archivo hasta llegar a "n", que corresponde a 10 en este caso. (texto_1.txt)
    {
        fscanf(p_arch, "%f", &datos[i]);
        i++;
    }

    return n;   // Ademas de "n", no es necesario retornar el array actualizado (ademas que no se puede; creo/supongo) ya que se modifica sin tener que estar dentro de la función "main".
}

void Imprimir(float datos[max], int n)
{
    // Muestra en pantalla cada dato encontrado en el archivo.

    int i;

    for (i=0; i<n; i++)                   // Ya que el programa sabe cuando es "n", lo usaremos para
        printf("\t%f\n", datos[i]);     // imprimir cada dato en el archivo linea tras linea.
}   

float Sumar(float datos[max], int n)
{
    // Suma de los valores del arreglo.

    float suma = 0;     // Variable donde se iran sumando y guardando los valores del array.
    int i;

    for (i=0; i<n; i++)   // Desde datos[0] hasta datos[n-1]. Digo "n-1" porque en el loop no cuento el "n" por ser "i < n".
        suma += datos[i];
    
    return suma;
}

float Mayor(float datos[max], int n)
{
    // Retorna el mayor numero del archivo.

    float mayor;
    int i;
    
    mayor = datos[0];    // Guardaremos el primer valor del array por si resulta siendo este el mayor.
    for (i=1; i<n; i++)    // Inicializo i en 1 porque ya inicie designando datos[0] y no voy a
    {
        if (datos[i] > mayor)   // comparar (en la iteración) datos[0] > datos[0]. No tiene sentido. Por eso lo defini antes.
            mayor = datos[i];   // Si el valor del indice siguiente del array es mayor que el indice anterior, entonces, sobreescribiremos la variable con el ahora valor mayor.
    }

    return mayor;
}

int Buscar(float datos[max], int n, float valor)
{
    // Busca un valor solicitado por el usuario, en el archivo.

    int i;

    for (i=0; i<n; i++)
    {
        if (datos[i] == valor)      // Si el valor en el indice "i" del array es el mismo que el que solicito el usuario (valor), entonces ...
            return i;               // retornas el indice del valor donde se encuentra contenido.
    }

    // En caso de que no exista el valor a buscar:
    return -1;
}

float Promediar(float datos[max], int n)
{
    // Calcula el promedio de los valores del archivo.

    return (Sumar(datos, n)) / n;   // Aprovecho la funcion suma para nada mas dividirlo en la cantidad de datos de la suma. Al mismo tiempo lo arrojo.
}

float SumaPosicionesPar(float datos[max], int n)
{
    // Arroja la suma total de los valores posicionados en los indices pares.
    
    int i;
    float suma_par = 0;

    for(i=2; i<n; i+=2)   // Los indices "i" irean incrementando de dos en dos pertinentemente, iniciando desde la posición 2. Asi nomas me preocupo en sumar esas posiciones.
        suma_par = suma_par + datos[i];

    return suma_par;      // Se arrojara la suma apenas termine el loop for.
}

void Invertir(float datos[max], int n)
{
    // Invertira el orden (indices) de los valores del array original y luego imprimira cada valor consecutivamente.
    
    // Parte 1: Invertir el orden de los valores del array:
    
    int i, j = 1;                   // La "j" lo usare para acceder al array pero inversamente.

    for (i=0; i<n; i++)             // Este loop for lo usare para acceder con indices al array original.
    {
        datos[i] = datos[n-j];      // Ejemplo: Iteración 1: datos[0] = datos[9] , Iteración 2: datos[1] = datos[8] , ... , Iteración 9: datos[9] = datos[0]
        j++;                        // "j" se ira incrementando para restarle al "n".
    }

    // Parte 2: Imprimir consecutivamente cada valor del array.

    for (i=0; i<n; i++)     // Este for nomas para acceder a cada valor del array.
        printf("\t%f\n", datos[i]);
}

int main()
{
    int n;
    float valor, datos[max];       // En "datos" se almacenara cada valor obtenido en el archivo. (Y mas adelante de actualizara)
    char nombre_arch[100];         // Aqui se almacenara el nombre del archivo.

    // Solicitar nombre del archivo ".txt" a leer:

    printf("Ingresa el nombre del archivo: ");
    scanf("%s", &nombre_arch);  // Recibira el nombre del archivo y lo guardara en el array "nombre_arch"
    printf("\n");
    //fgets(nombre_arch, sizeof(nombre_arch), stdin); por si el nombre del archivo tiene espacios.

    n = LeerArchivo(nombre_arch, datos);    // nombre_arch: la función recibira el nombre del archivo. ; datos: la función recibira el array "datos" donde se almacenaran los datos/valores del archivo. ; n: recibira el número de datos del archivo que arrojara la función.

    // Imprimir cada valor del archivo:

    printf("Contenido del archivo %s\n\n", nombre_arch);
    Imprimir(datos, n);

    // Suma de los valores del array.

    printf("\nSuma total: %.3f", Sumar(datos, n));

    // Mostrar mayor numero contenido en el archivo.

    printf("\nMayor valor: %.3f", Mayor(datos, n));

    // Calcular el promedio de los valores del archivo.

    printf("\nPromedio: %.3f", Promediar(datos, n));

    // Calcular la suma de los valores en las posiciones pares.

    printf("\nSuma de posiciones pares: %.3f", SumaPosicionesPar(datos, n));

    // Buscar un valor ingresado por el usario.

    printf("\n\nValor para buscar: ");
    scanf("%f", &valor);

    if (Buscar(datos, n, valor) != -1)          // Si la función no arroja un -1, quiere decir que si existe el valor solicitado.
        printf("Posicion: %i", Buscar(datos, n, valor));
    
    else    // Si anteriormente la función arrojo -1, entonces no existio el numero solicitado.
        printf("%.3f no se encuentra.", valor);

    // Invertir el contenido del array.

    printf("\n\nArreglo invertido:\n\n");
    Invertir(datos, n);

    return 0;
}
