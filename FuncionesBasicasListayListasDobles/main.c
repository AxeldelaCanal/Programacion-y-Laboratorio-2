#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///Estructuras para Listas simples:
typedef struct
{
    char nombre[20];
    int edad;
} persona;

typedef struct
{
    persona dato;
    struct nodo* siguiente;
} nodo;

///Estructuras para Lista Dobles:


typedef struct vehiculo
{
    char marca[20];
    int valor;
} vehiculo;

typedef struct nodoDoble
{
    vehiculo dato;
    struct nodoDoble* siguiente;
    struct nodoDoble* anterior;
} nodoDoble;


///Estructura para pilas:
//typedef struct
//{
//    int valor;
//    struct nodo* siguiente;
//} Nodo2;
//
//typedef struct{
//     Nodo2* head;
//} Pila;


///Prototipados Listas SIMPLES:
persona cargarPersona();
void cargarArchivoPersona();
void mostrarPersona(persona nuevaPersona);
void mostrarArchivo();
nodo* inicializarLista();
nodo* crearNodo(persona nuevaPersona);
nodo* agregarAlPrincipio(nodo* lista, nodo* nuevoNodo);
void mostrarLista(nodo* lista);
void cargarListaDesdeArchivo(nodo** lista);
nodo* buscarUltimoNodo(nodo* lista);
void insertarAlFinal(nodo** lista, persona nuevaPersona);
void insertarNuevoAlFinal(nodo** lista);
nodo* eliminarNodo(nodo* lista, persona personaEliminar);
void eliminarNodoPorValor(nodo** lista);
nodo* eliminarUltimoNodorecursivo(nodo* lista);
void eliminarUltimoNodo(nodo** lista);
nodo* eliminarPrimerNodoRetorna(nodo* lista);
void eliminarPrimerNodo(nodo** lista);

///Prototipados Listas DOBLES:
vehiculo cargarVehiculo();
void cargarArchivoVehiculo();
void mostrarVehiculo(vehiculo nuevoVehiculo);
void mostrarArchivoVehiculo();
nodoDoble* inicializarListaDoble();
nodoDoble* crearNodoDoble(vehiculo nuevoVehiculo);
void mostrarListaDoble(nodoDoble* lista);
nodoDoble* agregarAlPrincipioDoble(nodoDoble* lista, nodoDoble* nuevoNodo);
void insertarOrdenadoDoble(nodoDoble** lista, vehiculo nuevoVehiculo);
void insertarAlFinalDoble(nodoDoble** lista, vehiculo nuevoVehiculo);
void insertarNuevoAlFinalDoble(nodoDoble** lista);
nodoDoble* eliminarNodoDoble(nodoDoble* lista, vehiculo vehiculoEliminar);
nodoDoble* cargarListaDesdeArchivoDoble();
void eliminarNodoPorValorDoble(nodoDoble** lista);
nodoDoble* eliminarUltimoNodorecursivoDoble(nodoDoble* lista);
void eliminarUltimoNodoDoble(nodoDoble** lista);
nodoDoble* eliminarPrimerNodoRetornaDoble(nodoDoble* lista);
void eliminarPrimerNodoDoble(nodoDoble** lista);





