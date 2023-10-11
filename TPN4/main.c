#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


///Prototipados:
nodo* crearNodo(persona dato);
void mostrarNodo(nodo* nodoActual);
void mostraLista(nodo* primerNodo);
nodo* agregarNodoPrincipio(nodo* lista, nodo* nuevoNodo);
nodo* buscarUltimoNodo(nodo* lista);
nodo* buscarNodoParametro(nodo* lista, char nombre[20]);
nodo* agregarNodoFinal(nodo* lista, nodo* nuevoNodo);
nodo* borraNodo(nodo* lista, char nombre[20]);
nodo* agregarEnOrden(nodo* lista, nodo* nuevoNodo);
nodo* borrarTodaLaLista(nodo* lista);
int sumarEdadesLista(nodo* lista);
nodo* eliminarPrimerNodo(nodo* lista);
nodo* eliminarUltimoNodo(nodo* lista);

int main()
{
    nodo* lista = NULL;

    //Creo y Muestro los nodos/lista:
    persona p1 = {"Alicia", 60};
    nodo* nodo1 = crearNodo(p1);
    lista = nodo1;

    persona p2 = {"Axel", 25};
    nodo* nodo2 = crearNodo(p2);
    nodo1->siguiente = nodo2;

    printf("LISTA ORIGINAL: \n");
    mostraLista(lista);

    //Agregro un nuevo Nodo al PRINCIPIO:
    persona p3 = {"Fabian", 30};
    nodo* nodo3 = crearNodo(p3);
    lista = agregarNodoPrincipio(lista, nodo3);

    printf("\nLISTA ACTUALIZADA: \n");
    mostraLista(lista);

    //Busco el ultimo nodo de la lista:
    nodo* ultimoNodo = buscarUltimoNodo(lista);
    printf("\nEL ULTIMO NODO ES: \n");
    mostrarNodo(ultimoNodo);


    //Busco un nodo a travez de un parametro
    char nombreParametro[20] = "Alicia";
    nodo* nodoBuscado = buscarNodoParametro(lista, nombreParametro);


    //Agrego un nuevo Nodo al FINAL:
    persona p4 = {"Natasha", 28};
    nodo* nodo4 = crearNodo(p4);
    lista = agregarNodoFinal(lista, nodo4);

    printf("\nLISTA ACTULIZADA 2.0: \n");
    mostraLista(lista);


    //Elimino un nodo:
    char nombreBorrar[20] = "Axel";
    lista = borraNodo(lista, nombreBorrar);

    printf("\nLISTA CON NODO ELIMINADO: \n");
    mostraLista(lista);


    //Agregar Nodo en ORDEN
    persona p5 = {"Agustin", 23};
    nodo* nodo5 = crearNodo(p5);
    lista = agregarEnOrden(lista, nodo5);

    printf("\nLISTA CON NODO AGREGADADO EN ORDEN: \n");
    mostraLista(lista);


    //Borrar Toda la LISTA
    printf("ELIMINA TODA LA LISTA: \n");
    //lista = borrarTodaLaLista(lista);


    //Suma las edades de todos los Nodos (Comentar la linea 94 para poder hacer la suma)
    int sumaEdades = sumarEdadesLista(lista);
    printf("La suma de las edades es de: %i \n", sumaEdades);


    //Elimina el primer Nodo de la Lista
    lista = eliminarPrimerNodo(lista);

    printf("\nLISTA CON EL PRIMER NODO ELIMINADO: \n");
    mostraLista(lista);


    //Elimina el ULTIMO Nodo de la Lista
    lista = eliminarUltimoNodo(lista);

    printf("\nLISTA CON EL ULTIMO NODO ELIMINADO: \n");
    mostraLista(lista);

    return 0;
}

nodo* crearNodo(persona dato)
{
    nodo* aux = (nodo*)malloc(sizeof(nodo));

    aux->dato = dato;

    aux->siguiente = NULL;

    return aux;
}

void mostrarNodo(nodo* nodoActual)
{
    printf("Nombre: %s\n", nodoActual->dato.nombre);
    printf("Edad: %i\n", nodoActual->dato.edad);
    printf("--------------------\n");

}

