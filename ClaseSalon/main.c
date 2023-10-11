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
nodo* insertarNodo(nodo* lista, nodo* nuevoNodo);


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
    //lista = borraNodo(lista, nombreBorrar);

    printf("\nLISTA CON NODO ELIMINADO: \n");
    mostraLista(lista);

    //Agregar un nodo de forma ORDENADA:
    persona p5 = {"German", 24};
    nodo* nodo5 = crearNodo(p5);
    lista = insertarNodo(lista, nodo5);

    printf("LISTA CON NODO AGREGADO DE FORMA ORDENADA: \n");
    mostraLista(lista);

    //

    return 0;
}


nodo* inicLista() {
   return NULL;
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
    nodo** indirecto = &lista; // Puntero a un puntero que apunta al nodo actual
    nodo* temp;


    while (*indirecto != NULL && strcmp(nombre, (*indirecto)->dato.nombre) != 0)// Se inicia un ciclo mientras el puntero indirecto no sea nulo y el nombre no coincida.
    {
        indirecto = &(*indirecto)->siguiente; // Avanza al siguiente nodo, modificando el puntero indirecto.
    }

    if (*indirecto != NULL) // Si se encontró un nodo con el nombre dado.
    {
        temp = *indirecto; // Se guarda el nodo actual en temp.

        *indirecto = (*indirecto)->siguiente; // El puntero del nodo anterior se actualiza para saltar el nodo actual.

        free(temp);// Se libera la memoria del nodo actual.
    }

    return lista;
}

nodo* insertarNodo(nodo* lista, nodo* nuevoNodo)
{
    nodo* seg = lista;

    if (lista == NULL)
    {
        lista = nuevoNodo;  // Si la lista está vacía, el nuevo nodo se convierte en la lista
    }
    else if (strcmp(nuevoNodo->dato.nombre, lista->dato.nombre) < 0)
    {
        lista = agregarNodoPrincipio(lista, nuevoNodo);  // Si el nuevo nodo debe ir al principio, llamamos a la función agregarNodoPrincipio
    }
    else
    {
        nodo** indirecto = &lista;

        while (seg != NULL && strcmp(nuevoNodo->dato.nombre, seg->dato.nombre) > 0)
        {
            indirecto = &seg->siguiente;  // Avanzamos en la lista usando un puntero doble
            seg = seg->siguiente;
        }
        *indirecto = nuevoNodo;  // Insertamos el nuevo nodo en el lugar correcto
        nuevoNodo->siguiente = seg;  // Ajustamos el enlace del nuevo nodo al siguiente nodo
    }

    return lista;  // Devolvemos la lista actualizada
}