int main()
{
///--------------Funciones listas simples--------------
//    //cargarArchivoPersona();
//    printf("Archivo: \n");
//    mostrarArchivo();
//
//    nodo* lista = inicializarLista();
//    cargarListaDesdeArchivo(&lista);
//    printf("\nLista -> ");
//    mostrarLista(lista);
//
//    printf("\nInsercion de un nuevo dato al final. \n");
//    insertarNuevoAlFinal(&lista);
//    printf("\nLista Actualizada:\n");
//    mostrarLista(lista);
//
//    eliminarNodoPorValor(&lista);
//
//    printf("\nLista con el ultimo nodo ELIMINADO.\n");
//    eliminarUltimoNodo(&lista);
//    mostrarLista(lista);
//
//    printf("\nLista con el primer nodo ELIMINADO. \n");
//    eliminarPrimerNodo(&lista);
//    mostrarLista(lista);

///--------------Funciones listas dobles--------------
    //cargarArchivoVehiculo();
    printf("Archivo Vehiculo: \n");
    mostrarArchivoVehiculo();

    nodoDoble* listaVehiculo = inicializarListaDoble();
    cargarListaDesdeArchivoDoble(&listaVehiculo);
    printf("\nLista -> ");
    mostrarListaDoble(listaVehiculo);

    printf("Insercion de dato al Final: \n");
    insertarNuevoAlFinalDoble(&listaVehiculo);
    mostrarListaDoble(listaVehiculo);

    eliminarNodoPorValorDoble(&listaVehiculo);

    printf("\nLista con el ultimo nodo ELIMINADO.\n");
    eliminarUltimoNodoDoble(&listaVehiculo);
    mostrarListaDoble(listaVehiculo);

    printf("\nLista con el primer nodo ELIMINADO. \n");
    eliminarPrimerNodoDoble(&listaVehiculo);
    mostrarListaDoble(listaVehiculo);









    return 0;
}

///---------------------------------------FUNCIONES BASICAS PARA LISTAS.-------------------------------------------

persona cargarPersona()
{
    persona nuevaPersona;

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
    persona nuevaPersona;

    FILE* ptr = fopen("archivoPersona.txt", "a");

    if(ptr == NULL)
    {
        printf("ERROR: No se puede abrir el archivo. \n");
        return;
    }

    while(seguir == 's')
    {
        nuevaPersona = cargarPersona();

        fwrite(&nuevaPersona, sizeof(persona),1, ptr);

        printf("Quiere agregar otro persona? s/n \n");
        fflush(stdin);
        scanf(" %c", &seguir);
    }
    fclose(ptr);
}

void mostrarPersona(persona nuevaPersona)
{
    printf("\n----------------------------\n");
    printf(" NOMBRE: %s \n", nuevaPersona.nombre);
    printf(" EDAD: %i \n", nuevaPersona.edad);
    printf("----------------------------\n");
}

void mostrarArchivo()
{
    persona nuevaPersona;
    FILE* ptr = fopen("archivoPersona.txt", "r");

    if(ptr == NULL)
    {
        printf("ERROR: No se puede abrir el archivo. \n");
        return;
    }

    while(fread(&nuevaPersona, sizeof(persona),1, ptr) > 0)
    {
        mostrarPersona(nuevaPersona);
    }

    fclose(ptr);
}

///NODOS Y LISTAS
nodo* inicializarLista()
{
    return NULL;
}

nodo* crearNodo(persona nuevaPersona)
{
    nodo* temporal = (nodo*)malloc(sizeof(nodo));

    if(temporal != NULL)
    {
        temporal->dato = nuevaPersona;
        temporal->siguiente = NULL;
    }

    return temporal;
}

