#include <stdio.h>
#include <stdlib.h>
#include "FuncionesYPunteros.h"

///Ejercicio 1: Se tiene un arreglo de números enteros positivos. Se desea obtener el promedio de sus valores. Para ello se debe:
// a. Hacer una función que inicialice las celdas del arreglo en –1.
void cargarArregloNegativo(int arreglo[], int dimension)
{

    for(int i = 0; i < dimension; i++)
    {
        arreglo[i] = (-1);
    }
}

// b. Hacer una función que permita al usuario ingresar los valores. No se conoce la cantidad de antemano.
// d. Hacer una función que cuente la cantidad de valores ingresados.
int cargarArreglo(int arreglo[], int validos)
{
    char continuar;
    int aux;
    int i = 0;

    do
    {
        printf("Ingrese el numero a cargar en el arreglo: \n");
        fflush(stdin);
        scanf("%i", &arreglo[i]);

        i++;

        printf("Quiere cargar otro numero? s/n \n");
        fflush(stdin);
        scanf("%c", &continuar);
    }
    while(continuar == 's' || continuar == 'S');

    return i;
}

// c. Hacer una función que sume el contenido del arreglo y lo retorne.
int sumarArreglo(int arreglo[], int validos)
{
    int suma = 0;

    for(int i = 0; i < validos; i++)
    {
        suma += arreglo[i];
    }

    return suma;
}

// e. Hacer una función que reciba como parámetro el arreglo ya cargado, calcule y retorne el valor promedio usando las funciones anteriores (c y d).
float promedioArreglo(int arreglo[], int validos, int sumaTotal)
{
    float promedio = (float)sumaTotal / validos;

    return promedio;
}

///Ejercicio 2: Invertir el contenido de un arreglo de caracteres. Para ello se debe modularizar de la siguiente forma:
// a. Hacer una función para la carga del arreglo.
int cargarArregloChar(char arreglo[], int validos2)
{
    char continuar;
    int i = 0;

    do
    {
        printf("Ingrese el caracter a cargar en el arreglo: \n");
        fflush(stdin);
        scanf("%c", &arreglo[i]);

        i++;

        printf("Quiere cargar otro caracter? s/n \n");
        fflush(stdin);
        scanf("%c", &continuar);
    }
    while(continuar == 's' || continuar == 'S');

    return i;
}

// b. Hacer una función para invertir el arreglo.
void arregloInvert(int arreglo[], int validos)
{
    int aux;
    int i = 0;
    int u = validos - 1;

    while (i < u)
    {
        aux = arreglo[u];
        arreglo[u] = arreglo[i];
        arreglo[i] = aux;
        u--;
        i++;
    }

    printf("Arreglo Invertido: \n");
    mostrarArreglo(arreglo, validos);
}

// c. Hacer una función para mostrar el contenido del arreglo.
void mostrarArreglo(int arreglo[], int validos)
{
    for(int i = 0; i < validos; i++)
    {
        printf("%i", arreglo[i]);
    }
}

///Ejercicio 3: Hacer una función que reciba como parámetro un arreglo de números enteros de un dígito y retorne el valor decimal de dicho número.
///Por ejemplo, un arreglo que tiene cargados los valores 3, 2, 8 y 9, la fn retorna el valor 3289.
int valorDecimal(int arregloDecimal[], int validos)
{
    int num = validos - 1;
    int suma = 0;
    int aux = 0;

    for(int i = 0; i < validos; i ++)
    {
        aux = arregloDecimal[i];
        suma = (aux * (pow(10,num)) + suma);
        num--;
    }

    return suma;
}

///Ejercicio 4: Hacer una función que retorne la posición del valor máximo de un arreglo de números enteros.
int posicionMaximo(int arregloMaximo[], int validos)
{
    int maximo = 0;
    int pos = 0;

    for(int i = 0; i < validos; i++)
    {
        if(maximo <= arregloMaximo[i])
        {
            maximo = arregloMaximo[i];
            pos = i;
        }
    }
    return pos;
}

///Ejercicio 5:
