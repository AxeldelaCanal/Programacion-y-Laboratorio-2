#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


typedef struct
{
    int valor;
    struct nodo* siguiente;

} nodo;

typedef struct
{
    char nombre[50];
    int edad;
    struct nodoRegistro* siguiente;

}nodoRegistro;


///--------------------------------PROTOTIPADOS:-------------------------------------
/*----------------------------------EJERCICIO 1------------------------------------*/
int obtenerNumerosElemento();
int *crearArreglo(int n);
void ingresarValores(int *arreglo, int validos);
void mostrarArreglo(int *arreglo, int validos);
void liberarMemoria(int *arreglo);
/*----------------------------------EJERCICIO 2------------------------------------*/
void ingresarValoresAdicionales(int **arreglo, int *validos);
/*----------------------------------EJERCICIO 3------------------------------------*/
void guardarArregloEnArchivo(int *arreglo, int validos, const char *nombreArchivo);
void mostrarArchivo(const char *nombreArchivo);
/*----------------------------------EJERCICIO 4------------------------------------*/
nodo* crearNodo(int valor);
void mostrarNodo(nodo* nodoActual);
void mostrarLista(nodo* primerNodo);
int contarNodoParametro(nodo* lista, int numParametro);
nodo* eliminarNodoParametro(nodo* lista, int numParametro);
void encapsularContarEliminar(nodo** lista, int numParametro);
/*----------------------------------EJERCICIO 5------------------------------------*/
int generarNumeroAleatorio(int min, int max);
nodo *buscarUltimoNodo(nodo* lista);
nodo *generarListaNumerosAleatorios(int cantidad_elementos);
int *obtenerNumerosParesRecursivo(nodo* actual, int *cantidad_pares, int **numeros_pares);
void imprimirNumerosPares(int *numeros_pares, int cantidad_pares);
void guardarNumerosImparesEnArchivo(nodo* lista, const char *nombreArchivo);
void liberarMemorialista(nodo* lista);
/*----------------------------------EJERCICIO 6------------------------------------*/
nodoRegistro* crearRegistro(const char* nombre, int edad);
void mostrarRegistro(nodoRegistro* registro);
void insertarEnListaOrdenada(nodoRegistro** lista, nodoRegistro* nuevoRegistro);
void combinarNombresYEdades(nodoRegistro** lista, char nombres[][50], int edades[], int index, int total);
void mostrarListaRegistro(nodoRegistro* lista);

int main()
{
    //Ejercicio 1:
//    printf("Ejercicio 1: \n");
//    int validos = obtenerNumerosElemento();
//    int *arreglo = crearArreglo(validos);
//    ingresarValores(arreglo, validos);
//    mostrarArreglo(arreglo, validos);
//
//    //Ejericico 2:
//    ingresarValoresAdicionales(&arreglo, &validos);
//    mostrarArreglo(arreglo, validos);
//
//    //Ejercicio 3:
//    printf("Cargo el archivo y muestro: \n");
//    guardarArregloEnArchivo(arreglo, validos, "archivoArreglo.bin");
//    mostrarArchivo("archivoArreglo.bin");
//    liberarMemoria(arreglo);
//
//    //Ejercicio 4:
//    nodo* lista = NULL;
//
//    int valor = 1;
//    nodo* nodo1 = crearNodo(valor);
//    lista = nodo1;
//
//    int valor2 = 2;
//    nodo* nodo2 = crearNodo(valor2);
//    nodo1->siguiente = nodo2;
//
//    int valor3 = 3;
//    nodo* nodo3 = crearNodo(valor3);
//    nodo2->siguiente = nodo3;
//
//    int valor4 = 4;
//    nodo* nodo4 = crearNodo(valor4);
//    nodo3->siguiente = nodo4;
//
//    int valor5 = 2;
//    nodo* nodo5 = crearNodo(valor5);
//    nodo4->siguiente = nodo5;
//
//    mostrarLista(lista);
//
//    int valorParametro = 2;
//    encapsularContarEliminar(&lista, valorParametro);
//    mostrarLista(lista);
//
//
//    //Ejercicio 5:
//    srand(time(NULL));
//
//    int elementos_lista = 50;
//    nodo* lista = generarListaNumerosAleatorios(elementos_lista);
//    printf("Lista generada con numeros aleatorios: \n");
//    mostrarLista(lista);
//
//    int cantidad_pares = 0;
//    int *numeros_pares = NULL;
//    numeros_pares = obtenerNumerosParesRecursivo(lista, &cantidad_pares, &numeros_pares);
//    imprimirNumerosPares(numeros_pares, cantidad_pares);
//
//    printf("\nArchivo con los numeros impares \n");
//    guardarNumerosImparesEnArchivo(lista, "numeros_impares.bin");
//    mostrarArchivo("numeros_impares.bin");
//
//    liberarMemorialista(lista);
//    free(numeros_pares);

    //Ejercicio 6:
    char nombres[10][50] = {"Agustin", "Alicia", "Axel", "Carlos", "David", "Emmanuel", "Franco","Gero", "Hilda", "Karen"};
    int edades[10] = {20, 60, 25, 65, 30, 26, 28, 29, 70, 19};

    nodoRegistro* lista = NULL;

    combinarNombresYEdades(&lista, nombres, edades, 0, 10);

    mostrarListaRegistro(lista);



    return 0;
}

/*Ejercicio 1 - Crear un arreglo dinámico con punteros: Escribir un programa que permita al usuario ingresar un número entero n,
luego usando malloc crear un arreglo dinámico de n elementos utilizando punteros y permitir al usuario ingresar valores para completar el arreglo.
Luego, muestra los valores ingresados utilizando punteros.*/

///Funcion para solicitar al usuario el numero de elementos.
int obtenerNumerosElemento()
{
    int n;

    printf("Ingrese el numero de elementos a cargar en el arreglo: ");
    scanf("%i", &n);

    return n;
}

///Función para crear un arreglo dinámico de n elementos utilizando malloc.
int *crearArreglo(int n)
{
    int *arreglo = (int*)malloc(n * sizeof(int));

    if(arreglo == NULL)
    {
        printf("ERROR: No se puede asignar memoria.\n");
        return;
    }

    return arreglo;
}

///Función para solicitar al usuario ingresar valores para completar el arreglo.
void ingresarValores(int *arreglo, int validos)
{
    printf("Ingrese los valores para el arreglo: \n");

    for(int i = 0; i < validos; i++)
    {
        printf("VALORES %i: ", i + 1);
        scanf("%i", &arreglo[i]);
    }

}

///Función para mostrar los valores ingresados utilizando punteros.
void mostrarArreglo(int *arreglo, int validos)
{
    printf("\nValores Agregados: \n");

    for(int i = 0; i < validos; i++)
    {
        printf("%i ", arreglo[i]);
    }
    printf("\n");
}

///Función para liberar la memoria asignada con malloc.
void liberarMemoria(int *arreglo)
{
    free(arreglo);
}

/*Ejercicio 2 - Modificar el programa del Ejercicio 1 para permitir que el usuario ingrese mas elementos al arreglo
(usar realloc con punteros para redimensionar el arreglo dinámico) agregando más elementos al final.
El proceso de redimensionamiento debe ser transparente para el usuario, es decir que el mismo, no debe ingresar el nuevo tamaño para el arreglo,
sino que solo se le pedirá que ingrese los nuevos valores hasta el momento en que decida dejar de hacerlo. Finalmente mostrar el arreglo (modularizar)*/

void ingresarValoresAdicionales(int **arreglo, int *validos)
{
    char agregarValor = 's';

    do
    {
        printf("Quiere agregar el nuevo valor? s/n: ");
        fflush(stdin);
        scanf(" %c", &agregarValor);

        if (agregarValor == 's')
        {
            int nuevoElemento;
            printf("Ingrese el nuevo valor: ");
            scanf("%d", &nuevoElemento);

            (*validos)++;

            *arreglo = (int *)realloc(*arreglo, *validos * sizeof(int));

            if (*arreglo == NULL)
            {
                printf("ERROR: No se pudo asignar memoria.\n");
                return;
            }

            (*arreglo)[*validos - 1] = nuevoElemento;
        }
        else
        {
            printf("\nUsted elegio NO agregar mas elementos.\n");
        }
    }
    while (agregarValor == 's');
}

/*Ejercicio 3 - Escribir un programa que permita al usuario ingresar elementos en un arreglo dinámico utilizando punteros.
Luego, usar fwrite con punteros para guardar el contenido del arreglo en un archivo binario.
Finalmente, usar fread con punteros para cargar y mostrar el contenido del archivo. Modularizar en funciones lo crea conveniente.*/

///Funcion para guardar un arreglo en un archivo binario.
void guardarArregloEnArchivo(int *arreglo, int validos, const char *nombreArchivo)
{
    FILE* archivo = fopen(nombreArchivo, "wb");

    if(archivo == NULL)
    {
        printf("ERROR: No se pudo abrir el archivo. \n");
        return;
    }

    fwrite(arreglo, sizeof(int), validos, archivo);

    fclose(archivo);
}

///Funcion para mostrar el contenido de un archivo binario.
void mostrarArchivo(const char *nombreArchivo)
{
    FILE* archivo = fopen(nombreArchivo, "rb");

    if(archivo == NULL)
    {
        printf("ERROR: No se pudo abrir el archivo \n");
        return;
    }

    int valor;

    while(fread(&valor, sizeof(int),1, archivo) == 1)
    {

        printf("%i ", valor);
    }
    printf("\n");
}

/*Ejercicio 4 – Escribir un programa que permita crear una lista con números enteros y luego buscar y eliminar todos los nodos que coincidan
con la búsqueda de uno de ellos. Tener en cuenta que al buscar un determinado número, el mismo puede aparecer mas de una vez.
Por lo cual se deben eliminar todas sus ocurrencias y luego informar cuantos nodos fueron eliminados.*/

nodo* crearNodo(int valor)
{
    nodo* aux = (nodo*)malloc(sizeof(nodo));

    aux->valor = valor;

    aux->siguiente = NULL;

    return aux;
}

void mostrarNodo(nodo* nodoActual)
{
    printf("[%i] -> ", nodoActual->valor);
}

void mostrarLista(nodo* primerNodo)
{
    nodo* actual = primerNodo;

    printf("LISTA -> ");
    while(actual != NULL)
    {
        mostrarNodo(actual);
        actual = actual->siguiente;
    }
    printf("NULL");
}

///Funcion para buscar y contar los nodos con un numero pasado por parametro.
int contarNodoParametro(nodo* lista, int numParametro)
{
    nodo* actual = lista;

    int encontrado = 0;

    while(actual != NULL)
    {
        if(actual->valor == numParametro)
        {
            encontrado++;
        }

        actual = actual->siguiente;
    }

    return encontrado;
}

///Funcion para eliminar todos los nodos con el valor pasado por parametro.
nodo* eliminarNodoParametro(nodo* lista, int numParametro)
{
    if (lista == NULL)
    {
        return NULL;
    }

    if (lista->valor == numParametro)
    {
        nodo* temp = lista;
        lista = lista->siguiente;
        free(temp);
        return eliminarNodoParametro(lista, numParametro);
    }

    lista->siguiente = eliminarNodoParametro(lista->siguiente, numParametro);

    return lista;
}

void encapsularContarEliminar(nodo** lista, int numParametro)
{
    int cantidadEncontrada = contarNodoParametro(*lista, numParametro);

    if(cantidadEncontrada > 0)
    {
        printf("\n\nSe encontraron y borraron %i nodos con el valor de %i \n", cantidadEncontrada, numParametro);
        *lista = eliminarNodoParametro(*lista, numParametro);
    }
    else
    {
        printf("Nodo NO encontrado\n");
    }
}

/*Ejercicio 5 - Escribir un programa que permita generar una lista con números aleatorios entre 1 y 100 de por lo menos 50 elementos.
Una vez generada la lista, recorrerla para guardar en un arreglo dinámico de 10 elementos (inicialmente), todos los números pares de la lista
y en un archivo binario, todos los números impares. Finalmente mostrar el archivo, el arreglo dinámico y eliminar la lista. Modularizar.*/

int generarNumeroAleatorio(int min, int max)
{
    int numeroAlet = rand() % 100 + 1 ;

    return numeroAlet;
}

nodo *buscarUltimoNodo(nodo* lista)
{
    if(lista == NULL)
    {
        return NULL;
    }

    nodo* ultimo = lista;

    while(ultimo->siguiente != NULL)
    {
        ultimo = ultimo->siguiente;
    }
    return ultimo;
}

nodo *generarListaNumerosAleatorios(int cantidad_elementos)
{
    nodo* lista = NULL;

    for(int i = 0; i < cantidad_elementos; i++)
    {
        int numero_aleatorio = generarNumeroAleatorio(1, 100);
        nodo* nuevoNodo = crearNodo(numero_aleatorio);

        if(lista == NULL)
        {
            lista = nuevoNodo;
        }
        else
        {
            nodo* ultimo = buscarUltimoNodo(lista);
            ultimo->siguiente = nuevoNodo;
        }
    }

    return lista;
}

