#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int legajo;
    char nombre[20];
    int edad;
} persona;

typedef struct nodoArbol
{
    persona dato;
    struct nodoArbol * izq;
    struct nodoArbol * der;
} nodoArbol;

typedef struct nodo
{
    persona dato;
    struct nodo* sig;
} nodo;


///PROTOTIPADOS:
nodoArbol* inicArbol();
nodoArbol* crearNodoArbol(persona dato);
nodoArbol* insertar(nodoArbol* arbol, persona dato);
nodoArbol* ingresarNuevoNodo(nodoArbol* arbol);
void preorder(nodoArbol* arbol);
void inorden(nodoArbol* arbol);
void postorden(nodoArbol* arbol);
nodo* inicLista();
nodo* crearNodo(persona dato);
nodo* buscarUltimo(nodo* lista);
nodo* agregarAlFinal(nodo* lista, persona dato);
nodo* arbolALista(nodoArbol* arbol, nodo* lista);
void mostrarLista(nodo* lista);
nodoArbol* buscarLegajo(nodoArbol* arbol, int legajoBuscado);
void legajoEncontrado(nodoArbol* nodoBuscado);
nodoArbol* buscarNombre(nodoArbol* arbol, char nombreBuscado[]);
void nombreEncontrado(nodoArbol* nodoBuscadoNombre);
int calcularAltura(nodoArbol* arbol);
int contarNodos(nodoArbol* arbol);
int contarHojas(nodoArbol* arbol);
nodoArbol* encotrarSucesorInorden(nodoArbol* arbol);
nodoArbol* borrarNodo(nodoArbol* arbol, int legajo);



int main()
{
    nodoArbol* arbol;
    arbol = inicArbol();

    ///PUNTO 1:
    arbol = ingresarNuevoNodo(arbol);

    ///PUNTO 2:
    printf("PREORDEN: \n");
    preorder(arbol);

    printf("\nINORDEN: \n");
    inorden(arbol);

    printf("\nPOSTORDEN: \n");
    postorden(arbol);

    ///PUNTO 3:
    nodo* lista;
    lista = inicLista();

    lista = arbolALista(arbol, lista);
    printf("\nLISTA: \n");
    mostrarLista(lista);

    ///PUNTO 4:
    int legajoBuscado = 0;
    printf("\nIngrese el LEGAJO a buscar: ");
    fflush(stdin);
    scanf("%i", &legajoBuscado);

    nodoArbol* nodoBuscado = buscarLegajo(arbol, legajoBuscado);
    legajoEncontrado(nodoBuscado);

    ///PUNTO 5:
    char nombreBuscado[30];
    printf("\nIngrese el Nombre a buscar: ");
    fflush(stdin);
    gets(&nombreBuscado);

    nodoArbol* nodoBuscadoNombre = buscarNombre(arbol, nombreBuscado);
    nombreEncontrado(nodoBuscadoNombre);

    ///PUNTO 6:
    int alturaArbol = calcularAltura(arbol);
    printf("\nLa altura del arbol es de: %i", alturaArbol);

    ///PUNTO 7:
    int cantidadNodos = contarNodos(arbol);
    printf("\n\nHay %i nodos en el arbol.\n", cantidadNodos);

    ///PUNTO 8:
    int cantidadHojas = contarHojas(arbol);
    printf("\nHay %i hojas en el arbol.\n", cantidadHojas);

    ///PUNTO 9:
    int legajoBorrar = 0;
    printf("Ingrese el legajo a borra: ");
    fflush(stdin);
    scanf("%i", &legajoBorrar);

    arbol = borrarNodo(arbol, legajoBorrar);
    printf("\nARBOL con nodo BORRADO: \n");
    inorden(arbol);

    return 0;
}

nodoArbol* inicArbol()
{
    return NULL;
}

///PUNTO 1: Hacer una función que permita ingresar nuevos nodos manteniendo el árbol ordenado (por legajo).
nodoArbol* crearNodoArbol(persona dato)
{
    nodoArbol* aux = (nodoArbol*)malloc(sizeof(nodoArbol));
    aux->dato = dato;
    aux->der = NULL;
    aux->izq = NULL;

    return aux;
}

