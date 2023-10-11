#include <stdio.h>
#include <stdlib.h>

///Estructuras Ejercicio 1:)
typedef struct
{
    char nombre[20];
    int edad;
} Persona;

typedef struct
{
    Persona dato;
    struct nodo* siguiente;
} Nodo;
///----------------------------------

///Estructuras Ejercicio 2:)
typedef struct
{
    char marca[20];
    int anio;
} Automovil;

typedef struct
{
    Automovil dato;
    struct nodo* siguiente;
} Nodo1;
///------------------------------------

///Estructuras Ejercicio 4:)
typedef struct
{
    int valor;
    struct nodo* siguiente;
} Nodo2;
///------------------------------------

///Estructuras Ejercicio 6:)
typedef struct{
     Nodo2* head;
} Pila;
///------------------------------------





// Prototipados de las funciones del Ejercicio 1.)
Persona cargarPersona();
void cargarArchivoPersona();
void mostrarArchivo();
void mostrarPersona(Persona nuevaPersona);
Nodo* inicializarLista();
Nodo* crearNodo(Persona nuevaPersona);
Nodo* agregarAlPrincipio(Nodo* head, Nodo* nuevoNodo);
void punto1(Nodo** head);
void mostrarLista(Nodo* head);


// Prototipados de las funciones del Ejercicio 2.)
Automovil cargarAuto();
void cargarArchivoAutomovil();
void mostrarAutomovil(Automovil autoNuevo);
void mostrarArchivoAutomovil();
Nodo1* crearNodo1(Automovil autoNuevo);
void insertarOrdenado(Nodo1** cabeza, Automovil autoNuevo);
void punto2(Nodo1** lista);


// Prototipados de las funciones del Ejercicio 3.)
int punto3(Nodo1* lista, int anioParametro);


// Prototipados de las funciones del Ejercicio 4.)
Nodo2* crearNodoEjercicio4(int valor);
void mostrarNodo(Nodo2* nodoActual);
void mostrarListaNodo2(Nodo2* primerNodo);
Nodo2* buscarUltimo(Nodo2* lista);
Nodo2* agregarAlFinal(Nodo2* lista, Nodo2* nuevoNodo);
Nodo2* punto4(Nodo2* lista2, Nodo2* lista3);

// Prototipados de las funciones del Ejercicio 5.)
void invertirLista(Nodo2** cabeza);

// Prototipados de las funciones del Ejercicio 6.)
void inicPila(Pila *p);
void apilar(Pila *p, int valor);
int desapilar(Pila *p);
int tope(Pila *p);
int pilavacia(Pila *p);
void mostrar(Pila *p);
void leer(Pila *p);

// Prototipados de las funciones del Ejercicio 7.)
Nodo2* pilaAListaPar(Pila p); ///A)
void eliminarMenoresA10(Nodo2** lista); ///B)