int *obtenerNumerosParesRecursivo(nodo* actual, int *cantidad_pares, int **numeros_pares)
{
    if(actual == NULL)  // Caso base: si llegamos al final de la lista, devolvemos el arreglo
    {
        return *numeros_pares;
    }

    if(actual->valor % 2 == 0) // Si el valor actual es par, lo agregamos al arreglo de números pares
    {
        (*cantidad_pares)++;// Incrementar la cantidad de números pares encontrados
        *numeros_pares = (int*)realloc(*numeros_pares, (*cantidad_pares) * sizeof(int));// Reasignar memoria para el arreglo de números pares
        (*numeros_pares)[(*cantidad_pares) - 1] = actual->valor; // Agregar el valor par al arreglo de números pares en la última posición
    }

    return obtenerNumerosParesRecursivo(actual->siguiente, cantidad_pares, numeros_pares);
}

void imprimirNumerosPares(int *numeros_pares, int cantidad_pares)
{
    printf("\n\nNumero Pares: \n");

    for(int i = 0; i < cantidad_pares; i++)
    {
        printf("[%i] ", numeros_pares[i]);
    }
    printf("\n");
}

void guardarNumerosImparesEnArchivo(nodo* lista, const char *nombreArchivo)
{
    FILE* archivo_impares = fopen(nombreArchivo, "wb");

    if(archivo_impares == NULL)
    {
        printf("ERROR: No se pudo abrir el archivo. \n");
        return;
    }

    while(lista != NULL)
    {
        if(lista->valor % 2 != 0)
        {
            fwrite(&(lista->valor), sizeof(int),1, archivo_impares);
        }
        lista = lista->siguiente;
    }

    fclose(archivo_impares);
}

void liberarMemorialista(nodo* lista)
{
    nodo* actual = lista;
    nodo* siguiente = NULL;

    while(actual != NULL)
    {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
}

/*Ejercicio 6 - – Escribir un programa que lea edades de un arreglo dinámico de 10 posiciones para combinarlas con 10 nombres leídos
de otro arreglo estático de 10 posiciones. Una vez leídos ambos datos, debe generar un registro con esa info, el cual será agregado
a una lista ordenada que finalmente mostrará por pantalla.*/

// Función para crear un nuevo nodoRegistro
nodoRegistro* crearRegistro(const char* nombre, int edad)
{
    nodoRegistro* nuevoRegistro = (nodoRegistro*)malloc(sizeof(nodoRegistro)); // Reserva memoria para el nuevo nodoRegistro

    if(nuevoRegistro == NULL)
    {
        printf("ERROR: No se pudo asignar memoria al registro: \n");
        return;
    }

    // Copia el nombre y la edad al nuevo nodoRegistro
    strcpy(nuevoRegistro->nombre, nombre);
    nuevoRegistro->edad = edad;
    nuevoRegistro->siguiente = NULL;

    return nuevoRegistro;
}

// Función para mostrar un nodoRegistro
void mostrarRegistro(nodoRegistro* registro)
{
    printf("[%s: %i anios] -> ", registro->nombre, registro->edad);

}

// Función para insertar un nodoRegistro en una lista ordenada
void insertarEnListaOrdenada(nodoRegistro** lista, nodoRegistro* nuevoRegistro)
{
    if(*lista == NULL || strcmp((*lista)->nombre, nuevoRegistro->nombre) >= 0) // Verifica si la lista está vacía o el nuevo registro debe ir al principio
    {
        nuevoRegistro->siguiente = *lista; // Establece el siguiente del nuevo registro como la lista actual
        *lista = nuevoRegistro; // Actualiza la lista para apuntar al nuevo registro
    }
    else
    {
        insertarEnListaOrdenada(&((*lista)->siguiente), nuevoRegistro);
    }
}

// Función para combinar nombres y edades en una lista ordenada
void combinarNombresYEdades(nodoRegistro** lista, char nombres[][50], int edades[], int index, int total)
{
    if(index >= total)
    {
        return;
    }

    nodoRegistro* nuevoRegistro = crearRegistro(nombres[index], edades[index]); // Crea un nuevo nodoRegistro con el nombre y edad actuales

    if(nuevoRegistro != NULL)
    {
        insertarEnListaOrdenada(lista, nuevoRegistro);
    }

    combinarNombresYEdades(lista, nombres, edades, index + 1, total);
}

void mostrarListaRegistro(nodoRegistro* lista)
{
    nodoRegistro* actual = lista;

    printf("\nLISTA -> ");

    while(actual != NULL)
    {
        mostrarRegistro(actual);
        actual = actual->siguiente;
    }
    printf(" NULL \n");
}


