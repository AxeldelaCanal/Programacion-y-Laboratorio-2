#include <stdio.h>
#include <stdlib.h>

typedef struct nodoDoble
{
    int dato;
    struct nodoDoble* siguiente;
    struct nodoDoble* anterior;
} nodoDoble;


nodoDoble* inicializarListaDoble();
nodoDoble* crearNodo(int dato);
void mostrarListaDoble(nodoDoble* lista);
nodoDoble* eliminarUltimoNodo(nodoDoble* lista);
void eliminarUltimoNodoDoble(nodoDoble** lista);
nodoDoble* ultimoNodo(nodoDoble* lista);

int main()
{
    ///Ejercicio 1.)
    printf("--Ejercicio 1: \n");
    nodoDoble* lista = inicializarListaDoble();

    int valor1 = 10;
    nodoDoble* nodo1 = crearNodo(valor1);

    int valor2 = 20;
    nodoDoble* nodo2 = crearNodo(valor2);

    int valor3 = 30;
    nodoDoble* nodo3 = crearNodo(valor3);

    int valor4 = 20;
    nodoDoble* nodo4 = crearNodo(valor4);

    int valor5 = 10;
    nodoDoble* nodo5 = crearNodo(valor5);

    lista = nodo1;
    nodo1->siguiente = nodo2;
    nodo2->anterior = nodo1;
    nodo2->siguiente = nodo3;
    nodo3->anterior = nodo2;
    nodo3->siguiente = nodo4;
    nodo4->anterior = nodo3;
    nodo4->siguiente = nodo5;
    nodo5->anterior = nodo4;
    nodo5->siguiente = NULL;

    printf("*LISTA: \n");
    mostrarListaDoble(lista);

    //eliminarUltimoNodoDoble(&lista);
    printf("\n*Lista despues de borrar el ultimo nodo: \n");
    mostrarListaDoble(lista);

    ///Ejercicio 2.)
    printf("\n--Ejercicio 2: \n");

    nodoDoble* inicio = lista;
    nodoDoble* fin = ultimoNodo(lista);

    if(listaCapicua(&inicio, fin))
    {
        printf("La lista es capicua.\n");
    }
    else
    {
        printf("La lista NO es capicua. \n");
    }



    return 0;
}

///Ejercicio 1:

nodoDoble* inicializarListaDoble()
{
    return NULL;
}

nodoDoble* crearNodo(int dato)
{
    nodoDoble* nuevoNodo = (nodoDoble*)malloc(sizeof(nodoDoble));

    if(nuevoNodo == NULL)
    {
        printf("ERROR: No se pudo asignar memoria para el nodo. \n");
        return;
    }

    nuevoNodo->dato = dato;
    nuevoNodo->siguiente = NULL;
    nuevoNodo->anterior = NULL;

    return nuevoNodo;
}

void mostrarListaDoble(nodoDoble* lista)
{
    printf(" LISTA <-> ");
    while(lista != NULL)
    {
        printf("[%i] <-> ", lista->dato);
        lista = lista->siguiente;
    }
    printf("NULL \n");
}

nodoDoble* eliminarUltimoNodo(nodoDoble* lista)
{
    if(lista->siguiente == NULL)
    {
        free(lista);
        return NULL;
    }

    lista->siguiente = eliminarUltimoNodo(lista->siguiente);

    return lista;
}

void eliminarUltimoNodoDoble(nodoDoble** lista)
{
   *lista = eliminarUltimoNodo(*lista);
}

///Ejercicio 2:

nodoDoble* ultimoNodo(nodoDoble* lista)
{
    if(lista == NULL)
    {
        return NULL;
    }

    while(lista->siguiente != NULL)
    {
        lista = lista->siguiente;
    }

    return lista;
}

int listaCapicua(nodoDoble** inicio, nodoDoble* fin)
{
    // Caso base: Cuando el inicio y el fin se encuentran o son nulos.
    if (*inicio == fin || *inicio == NULL || fin == NULL) {
        return 1;
    }

    // Compara los datos de los nodos.
    if ((*inicio)->dato != fin->dato) {
        return 0;
    }

    // Avanza al siguiente nodo y retrocede al anterior nodo.
    *inicio = (*inicio)->siguiente;

    // Retrocede al anterior nodo.
    fin = fin->anterior;

    // Llama recursivamente para verificar el siguiente par de nodos.
    return listaCapicua(inicio, fin);
}

