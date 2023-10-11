#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo
{
    int dato;
    struct Nodo* siguiente;
    struct Nodo* anterior;
} Nodo;

typedef struct
{
    Nodo* frente;
    Nodo* dorso;
} Fila;

///PROTOTIPADOS:
void inicializarFila(Fila* fila);
void insertarEnFila(Fila* fila, int dato);
void cargaFila(Fila* fila);
void muestraFila(Fila* fila);
void liberarFila(Fila* fila);
int buscaDato(Fila* fila, int datoBuscado);
void crearArchivoTexto(Fila* fila);




int main()
{
    Fila fila;
    inicializarFila(&fila);

    printf("Carga de la fila:\n");
    cargaFila(&fila);

    printf("\n");
    muestraFila(&fila);

    int datoBuscado;
    printf("\nIngrese el dato que desea buscar: ");
    scanf("%d", &datoBuscado);

    int ocurrencias = buscaDato(&fila, datoBuscado);

    printf("\nEl dato %d aparece %d veces en la fila.\n", datoBuscado, ocurrencias);

    //crearArchivoTexto(&fila);

    liberarFila(&fila);

    return 0;
}

void inicializarFila(Fila* fila)
{
    fila->frente = NULL;
    fila->dorso = NULL;
}

void insertarEnFila(Fila* fila, int dato)
{
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevoNodo == NULL)
    {
        printf("Error: No se pudo asignar memoria para el nuevo nodo.\n");
        return;
    }

    nuevoNodo->dato = dato;
    nuevoNodo->siguiente = NULL;
    nuevoNodo->anterior = NULL;

    if (fila->dorso == NULL)
    {
        fila->frente = nuevoNodo;
        fila->dorso = nuevoNodo;
    }
    else
    {
        fila->dorso->siguiente = nuevoNodo;
        nuevoNodo->anterior = fila->dorso;
        fila->dorso = nuevoNodo;
    }
}

void cargaFila(Fila* fila)
{
    int dato;
    char continuar;

    do
    {
        printf("Ingrese un dato entero: ");
        scanf("%d", &dato);
        insertarEnFila(fila, dato);

        printf("¿Desea ingresar otro dato? (s/n): ");
        getchar();
        scanf("%c", &continuar);
    }
    while (continuar == 's' || continuar == 'S');
}

///PUNTO 2
void muestraFila(Fila* fila)
{
    Nodo* actual = fila->frente;

    printf("Contenido de la fila:\n");
    while (actual != NULL)
    {
        printf("%d ", actual->dato);
        actual = actual->siguiente;
    }
    printf("\n");
}

void liberarFila(Fila* fila)
{
    Nodo* actual = fila->frente;
    Nodo* siguiente;

    while (actual != NULL)
    {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }

    fila->frente = NULL;
    fila->dorso = NULL;
}

///PUNTO 3
int buscaDato(Fila* fila, int datoBuscado)
{
    Nodo* actual = fila->frente;
    int ocurrencias = 0;

    while (actual != NULL)
    {
        if (actual->dato == datoBuscado)
        {
            ocurrencias++;
        }
        actual = actual->siguiente;
    }

    return ocurrencias;
}

///PUNTO 4
void crearArchivoTexto(Fila* fila)
{
    char nombreArchivo[100];

    printf("Ingrese el nombre del archivo de texto: ");
    scanf("%s", nombreArchivo);

    FILE* archivo = fopen(nombreArchivo, "w");

    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    Nodo* actual = fila->frente;

    while (actual != NULL)
    {
        fprintf(archivo, "%d\n", actual->dato);
        actual = actual->siguiente;
    }

    fclose(archivo);
    printf("Contenido de la fila guardado en el archivo \"%s\".\n", nombreArchivo);
}