nodoArbol* insertar(nodoArbol* arbol, persona dato)
{
    if(arbol == NULL)
    {
        arbol = crearNodoArbol(dato);
    }
    else
    {
        if(dato.legajo > arbol->dato.legajo)
        {
            arbol->der = insertar(arbol->der, dato);
        }
        else
        {
            arbol->izq = insertar(arbol->izq, dato);
        }
    }

    return arbol;
}

nodoArbol* ingresarNuevoNodo(nodoArbol* arbol)
{
    char continuar;

    do
    {
        persona dato;

        printf("Ingrese Nombre: ");
        fflush(stdin);
        gets(&dato.nombre);

        printf("Ingrese edad: ");
        fflush(stdin);
        scanf("%i", &dato.edad);

        printf("Ingrese legajo: ");
        fflush(stdin);
        scanf("%i", &dato.legajo);

        arbol = insertar(arbol, dato);

        printf("Quiere cargar otra persona? s/n \n");
        fflush(stdin);
        scanf("%c", &continuar);
    }
    while(continuar == 's' || continuar == 'S');

    return arbol;
}

///PUNTO 2: Hacer tres funciones, una función que recorra el árbol y muestre su contenido en orden (verificar cual de los recorridos es conveniente
///(inorder, posorder o preorder). Modularizar
void preorder(nodoArbol* arbol)
{
    if(arbol != NULL)
    {
        printf("LEGAJO: %i, NOMBRE: %s, EDAD: %i\n", arbol->dato.legajo, arbol->dato.nombre, arbol->dato.edad);
        preorder(arbol->izq);
        preorder(arbol->der);
    }
}

void inorden(nodoArbol* arbol)
{
    if(arbol != NULL)
    {
        inorden(arbol->izq);
        printf("LEGAJO: %i, NOMBRE: %s, EDAD: %i\n", arbol->dato.legajo, arbol->dato.nombre, arbol->dato.edad);
        inorden(arbol->der);
    }
}

void postorden(nodoArbol* arbol)
{
    if(arbol != NULL)
    {
        postorden(arbol->izq);
        postorden(arbol->der);
        printf("LEGAJO: %i, NOMBRE: %s, EDAD: %i\n", arbol->dato.legajo, arbol->dato.nombre, arbol->dato.edad);
    }
}

///PUNTO 3: Hacer una función que copie el contenido del árbol en una lista simplemente enlazada.
nodo* inicLista()
{
    return NULL;
}

nodo* crearNodo(persona dato)
{
    nodo* aux = (nodo*)malloc(sizeof(nodo));
    aux->dato = dato;
    aux->sig = NULL;

    return aux;
}

nodo* buscarUltimo(nodo* lista)
{
    if(lista == NULL || lista->sig == NULL)
    {
        return lista;
    }

    return buscarUltimo(lista->sig);
}

nodo* agregarAlFinal(nodo* lista, persona dato)
{
    nodo* aux = crearNodo(dato);

    if(lista == NULL)
    {
        lista = aux;
    }
    else
    {
        nodo* ultimo = buscarUltimo(lista);
        ultimo->sig = aux;
    }

    return lista;
}

nodo* arbolALista(nodoArbol* arbol, nodo* lista)
{
    if(arbol != NULL)
    {
        lista = agregarAlFinal(lista, arbol->dato);
        arbolALista(arbol->izq, lista);
        arbolALista(arbol->der, lista);
    }

    return lista;
}

void mostrarLista(nodo* lista)
{
    if(lista != NULL)
    {
        printf("LEGAJO: %i, NOMBRE: %s, EDAD: %i \n", lista->dato.legajo, lista->dato.nombre, lista->dato.edad);
        mostrarLista(lista->sig);
    }
}

///PUNTO 4: Hacer una función que busque un nodo por legajo y lo retorne.
nodoArbol* buscarLegajo(nodoArbol* arbol, int legajoBuscado)
{
    nodoArbol* respuesta = NULL;

    if (arbol != NULL)
    {
        if (legajoBuscado == arbol->dato.legajo)
        {
            respuesta = arbol;
        }
        else if (legajoBuscado > arbol->dato.legajo)
        {
            respuesta = buscarLegajo(arbol->der, legajoBuscado);
        }
        else
        {
            respuesta = buscarLegajo(arbol->izq, legajoBuscado);
        }
    }

    return respuesta;
}

