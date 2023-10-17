#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int nota;
    int legajo;
    char nombreApe[40];
    char materia[40];
    int idMateria;
} registroArchivo;

typedef struct
{
    int nota;
    int legajo;
    char nombreApe[40];
} notaAlumno;

typedef struct _nodo
{
    notaAlumno dato;
    struct _nodo* siguiente;
} nodo;

typedef struct
{
    int idMateria;
    char materia[40];
    nodo* listaDeNotas;
} celda;

///PROTOTIPADOS:
nodo* crearNodo(int nota, int legajo, char nombreApe[]);
int buscarPosMateria(celda arreglo[], char materia[], int validos);
int agregarMateria(celda arreglo[], char materia[], int validos);
nodo* agregaAlPpio(nodo* lista, nodo* nuevoNodo);
int alta(celda arreglo[], char materia[], int nota, int legajo, char nombreApe[], int validos);
int ingresarnotas(celda arreglo[], int dimension);
void mostrarNotasPorMateria(celda arreglo[], int validos, char materia[]);



int main()
{
    celda arreglo[20];

    int validos = ingresarnotas(arreglo, 20);

    char materia[40];
    printf("\nIngrese la materia para mostrar las notas: ");
    scanf("%s", materia);

    mostrarNotasPorMateria(arreglo, validos, materia);

    return 0;
}


// Función para crear un nuevo nodo
nodo* crearNodo(int nota, int legajo, char nombreApe[])
{
    nodo* aux = (nodo*)malloc(sizeof(nodo));
    aux->dato.nota = nota;
    aux->dato.legajo = legajo;
    strcpy(aux->dato.nombreApe, nombreApe);
    aux->siguiente = NULL;

    return aux;
}

// Función para buscar la posición de una materia en el arreglo
int buscarPosMateria(celda arreglo[], char materia[], int validos)
{
    for (int i = 0; i < validos; i++)
    {
        if (strcmpi(arreglo[i].materia, materia) == 0)
        {
            return i;  // Si la materia se encuentra, se devuelve su posición
        }
    }
    return -1;  // Si no se encuentra la materia, se devuelve -1
}

// Función para agregar una nueva materia al arreglo
int agregarMateria(celda arreglo[], char materia[], int validos)
{
    arreglo[validos].idMateria = validos;  // Asignamos el índice como idMateria
    strcpy(arreglo[validos].materia, materia);  // Se copia el nombre de la materia
    arreglo[validos].listaDeNotas = NULL;  // Se inicializa la lista de notas como NULL
    validos++;

    return validos;
}

// Función para agregar un nodo al principio de una lista enlazada
nodo* agregaAlPpio(nodo* lista, nodo* nuevoNodo)
{
    if (lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nuevoNodo->siguiente = lista;
        lista = nuevoNodo;
    }
    return lista;
}

// Función para dar de alta un estudiante en una materia
int alta(celda arreglo[], char materia[], int nota, int legajo, char nombreApe[], int validos)
{
    nodo* aux = crearNodo(nota, legajo, nombreApe);  // Se crea un nuevo nodo con los datos del estudiante
    int pos = buscarPosMateria(arreglo, materia, validos);  // Se busca la posición de la materia en el arreglo

    if (pos == -1)
    {
        validos = agregarMateria(arreglo, materia, validos);  // Si la materia no existe, se agrega al arreglo
        pos = validos - 1;  // La posición es la última del arreglo
    }
    arreglo[pos].listaDeNotas = agregaAlPpio(arreglo[pos].listaDeNotas, aux);  // Se agrega el nodo a la lista de notas de la materia

    return validos;
}

// Función para ingresar notas y detalles de estudiantes
int ingresarnotas(celda arreglo[], int dimension)
{
    int nota;
    int legajo;
    char nombreApe[40];
    char materia[40];
    char salir = 's';
    int validos = 0;

    while (salir == 's' && validos < dimension)
    {
        printf("\ningrese la materia: ");
        fflush(stdin);
        gets(&materia);

        printf("\ningrese un nota: ");
        fflush(stdin);
        scanf("%d", &nota);

        printf("\ningrese un legajo: ");
        fflush(stdin);
        scanf("%d", &legajo);

        printf("\ningrese un nombre y apellido: ");
        fflush(stdin);
        gets(&nombreApe);

        validos = alta(arreglo, materia, nota, legajo, nombreApe, validos);  // Se da de alta al estudiante en la materia

        printf("Desea continuar presione 's'");
        salir = getchar();  // Se obtiene la opción del usuario para continuar
    }
    return validos;
}

// Función para mostrar las notas de una materia
void mostrarNotasPorMateria(celda arreglo[], int validos, char materia[])
{
    int pos = buscarPosMateria(arreglo, materia, validos);  // Se busca la posición de la materia en el arreglo

    if (pos != -1)
    {
        printf("Notas para la materia %s:\n", arreglo[pos].materia);

        nodo* actual = arreglo[pos].listaDeNotas;  // Se obtiene la lista de notas de la materia

        while (actual != NULL)
        {
            printf("Legajo: %d, Nombre y Apellido: %s, Nota: %d\n", actual->dato.legajo, actual->dato.nombreApe, actual->dato.nota);
            actual = actual->siguiente;
        }
    }
    else
    {
        printf("No se encontro la materia especificada.\n");
    }
}
