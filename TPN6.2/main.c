#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char animal[30];
    int cant;
    int habitat;
    int idEspecie;
    char especie[20];
} registroArchivo;

typedef struct
{
    char nombreAnimal [30];
    int cantidad;
    int habitat;
// 1 - selva, 2- savana, 3-bosque, 4-mar
} animal;

typedef struct
{
    animal dato;
    struct nodoArbol * izq;
    struct nodoArbol * der;
} nodoArbol;

typedef struct
{
    int idEspecie;
    char especie [20];
    // "Mamiferos", "Aves"
    // "Reptiles", "Peces",”Anfibios”
    nodoArbol * arbolDeAnimales;
} celdaEspecie;



int main()
{
    celdaEspecie arreglo[5];
    strcpy(arreglo[0].especie, "Mamiferos");
    strcpy(arreglo[1].especie, "Aves");
    strcpy(arreglo[2].especie, "Reptiles");
    strcpy(arreglo[3].especie, "Peces");
    strcpy(arreglo[4].especie, "Anfibios");

    arreglo[0].idEspecie = 1;
    arreglo[1].idEspecie = 2;
    arreglo[2].idEspecie = 3;
    arreglo[3].idEspecie = 4;
    arreglo[4].idEspecie = 5;

    arreglo[0].arbolDeAnimales = NULL;
    arreglo[1].arbolDeAnimales = NULL;
    arreglo[2].arbolDeAnimales = NULL;
    arreglo[3].arbolDeAnimales = NULL;
    arreglo[4].arbolDeAnimales = NULL;

    leerArchivo(arreglo, 5);

    printf("\nArreglo[3] PECES\n");
    inorden(arreglo[3].arbolDeAnimales);

    printf("\n***Segunda Parte: \n");
    crearArchivoNuevo(arreglo[3].arbolDeAnimales, "Archivo3.dat",4, "Peces");
    printf("\nLee la segunda parte.\n");
    leerArchivo2("Archivo3.dat");




    return 0;
}


animal crearAnimal(registroArchivo dato)
{
    animal aux;

    aux.cantidad = dato.cant;
    aux.habitat = dato.habitat;
    strcpy(aux.nombreAnimal, dato.animal);

    return aux;
}

nodoArbol* crearNodoArbol(animal dato)
{
    nodoArbol* aux = (nodoArbol*)malloc(sizeof(nodoArbol));
    aux->dato = dato;
    aux->der = NULL;
    aux->izq = NULL;

    return aux;
}

nodoArbol* insertar(nodoArbol* arbol, nodoArbol* dato)
{
    if(arbol == NULL)
    {
        arbol = dato;
    }
    else
    {
        if(dato->dato.cantidad > arbol->dato.cantidad)
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

void inorden(nodoArbol* arbol)
{
    if(arbol != NULL)
    {
        printf("Nombre: %s, Cantidad: %i\n", arbol->dato.nombreAnimal, arbol->dato.cantidad);
        inorden(arbol->izq);
        inorden(arbol->der);
    }
}

void insertarEnArregloArboles(celdaEspecie arreglo[], registroArchivo dato)
{
    int opcion = dato.idEspecie;
    animal aux = crearAnimal(dato);

    nodoArbol* aux2 = crearNodoArbol(aux);

    switch(opcion)
    {
    case 1:
        arreglo[0].arbolDeAnimales = insertar(arreglo[0].arbolDeAnimales, aux2);
        break;
    case 2:
        arreglo[1].arbolDeAnimales = insertar(arreglo[1].arbolDeAnimales, aux2);
        break;
    case 3:
        arreglo[2].arbolDeAnimales = insertar(arreglo[2].arbolDeAnimales, aux2);
        break;
    case 4:
        arreglo[3].arbolDeAnimales = insertar(arreglo[3].arbolDeAnimales, aux2);
        break;
    case 5:
        arreglo[4].arbolDeAnimales = insertar(arreglo[4].arbolDeAnimales, aux2);
        break;
    default:
        break;
    }
}

void leerArchivo(celdaEspecie arreglo[], int validos)
{
    FILE* ptr = fopen("animales.dat", "rb");

    registroArchivo aux;
    int opcion;

    if(ptr != NULL)
    {
        while(fread(&aux, sizeof(registroArchivo),1,ptr) > 0)
        {
            printf("Nombre: %s, idEspecie: %i, Especie: %s, cantidad: %i\n", aux.animal, aux.idEspecie, aux.especie, aux.cant);
            insertarEnArregloArboles(arreglo, aux);
        }
    }
    fclose(ptr);
}

void preorderArchivo(FILE* ptr, nodoArbol* arbol, int idEspecie, char especie[])
{
    if(arbol != NULL)
    {
        registroArchivo aux;

        strcpy(aux.animal, arbol->dato.nombreAnimal);
        aux.cant = arbol->dato.cantidad;
        aux.habitat = arbol->dato.habitat;
        aux.idEspecie = idEspecie;
        strcpy(aux.especie, especie);

        fwrite(&aux, sizeof(registroArchivo),1, ptr);
        preorderArchivo(ptr, arbol->izq, idEspecie, especie);
        preorderArchivo(ptr, arbol->der, idEspecie, especie);
    }
}

void crearArchivoNuevo(nodoArbol* arbol, char nombreArchivo[], int idEspecie, char especie[])
{
    FILE* ptr = fopen(nombreArchivo, "wb");

    if(ptr != NULL)
    {
        preorderArchivo(ptr, arbol, idEspecie, especie);
        fclose(ptr);
    }
}

void leerArchivo2(char nombreArchivo[])
{
    FILE* ptr = fopen(nombreArchivo, "rb");
    registroArchivo aux;

    if(ptr != NULL)
    {
        while(fread(&aux, sizeof(registroArchivo),1, ptr) > 0)
        {
            printf("\nNombre: %s, idEspecie: %i, Especie: %s, Cantidad: %i\n", aux.animal, aux.idEspecie, aux.especie, aux.cant);
        }
    }
    fclose(ptr);
}