int main()
{
    ///EJERCICIO NUMERO ---------------------------------------------------> 1
//    printf("Ejercicio 1: \n");
//    cargarArchivoPersona();
//    mostrarArchivo();
//    Nodo* head = inicializarLista();
//    punto1(&head);
//    printf("\nLISTA -> ");
//    mostrarLista(head);

    ///EJERCICIO NUMERO ---------------------------------------------------> 2
//    printf("\nEjercicio 2: \n");
//    //cargarArchivoAutomovil();
//    mostrarArchivoAutomovil();
//    Nodo1* lista = inicializarLista();
//    punto2(&lista);
//    printf("\nLISTA -> ");
//    mostrarLista(lista);

    ///EJERCICIO NUMERO ---------------------------------------------------> 3
//    printf("\nEjercicio 3: \n");
//    int respuesta = punto3(lista, 2000);
//    printf("1 = Encontrado || 0 = NO Encotrado \n");
//    printf("Respuesta: %i \n", respuesta);

    ///EJERCICIO NUMERO ---------------------------------------------------> 4
    printf("\nEjercicio 4: \n");
    Nodo2* lista2 = inicializarLista(); ///Creo  la Primer lista.

    int dato1 = 1;
    Nodo2* nodo2a = crearNodoEjercicio4(dato1);
    lista2 = nodo2a;


    int dato2 = 3;
    Nodo2* nodo2b = crearNodoEjercicio4(dato2);
    nodo2a->siguiente = nodo2b;

    int dato3 = 5;
    Nodo2* nodo2c = crearNodoEjercicio4(dato3);
    nodo2b->siguiente = nodo2c;

    printf("\nPRIMER LISTA: \n");
    printf("LISTA -> ");
    mostrarListaNodo2(lista2);

    Nodo2* lista3 = inicializarLista(); ///Creo la Segunda lista.

    int dato4 = 2;
    Nodo2* nodo3a = crearNodoEjercicio4(dato4);
    lista3 = nodo3a;

    int dato5 = 4;
    Nodo2* nodo3b = crearNodoEjercicio4(dato5);
    nodo3a->siguiente = nodo3b;

    int dato6 = 6;
    Nodo2* nodo3c = crearNodoEjercicio4(dato6);
    nodo3b->siguiente = nodo3c;

    printf("\nSEGUNDA LISTA: \n");
    printf("LISTA -> ");
    mostrarListaNodo2(lista3);

    printf("\nLISTA ORDENA: \n");
    Nodo2* listaResultado;
    listaResultado = inicializarLista();
    listaResultado = punto4(lista2, lista3);
    printf("LISTA -> ");
    mostrarListaNodo2(listaResultado);

    ///EJERCICIO NUMERO ---------------------------------------------------> 5
    printf("\nEjercicio 5: \n");
    invertirLista(&lista2);
    printf("LISTA -> ");
    mostrarListaNodo2(lista2);

    ///EJERCICIO NUMERO ---------------------------------------------------> 6
    printf("\nEjercicio 6: \n");
    Pila pilita;
    inicPila(&pilita);

    apilar(&pilita, 1);
    apilar(&pilita, 2);
    apilar(&pilita, 3);
    apilar(&pilita, 4);
    apilar(&pilita, 5);
    apilar(&pilita, 6);
    apilar(&pilita, 7);
    apilar(&pilita, 8);
    apilar(&pilita, 9);
    apilar(&pilita, 10);
    apilar(&pilita, 11);
    apilar(&pilita, 12);
    apilar(&pilita, 13);
    apilar(&pilita, 14);

    printf("PILA:");
    mostrar(&pilita);
    //printf("TOPE: %i", tope(&pilita));

    //desapilar(&pilita);
    //mostrar(&pilita);

    //leer(&pilita);
    //mostrar(&pilita);

    ///EJERCICIO NUMERO ---------------------------------------------------> 7
    printf("\nEjercicio 7 A: \n");

    Nodo2* listaPares = pilaAListaPar(pilita);
    printf("PILA REALIZADA EN EL EJERCICIO 6 y UTILIZADA EN EL 7: ");
    mostrar(&pilita);
    printf("LISTA EJERCICIO 7 A: \n");
    mostrarListaNodo2(listaPares);

    printf("\nEjercicio 7 B: \n");
    eliminarMenoresA10(&listaPares);
    mostrarListaNodo2(listaPares);

    return 0;
}


///Ejercicio 1: Hacer un programa que lea de un archivo datos y los inserte en una lista.
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

///Ejercicio 2: Hacer un programa que lea de un archivo datos y los inserte en una lista en forma ordenada.
Automovil cargarAuto()
{
    Automovil autoNuevo;

    printf("Ingrese la MARCA del automovil: \n");
    fflush(stdin);
    scanf("%s", &autoNuevo.marca);

    printf("Ingrese el ANIO del automovil: \n");
    fflush(stdin);
    scanf("%i", &autoNuevo.anio);

    return autoNuevo;
}