void legajoEncontrado(nodoArbol* nodoBuscado)
{
    if(nodoBuscado != NULL)
    {
        printf("\nNodo encontado, Legajo: %i, Nombre: %s, Edad: %i\n", nodoBuscado->dato.legajo, nodoBuscado->dato.nombre, nodoBuscado->dato.edad);
    }
    else
    {
        printf("\nNodo NO encontrado. \n");
    }
}

///PUNTO 5: Hacer una función que busque un nodo por nombre. Cuidado, el árbol está ordenado por legajo.
nodoArbol* buscarNombre(nodoArbol* arbol, char nombreBuscado[])
{
    if(arbol != NULL)
    {
        if(strcmpi(nombreBuscado, arbol->dato.nombre) == 0)
        {
            return arbol;
        }
        else
        {
            nodoArbol* encontradoIzq = buscarNombre(arbol->izq, nombreBuscado);
            if(encontradoIzq != NULL)
            {
                return encontradoIzq;
            }

            nodoArbol* encontradoDer = buscarNombre(arbol->der, nombreBuscado);
            if(encontradoDer != NULL)
            {
                return encontradoDer;
            }
        }
    }

    return NULL;
}

void nombreEncontrado(nodoArbol* nodoBuscadoNombre)
{
    if(nodoBuscadoNombre != NULL)
    {
        printf("\nNodo encontado, Legajo: %i, Nombre: %s, Edad: %i\n", nodoBuscadoNombre->dato.legajo, nodoBuscadoNombre->dato.nombre, nodoBuscadoNombre->dato.edad);
    }
    else
    {
        printf("\nNodo NO encontrado. \n");
    }
}

///PUNTO 6: Hacer una función que calcule la altura que tiene el árbol.
int calcularAltura(nodoArbol* arbol)
{
    if(arbol != NULL)
    {
        int alturaIzquierda = calcularAltura(arbol->izq);
        int alturaDerecha = calcularAltura(arbol->der);

        if(alturaIzquierda > alturaDerecha)
        {
            return alturaIzquierda + 1;
        }
        else
        {
            return alturaDerecha + 1;
        }
    }
}

///PUNTO 7: Hacer una función que calcule la cantidad de nodos del árbol.
int contarNodos(nodoArbol* arbol)
{
    if(arbol != NULL)
    {
        int nodosIzquierda = contarNodos(arbol->izq);
        int nodosDerecha = contarNodos(arbol->der);

        return nodosIzquierda + nodosDerecha + 1;
    }
}

///PUNTO 8: Hacer una función que calcule la cantidad de hojas del árbol.
int contarHojas(nodoArbol* arbol)
{
    if (arbol != NULL)
    {

        if (arbol->izq == NULL && arbol->der == NULL)
        {
            return 1;
        }
        else
        {
            int hojasIzquierda = contarHojas(arbol->izq);
            int hojasDerecha = contarHojas(arbol->der);

            return hojasDerecha + hojasIzquierda;
        }

    }
}

///PUNTO 9: Hacer una función que borre un nodo de un árbol.
nodoArbol* borrarNodo(nodoArbol* arbol, int legajo)
{
    if(arbol != NULL)
    {
        if (legajo < arbol->dato.legajo)
        {
            arbol->izq = borrarNodo(arbol->izq, legajo);
        }
        else if (legajo > arbol->dato.legajo)
        {
            arbol->der = borrarNodo(arbol->der, legajo);
        }
        else
        {
            if (arbol->izq == NULL)
            {
                nodoArbol* temp = arbol->der;
                free(arbol);
                arbol = temp;
            }
            else if (arbol->der == NULL)
            {
                nodoArbol* temp = arbol->izq;
                free(arbol);
                arbol = temp;
            }
            else
            {
                nodoArbol* sucesor = encotrarSucesorInorden(arbol->der);
                arbol->dato = sucesor->dato;
                arbol->der = borrarNodo(arbol->der, sucesor->dato.legajo);
            }
        }
    }

    return arbol;
}

nodoArbol* encotrarSucesorInorden(nodoArbol* arbol)
{
    while(arbol->izq != NULL)
    {
        arbol = arbol->izq;
    }
    return arbol;
}