nodo* agregarAlPrincipio(nodo* lista, nodo* nuevoNodo)
{
    if(lista == NULL)
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

void mostrarLista(nodo* lista)
{
    while(lista != NULL)
    {
        printf("[%s, %i] -> ", lista->dato.nombre, lista->dato.edad);
        lista = lista->siguiente;
    }
    printf("NULL \n");
}

void insertarOrdenado(nodo** lista, persona nuevaPersona)
{
    nodo* nuevoNodo = crearNodo(nuevaPersona);

    if(nuevoNodo == NULL)
    {
        printf("ERROR: No se pudo crear el nodo. \n");
        return;
    }

    if(*lista == NULL || nuevaPersona.edad < (*lista)->dato.edad)
    {
           nuevoNodo->siguiente = *lista;
           *lista = nuevoNodo;
    }
    else
    {
       insertarOrdenado(&((*lista)->siguiente), nuevaPersona);
    }
}

void cargarListaDesdeArchivo(nodo** lista)
{
    persona nuevaPersona;

    FILE* ptr = fopen("archivoPersona.txt", "r");

    if(ptr == NULL)
    {
        printf("ERROR: No se pudo abrir el archivo. \n");
        return;
    }

    while(fread(&nuevaPersona, sizeof(persona),1, ptr) > 0)
    {
        insertarOrdenado(lista, nuevaPersona);
    }
    fclose(ptr);
}

nodo* buscarUltimoNodo(nodo* lista)
{
    if(lista == NULL || lista->siguiente == NULL)
    {
        return lista;
    }

    return buscarUltimoNodo(lista->siguiente);
}

void insertarAlFinal(nodo** lista, persona nuevaPersona)
{
    nodo* nuevoNodo = crearNodo(nuevaPersona);

    if(*lista == NULL)
    {
        *lista = nuevoNodo;
    }
    else
    {
        nodo* ultimoNodo = buscarUltimoNodo(*lista);
        ultimoNodo->siguiente = nuevoNodo;
    }
}

void insertarNuevoAlFinal(nodo** lista) /// Función auxiliar para facilitar la inserción de un nuevo nodo al final desde el main.
{
    persona nuevaPersona = cargarPersona();
    insertarAlFinal(lista, nuevaPersona);
}

nodo* eliminarNodo(nodo* lista, persona personaEliminar)
{

    if(strcmp(lista->dato.nombre, personaEliminar.nombre) == 0 && lista->dato.edad == personaEliminar.edad)
    {
        nodo* temporal = lista->siguiente;
        free(lista);
        return temporal;
    }

    lista->siguiente = eliminarNodo(lista->siguiente, personaEliminar);
}

void eliminarNodoPorValor(nodo** lista) /// Función auxiliar para facilitar la eliminación de un nodo desde el main.
{
    persona personaAEliminar;

    printf("\nIngrese el nombre de la persona a eliminar: ");
    scanf("%s", personaAEliminar.nombre);

    printf("Ingrese la edad de la persona a eliminar: ");
    scanf("%i", &personaAEliminar.edad);

    *lista = eliminarNodo(*lista, personaAEliminar);

    printf("Lista actualizada -> ");
    mostrarLista(*lista);
}

nodo* eliminarUltimoNodorecursivo(nodo* lista)
{
    if(lista->siguiente == NULL)
    {
        free(lista);
        return NULL;
    }

    lista->siguiente = eliminarUltimoNodorecursivo(lista->siguiente);

    return lista;
}

void eliminarUltimoNodo(nodo** lista) /// Función auxiliar para facilitar la eliminación del último nodo desde el main.
{
    *lista = eliminarUltimoNodorecursivo(*lista);
}

nodo* eliminarPrimerNodoRetorna(nodo* lista)
{
    nodo* temporal = lista->siguiente;
    free(lista);

    return temporal;
}

void eliminarPrimerNodo(nodo** lista) /// Función auxiliar para facilitar la eliminación del primer nodo desde el main.
{
    *lista = eliminarPrimerNodoRetorna(*lista);
}


///---------------------------------------FUNCIONES BASICAS PARA LISTAS DOBLES.-------------------------------------

vehiculo cargarVehiculo()
{
    vehiculo nuevoVehiculo;

    printf("Ingrese la MARCA: \n");
    fflush(stdin);
    scanf("%s", nuevoVehiculo.marca);

    printf("Ingrese el VALOR: \n");
    fflush(stdin);
    scanf("%i", &nuevoVehiculo.valor);

    return nuevoVehiculo;
}

void cargarArchivoVehiculo()
{
    char seguir = 's';

    vehiculo nuevoVehiculo;

    FILE* ptr = fopen("archivoVehiculo.txt", "a");

    if(ptr == NULL)
    {
        printf("ERROR: No se puede abrir el archivo. \n");
        return;
    }

    while(seguir == 's')
    {
        nuevoVehiculo = cargarVehiculo();

        fwrite(&nuevoVehiculo, sizeof(vehiculo),1, ptr);

        printf("Quiere agregar otro vehiculo? s/n \n");
        fflush(stdin);
        scanf("%c", &seguir);
    }
    fclose(ptr);
}

void mostrarVehiculo(vehiculo nuevoVehiculo)
{
    printf("\n-----------------------\n");
    printf(" MARCA: %s \n", nuevoVehiculo.marca);
    printf(" PRECIO: %i \n", nuevoVehiculo.valor);
    printf("-----------------------\n");
}

void mostrarArchivoVehiculo()
{
    vehiculo nuevoVehiculo;

    FILE* ptr = fopen("archivoVehiculo.txt", "r");

    if(ptr == NULL)
    {
        printf("ERROR: No se pudo abrir el archivo. \n");
        return;
    }

    while(fread(&nuevoVehiculo, sizeof(vehiculo),1, ptr) > 0)
    {
        mostrarVehiculo(nuevoVehiculo);
    }

    fclose(ptr);
}

///NODOS Y LISTAS DOBLES
nodoDoble* inicializarListaDoble()
{
    return NULL;
}

nodoDoble* crearNodoDoble(vehiculo nuevoVehiculo)
{
    nodoDoble* temporal = (nodoDoble*)malloc(sizeof(nodoDoble));

    if (temporal != NULL)
    {
        temporal->dato = nuevoVehiculo;
        temporal->siguiente = NULL;
        temporal->anterior = NULL;
    }

    return temporal;
}

void mostrarListaDoble(nodoDoble* lista)
{
    while (lista != NULL)
    {
        printf("[%s, %i] <-> ", lista->dato.marca, lista->dato.valor);
        lista = lista->siguiente;
    }
    printf("NULL \n");
}

nodoDoble* agregarAlPrincipioDoble(nodoDoble* lista, nodoDoble* nuevoNodo)
{
    if (lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nuevoNodo->siguiente = lista;
        lista->anterior = nuevoNodo;
        lista = nuevoNodo;
    }

    return lista;
}

void insertarOrdenadoDoble(nodoDoble** lista, vehiculo nuevoVehiculo)
{
    nodoDoble* nuevoNodo = crearNodoDoble(nuevoVehiculo);

    if (nuevoNodo == NULL)
    {
        printf("ERROR: No se pudo crear el nodo. \n");
        return;
    }

    if (*lista == NULL || nuevoVehiculo.valor < (*lista)->dato.valor)
    {
        nuevoNodo->siguiente = *lista;
        if (*lista != NULL)
            (*lista)->anterior = nuevoNodo;
        *lista = nuevoNodo;
    }
    else
    {
        insertarOrdenadoDoble(&((*lista)->siguiente), nuevoVehiculo);
        if ((*lista)->siguiente != NULL)
            (*lista)->siguiente->anterior = *lista;
    }
}

nodoDoble* cargarListaDesdeArchivoDoble(nodo** lista)
{
    vehiculo nuevoVehiculo;

    FILE* ptr = fopen("archivoVehiculo.txt", "r");

    if (ptr == NULL)
    {
        printf("ERROR: No se pudo abrir el archivo. \n");
        return NULL;
    }


    while (fread(&nuevoVehiculo, sizeof(vehiculo), 1, ptr) > 0)
    {
        insertarOrdenadoDoble(lista, nuevoVehiculo);
    }

    fclose(ptr);

    return lista;
}

void insertarAlFinalDoble(nodoDoble** lista, vehiculo nuevoVehiculo)
{
    nodoDoble* nuevoNodo = crearNodoDoble(nuevoVehiculo);

    if (*lista == NULL)
    {
        *lista = nuevoNodo;
    }
    else
    {
        nodoDoble* ultimoNodo = *lista;
        while (ultimoNodo->siguiente != NULL)
        {
            ultimoNodo = ultimoNodo->siguiente;
        }
        nuevoNodo->anterior = ultimoNodo;
        ultimoNodo->siguiente = nuevoNodo;
    }
}

void insertarNuevoAlFinalDoble(nodoDoble** lista) /// Función auxiliar para facilitar la inserción de un nuevo nodo al final desde el main.
{
    vehiculo nuevoVehiculo = cargarVehiculo();
    insertarAlFinalDoble(lista, nuevoVehiculo);
}

nodoDoble* eliminarNodoDoble(nodoDoble* lista, vehiculo vehiculoEliminar)
{

    if (strcmp(lista->dato.marca, vehiculoEliminar.marca) == 0 && lista->dato.valor == vehiculoEliminar.valor)
    {
        nodoDoble* temporal = lista->siguiente;
        if (temporal != NULL)
        {
            temporal->anterior = NULL;
        }
        free(lista);
        return temporal;
    }

    lista->siguiente = eliminarNodoDoble(lista->siguiente, vehiculoEliminar);

    if (lista->siguiente != NULL)
    {
        lista->siguiente->anterior = lista;
    }

    return lista;
}

void eliminarNodoPorValorDoble(nodoDoble** lista) /// Función auxiliar para facilitar la eliminación de un nodo desde el main.
{
    vehiculo vehiculoAEliminar;

    printf("Ingrese la marca del vehiculo a eliminar: ");
    scanf("%s", vehiculoAEliminar.marca);

    printf("Ingrese el valor del vehiculo a eliminar: ");
    scanf("%i", &vehiculoAEliminar.valor);

    *lista = eliminarNodoDoble(*lista, vehiculoAEliminar);

    printf("Lista Actualizada -> ");
    mostrarListaDoble(*lista);
}

nodoDoble* eliminarUltimoNodorecursivoDoble(nodoDoble* lista)
{
    if(lista->siguiente == NULL)
    {
        free(lista);
        return NULL;
    }

    lista->siguiente = eliminarUltimoNodorecursivoDoble(lista->siguiente);

    return lista;
}

void eliminarUltimoNodoDoble(nodoDoble** lista) /// Función auxiliar para facilitar la eliminación del último nodo desde el main.
{
    *lista = eliminarUltimoNodorecursivoDoble(*lista);
}

nodoDoble* eliminarPrimerNodoRetornaDoble(nodoDoble* lista)
{
    nodoDoble* segundoNodo = lista->siguiente;

    if(segundoNodo != NULL)
    {
        segundoNodo->anterior = NULL;
    }

    free(lista);

    return segundoNodo;
}

void eliminarPrimerNodoDoble(nodoDoble** lista) /// Función auxiliar para facilitar la eliminación del primer nodo desde el main.
{
    *lista = eliminarPrimerNodoRetornaDoble(*lista);
}

///PILAS
/*void inicPila(Pila *p)
{
    p->head = inicializarLista();
}

void apilar(Pila* p, int valor)
{
    Nodo2* nuevoNodo = crearNodoEjercicio4(valor);

    if (p->head == NULL)
    {
        p->head = agregarAlPrincipio(p->head, nuevoNodo);
    }
    else
    {
        nuevoNodo->siguiente = p->head;
        p->head = nuevoNodo;
    }
}

int desapilar(Pila *p)
{
    Nodo2* anterior = p->head;
    p->head = p->head->siguiente;

    return anterior->valor;
}

int tope(Pila *p)
{
    return p->head->valor;
}

int pilavacia(Pila *p)
{
    return p->head == NULL;
}

void mostrar(Pila *p)
{
    printf("\nTOPE---------------------------------------------------BASE\n");
    mostrarListaNodo2(p->head);
    printf("---------------------------------------------------------\n\n");
}

void leer(Pila *p)
{
    int valor = 0;
    printf("\nIngrese un valor: ");
    scanf("%i", &valor);

    Nodo2* nuevoNodo = crearNodoEjercicio4(valor);

    if (p->head == NULL)
    {
        p->head = agregarAlPrincipio(p->head, nuevoNodo);
    }
    else
    {
        nuevoNodo->siguiente = p->head;
        p->head = nuevoNodo;
    }
}
*/