void cargarArchivoAutomovil()
{
    char continuar;

    Automovil autoNuevo;

    FILE* buffer = fopen("archivoAutomovil.txt", "a");

    if(buffer == NULL)
    {
        printf("No se pudo abrir el archivo. \n");
        return;
    }

    do
    {
        autoNuevo = cargarAuto();
        fwrite(&autoNuevo, sizeof(Automovil),1,buffer);

        printf("Quiere agregar otro automovil? s/n \n");
        fflush(stdin);
        scanf("%c", &continuar);
    }
    while(continuar == 's' || continuar == 'S');

    fclose(buffer);
}

void mostrarAutomovil(Automovil autoNuevo)
{
    printf("\n---------------\n");
    printf("MARCA: %s \n",autoNuevo.marca);
    printf("ANIO: %i \n",autoNuevo.anio);
    printf("-----------------\n");
}

void mostrarArchivoAutomovil()
{
    Automovil autoNuevo;

    FILE* buffer = fopen("archivoAutomovil.txt", "r");

    if(buffer == NULL)
    {
        printf("No se puede abrir el archivo. \n");
        return;
    }

    while(fread(&autoNuevo, sizeof(Automovil),1,buffer) > 0)
    {
        mostrarAutomovil(autoNuevo);
    }

    fclose(buffer);
}

Nodo1* crearNodo1(Automovil autoNuevo)
{
    Nodo1* aux = (Nodo1*)malloc(sizeof(Nodo1));
    if(aux != NULL)
    {
        aux->dato = autoNuevo;
        aux->siguiente = NULL;
    }

    return aux;
}

void insertarOrdenado(Nodo1** lista, Automovil autoNuevo)
{
    Nodo1* nuevoNodo = crearNodo1(autoNuevo);

    if (nuevoNodo == NULL)
    {
        printf("Error al crear el nuevo nodo.\n");
        return;
    }

    Nodo1* anterior = NULL;
    Nodo1* actual = *lista;

    while (actual != NULL && autoNuevo.anio >= actual->dato.anio)
    {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (anterior == NULL)
    {
        // El nuevo nodo debe ser el nuevo lista de la lista
        nuevoNodo->siguiente = *lista;
        *lista = nuevoNodo;
    }
    else
    {
        // Insertar el nuevo nodo despu s de 'anterior'
        nuevoNodo->siguiente = actual;
        anterior->siguiente = nuevoNodo;
    }
}

void punto2(Nodo1** lista)
{
    Automovil nuevoAuto;

    FILE* buffer = fopen("archivoAutomovil.txt", "r");

    if(buffer != NULL)
    {
        while(fread(&nuevoAuto, sizeof(Automovil),1,buffer) > 0)
        {
            insertarOrdenado(lista, nuevoAuto);
        }
        fclose(buffer);
    }
}

///Ejercicio 3: Hacer una funci n que retorne un 1 (uno) o 0 (cero) si existe un determinado elemento en una lista dada.
///(considerar caso ordenada y caso desordenada)
int punto3(Nodo1* lista, int anioParametro)
{
    int flag = 0;

    while(lista->siguiente != NULL && flag != 1)
    {
        if(lista->dato.anio == anioParametro)
        {
            flag = 1;
        }
        lista = lista->siguiente;
    }

    return flag;
}

///Ejercicio 4: Hacer una funci n que intercale en orden los elementos de dos listas ordenadas generando una nueva lista.
///Se deben redireccionar los punteros, no se deben crear nuevos nodos.

Nodo2* crearNodoEjercicio4(int valor)
{
    Nodo2* aux = (Nodo2*)malloc(sizeof(Nodo2));

    aux->valor = valor;
    aux->siguiente = NULL;

    return aux;
}

void mostrarNodo(Nodo2* nodoActual)
{
    printf("[%i] -> ", nodoActual->valor);
}

void mostrarListaNodo2(Nodo2* primerNodo)
{
    Nodo2* actual = primerNodo;

    while(actual != NULL)
    {
        mostrarNodo(actual);
        actual = actual->siguiente;
    }
    printf("NULL\n");
}

Nodo2* buscarUltimo(Nodo2* lista)
{
    Nodo2* seg = lista;

    if(seg != NULL)
    {
        while(seg->siguiente != NULL)
        {
            seg = seg->siguiente;
        }

    }
    return seg;
}

Nodo2* agregarAlFinal(Nodo2* lista, Nodo2* nuevoNodo)
{
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        Nodo2* ultimo = buscarUltimo(lista);
        ultimo->siguiente = nuevoNodo;
    }
    return lista;
}