void mostraLista(nodo* primerNodo)
{
    nodo* actual = primerNodo;

    while(actual != NULL)
    {
        mostrarNodo(actual);
        actual = actual->siguiente;
    }
}

nodo* agregarNodoPrincipio(nodo* lista, nodo* nuevoNodo)
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

nodo* buscarUltimoNodo(nodo* lista)
{
    nodo* seg = lista;

    if(seg != NULL)
    {
        while(seg->siguiente != NULL)
        {
            seg = seg->siguiente;
        }
    }
    return seg;
}

nodo* buscarNodoParametro(nodo* lista, char nombre[20])
{
    nodo* seg = lista;

    while((seg != NULL) && (strcmp(nombre, seg->dato.nombre) != 0))
    {
        seg = seg->siguiente;
    }

    if (seg != NULL)
    {
        printf("\nNODO ENCONTRADO:\n");
        mostrarNodo(seg);
    }
    else
    {
        printf("\nNODO NO ENCONTRADO.\n");
    }

    return seg;
}

nodo* agregarNodoFinal(nodo* lista, nodo* nuevoNodo)
{
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nodo* ultimo = buscarUltimoNodo(lista);
        ultimo->siguiente = nuevoNodo;
    }
    return lista;
}

nodo* borraNodo(nodo* lista, char nombre[20])
{
    nodo** indirecto = &lista; //Puntero a un puntero que apunta al nodo actual
    nodo* temp; //Puntero que se utiliza para mantener temporalmente el nodo que se va a eliminar

    while(*indirecto != NULL && strcmp(nombre, (*indirecto)->dato.nombre) != 0)
    {
        indirecto = &(*indirecto)->siguiente; //Actualiza "indirecto" para que apunte al siguiente nodo en la lista
    }

    if(*indirecto != NULL) //Verifica si se encontr  el nodo con el nombre deseado.
    {
        temp = *indirecto; //Almacena el puntero al nodo que se eliminar  en la variable "temp".
        *indirecto = (*indirecto)->siguiente; //Actualiza el puntero para eliminar el nodo de la lista
        free(temp); //Libera la memoria del nodo eliminado.
    }

    return lista; //Devuelve la lista actualizada.
}

nodo* agregarEnOrden(nodo* lista, nodo* nuevoNodo)
{
    nodo** actual = &lista; //Puntero a puntero que apunta al nodo actual.

    while(*actual != NULL && strcmp(nuevoNodo->dato.nombre, (*actual)->dato.nombre) >= 0)
    {
        actual = &((*actual)->siguiente); //Avanza al siguiente nodo si es necesario.
    }

    nuevoNodo->siguiente = *actual; //Enlaza el nuevo nodo al nodo siguiente.
    *actual = nuevoNodo; //Actualiza el puntero anterior para apuntar al nuevo nodo.

    return lista;
}

nodo* borrarTodaLaLista(nodo* lista)
{
    while(lista != NULL)
    {
        nodo* temp = lista;
        lista = lista->siguiente; //Avanzar al siguiente nodo.
        free(temp); //Liberar la memoria del nodo actual.
    }
    return NULL; //Devolver NULL para indicar que la lista est  vac a.
}

int sumarEdadesLista(nodo* lista)
{
    int suma = 0;
    nodo* seg = lista;

    while(seg != NULL)
    {
        suma = suma + seg->dato.edad;
        seg = seg->siguiente;
    }

    return suma;
}

nodo* eliminarPrimerNodo(nodo* lista)
{
    if(lista != NULL)
    {
        nodo* temp = lista;
        lista = lista->siguiente;
        free(temp);
    }
    return lista;
}

nodo* eliminarUltimoNodo(nodo* lista)
{
    if(lista != NULL)
    {
        nodo* ultimo = buscarUltimoNodo(lista); //Busca el  ltimo nodo de la lista.
        nodo* actual = lista;

        while(actual->siguiente != ultimo)
        {
            actual = actual->siguiente; //Avanza al siguiente nodo hasta el pen ltimo.
        }

        actual->siguiente = NULL; //Desconecta el  ltimo nodo del pen ltimo.
        free(ultimo); //Libera la memoria del  ltimo nodo.
    }
    return lista;
}
