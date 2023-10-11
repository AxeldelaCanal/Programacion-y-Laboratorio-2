#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char nombre[20];
    int edad;
} Persona;

typedef struct nodo
{
    Persona dato;
    struct nodo* siguiente;
} Nodo;

// Prototipos de funciones
Persona cargarPersona();
void cargarArchivoPersona();
void mostrarArchivo();
void mostrarPersona(Persona nuevaPersona);
Nodo* inicializarLista();
Nodo* crearNodo(Persona nuevaPersona);
Nodo* agregarAlPrincipio(Nodo* head, Nodo* nuevoNodo);
void punto1(Nodo** head);
void mostrarLista(Nodo* head);

int main()
{
    printf("Ejercicios: \n");
    cargarArchivoPersona();
    mostrarArchivo();
    Nodo* head = inicializarLista();
    punto1(&head);
    printf("\nLISTA -> ");
    mostrarLista(head);

    return 0;
}

Persona cargarPersona()
{
    Persona nuevaPersona;

    printf("Ingrese el nombre: \n");
    fflush(stdin);
    scanf("%s", nuevaPersona.nombre);

    printf("Ingrese la edad: \n");
    fflush(stdin);
    scanf("%i", &nuevaPersona.edad);

    return nuevaPersona;
}

void cargarArchivoPersona()
{
    char seguir = 's';
    Persona nuevaPersona;

    FILE* ptr = fopen("archivoPersona.txt", "a");

    if (ptr != NULL)
    {
        printf("Ingreso de Persona: \n");

        while (seguir == 's')
        {
            nuevaPersona = cargarPersona();
            fwrite(&nuevaPersona, sizeof(Persona), 1, ptr);

            printf("Quiere agregar otra persona? s/n \n");
            fflush(stdin);
            scanf(" %c", &seguir);
        }
        fclose(ptr);
    }
    else
    {
        printf("Error al abrir el archivo.\n");
    }
}

void mostrarArchivo()
{
    Persona nuevaPersona;
    FILE* ptr = fopen("archivoPersona.txt", "r");

    if (ptr != NULL)
    {
        while (fread(&nuevaPersona, sizeof(Persona), 1, ptr) > 0)
        {
            mostrarPersona(nuevaPersona);
        }
        fclose(ptr);
    }
    else
    {
        printf("Error al abrir el archivo.\n");
    }
}

void mostrarPersona(Persona nuevaPersona)
{
    printf("\n-----------------\n");
    printf(" NOMBRE: %s \n", nuevaPersona.nombre);
    printf(" EDAD: %i \n", nuevaPersona.edad);
    printf("-----------------\n");
}

Nodo* inicializarLista()
{
    return NULL;
}

Nodo* crearNodo(Persona nuevaPersona)
{
    Nodo* temp = (Nodo*)malloc(sizeof(Nodo));
    if (temp != NULL)
    {
        temp->dato = nuevaPersona;
        temp->siguiente = NULL;
    }
    return temp;
}

Nodo* agregarAlPrincipio(Nodo* head, Nodo* nuevoNodo)
{
    if (head == NULL)
    {
        head = nuevoNodo;
    }
    else
    {
        nuevoNodo->siguiente = head;
        head = nuevoNodo;
    }
    return head;
}

void punto1(Nodo** head)
{
    Persona nuevaPersona;
    Nodo* temp;

    FILE* ptr = fopen("archivoPersona.txt", "r");

    if (ptr != NULL)
    {
        while(fread(&nuevaPersona, sizeof(Persona), 1, ptr) > 0)
        {
            temp = crearNodo(nuevaPersona);
            *head = agregarAlPrincipio(*head, temp);
        }
        fclose(ptr);
    }
    else
    {
        printf("Error al abrir el archivo.\n");
    }
}

void mostrarLista(Nodo* head)
{
    while (head != NULL)
    {
        printf("[%s, %i] -> ", head->dato.nombre, head->dato.edad);
        head = head->siguiente;
    }
    printf("NULL\n");
}