Nodo2* punto4(Nodo2* lista1, Nodo2* lista2)
{
    if (lista1 == NULL)
        return lista2;

    if (lista2 == NULL)
        return lista1;

    // Compara los valores de los nodos actuales en lista1 y lista2
    if (lista1->valor <= lista2->valor)
    {
        // Si el valor en lista1 es menor o igual, realiza la fusión en lista1
        // Llama recursivamente a punto4 con el siguiente nodo en lista1 y lista2 sin cambios
        lista1->siguiente = punto4(lista1->siguiente, lista2);

        // Devuelve lista1, ya que es el nodo actual en lista1
        return lista1;
    }
    else
    {
        // Si el valor en lista2 es menor, realiza la fusión en lista2
        // Llama recursivamente a punto4 con lista1 sin cambios y el siguiente nodo en lista2
        lista2->siguiente = punto4(lista1, lista2->siguiente);

        // Devuelve lista2, ya que es el nodo actual en lista2
        return lista2;
    }
}

///Ejercicio 5: Invertir los elementos de una lista redireccionando solamente los punteros. (No se deben crear nuevos nodos)
void invertirLista(Nodo2** cabeza)
{
    Nodo2* prev = NULL;
    Nodo2* current = *cabeza;
    Nodo2* siguiente = NULL;

    while (current != NULL)
    {
        siguiente = current->siguiente;  // Guarda el siguiente nodo
        current->siguiente = prev;       // Cambia el puntero siguiente al nodo previo
        prev = current;                  // Avanza el puntero previo
        current = siguiente;             // Avanza el puntero actual
    }

    *cabeza = prev;  // Actualiza el puntero de la cabeza
}

///Ejercicio 6: Codificar el TDA Pila con las funciones necesarias, implementada con una lista enlazada (Similar al ejercicio hecho con arreglo).

///Pilas
void inicPila(Pila *p)
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

///Ejercicio 7: Utilizando el TDA Pila creado en el punto 6, cargar la pila con números enteros.
//A) Luego, recorrer dicha pila e insertar por orden de llegada (al final) en una lista simplemente enlazada aquellos números que sean pares.
//   Cuidado, la función no debe perder la pila original, trabaje de forma tal que se conserven sus datos.

Nodo2* pilaAListaPar(Pila p)
{
    Nodo2* listaPares = NULL;  // Inicializa una lista enlazada vacía para los números pares.

    while (!pilavacia(&p))
    {
        int elemento = tope(&p);

        if (elemento % 2 == 0)
        {
            // Si el elemento es par, agrega un nodo al final de la lista de números pares.
            listaPares = agregarAlFinal(listaPares, crearNodoEjercicio4(elemento));
        }

        desapilar(&p);
    }

    return listaPares;
}

//B) Eliminar de la lista cargada en el ejercicio anterior, aquellos nodos que contengan valores menores a 10.
void eliminarMenoresA10(Nodo2** lista)
{
    Nodo2* actual = *lista;
    Nodo2* anterior = NULL;

    while(actual != NULL)
    {
        if(actual->valor < 10)
        {
            // El valor es menor a 10, elimina el nodo.
            Nodo2* nodoAEliminar = actual;
            actual = actual->siguiente;

            if(anterior != NULL)
            {
                anterior->siguiente = actual;
            }
            else
            {
                *lista = actual; // Si el nodo a eliminar es el primero de la lista, actualiza la cabeza de la lista.
            }

            free(nodoAEliminar); // Libera la memoria del nodo eliminado.
        }
        else
        {
            anterior = actual;
            actual = actual->siguiente;
        }
    }
}

