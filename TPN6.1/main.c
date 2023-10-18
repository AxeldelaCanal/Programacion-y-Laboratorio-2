/*#include <stdio.h>
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
nodo* agregarAlPrincipio(nodo* lista, nodo* nuevoNodo);
int cargarEnArreglo(celda arreglo[], char materia[], int nota, int legajo, char nombreApe[], int validos);
int ingresarNotas(celda arreglo[], int dimension, int validos);
void mostrarNotasPorMateria(celda arreglo[], int validos, char materia[]);



int main()
{
    celda arreglo[20];

    int validos = ingresarNotas(arreglo, 20, validos);

    char materia[40];
    printf("\nIngrese la materia para mostrar las notas: ");
    scanf("%s", materia);

    mostrarNotasPorMateria(arreglo, validos, materia);

    return 0;
}


// Función para ingresar notas y detalles de estudiantes
int ingresarNotas(celda arreglo[], int dimension, int validos)
{
    int nota;
    int legajo;
    char nombreApe[40];
    char materia[40];
    char salir = 's';

    while (salir == 's' && validos < dimension)
    {
        printf("Ingrese la materia: ");
        fflush(stdin);
        gets(&materia);

        printf("\nIngrese un nota: ");
        fflush(stdin);
        scanf("%d", &nota);

        printf("\nIngrese un legajo: ");
        fflush(stdin);
        scanf("%d", &legajo);

        printf("\nIngrese un nombre y apellido: ");
        fflush(stdin);
        gets(&nombreApe);

        validos = cargarEnArreglo(arreglo, materia, nota, legajo, nombreApe, validos);  // Se da de alta al estudiante en la materia

        printf("\nDesea continuar s/n \n");
        fflush(stdin);
        scanf("%c", &salir);
    }
    return validos;
}



*/
///---------------------------------------------------------------------------------------------------------------------------------------
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
registroArchivo cargarRegistro();
void cargarArchivo();
void mostrarRegistro(registroArchivo nuevoRegistro);
void mostrarArchivo();



int main()
{
    celda arreglo[100];  // Tamaño máximo del arreglo
    int validos = 0;

    //cargarArchivo();
    pasarDeArchivoToADL(arreglo, &validos);
    mostrarArchivoArreglo(arreglo, validos);

    return 0;
}



registroArchivo cargarRegistro()
{
    registroArchivo nuevoRegistro;

    printf("Ingrese la Nota: ");
    fflush(stdin);
    scanf("%i", &nuevoRegistro.nota);

    printf("\nIngrese el legajo: ");
    fflush(stdin);
    scanf("%i", &nuevoRegistro.legajo);

    printf("\nIngrese Nombre y Apellido: ");
    fflush(stdin);
    gets(&nuevoRegistro.nombreApe);

    printf("\nIngrese la materia: ");
    fflush(stdin);
    gets(&nuevoRegistro.materia);

    printf("\nIngrese id materia: ");
    fflush(stdin);
    scanf("%i", &nuevoRegistro.idMateria);

    return nuevoRegistro;
}

void cargarArchivo()
{
    char seguir = 's';
    registroArchivo nuevoRegistro;

    FILE* ptr = fopen("archivoRegistro.txt", "a");

    if(ptr != NULL)
    {
        printf("REGISTROS: \n");

        while(seguir == 's')
        {
            nuevoRegistro = cargarRegistro();
            fwrite(&nuevoRegistro, sizeof(registroArchivo),1, ptr);

            printf("Quiere cargar otro registro? s/n\n");
            fflush(stdin);
            scanf("%c", &seguir);
        }
        fclose(ptr);
    }
    else
    {
        printf("ERROR: No se pudo abrir el archivo.");
    }
}

void mostrarRegistro(registroArchivo nuevoRegistro)
{
    printf("\n-------------------------------------------\n");
    printf("NOTA: %i\n", nuevoRegistro.nota);
    printf("LEGAJO: %i\n", nuevoRegistro.legajo);
    printf("NOMBRE Y APELLIDO: %s\n", nuevoRegistro.nombreApe);
    printf("MATERIO: %s\n", nuevoRegistro.materia);
    printf("ID MATERIA: %i\n", nuevoRegistro.idMateria);
    printf("-------------------------------------------\n");

}

void mostrarArchivo()
{
    registroArchivo nuevoRegistro;
    FILE* ptr = fopen("archivoAprobados.txt", "r");

    if(ptr != NULL)
    {
        while(fread(&nuevoRegistro, sizeof(registroArchivo),1, ptr) > 0)
        {
            mostrarRegistro(nuevoRegistro);
        }
        fclose(ptr);
    }
    else
    {
        printf("ERROR: No se pudo abrir el archivo.");
    }
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
nodo* agregarAlPrincipio(nodo* lista, nodo* nuevoNodo)
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
int cargarEnArreglo(celda arreglo[], char materia[], int nota, int legajo, char nombreApe[], int validos)
{
    nodo* aux = crearNodo(nota, legajo, nombreApe);  // Se crea un nuevo nodo con los datos del estudiante
    int pos = buscarPosMateria(arreglo, materia, validos);  // Se busca la posición de la materia en el arreglo

    if (pos == -1)
    {
        validos = agregarMateria(arreglo, materia, validos);  // Si la materia no existe, se agrega al arreglo
        pos = validos - 1;  // La posición es la última del arreglo
    }
    arreglo[pos].listaDeNotas = agregarAlPrincipio(arreglo[pos].listaDeNotas, aux);  // Se agrega el nodo a la lista de notas de la materia

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


///… pasarDeArchivoToADL(…) ---> esta función recorrerá el archivo y pasará la información al arreglo de listas
///(utilizando las funciones necesarias que usted ya codificó).
void pasarDeArchivoToADL(celda arreglo[], int *validos)
{
    FILE *ptr = fopen("archivoRegistro.txt", "r");

    if (ptr != NULL)
    {
        registroArchivo nuevoRegistro;
        while (fread(&nuevoRegistro, sizeof(registroArchivo), 1, ptr) > 0)
        {
            *validos = cargarEnArreglo(arreglo, nuevoRegistro.materia, nuevoRegistro.nota, nuevoRegistro.legajo, nuevoRegistro.nombreApe, *validos);
        }
        fclose(ptr);
    }
    else
    {
        printf("ERROR: No se pudo abrir el archivo.");
    }
}


void mostrarArchivoArreglo(celda arreglo[], int validos)
{
    printf("----------------------------MATERIAS Y NOTAS:----------------------------\n");

    for (int i = 0; i < validos; i++)
    {
        printf("MATERIA: %s\n", arreglo[i].materia);
        printf("ID Materia: %d\n", arreglo[i].idMateria);

        nodo *actual = arreglo[i].listaDeNotas;

        if (actual != NULL)
        {
            while (actual != NULL)
            {
                printf("Legajo: %d, Nombre y Apellido: %s, NOTAS: %d\n", actual->dato.legajo, actual->dato.nombreApe, actual->dato.nota);
                actual = actual->siguiente;
            }
        }
        else
        {
            printf("No hay notas registradas para esta materia.\n");
        }
        printf("-------------------------------------------\n");
    }
}



