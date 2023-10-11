#include "FuncionesYPunteros.h"

int main()
{
    //Ejercicio 1
    ///a)
    printf("Ejercicio 1. A) \n");
    int dimension = 50;
    int arreglo[dimension];
    cargarArregloNegativo(arreglo, dimension);

    ///b) y d)
    printf("\nEjercicio 1. B) y D) \n");
    int validos = cargarArreglo(arreglo, validos);
    mostrarArreglo(arreglo, validos);
    printf("\nHay %i valores cargados en el arreglo. \n", validos);

    ///c)
    printf("\nEjercicio 1. C) \n");
    int sumaTotal = sumarArreglo(arreglo, validos);
    printf("La suma del arreglo es de: %i \n", sumaTotal);

    ///e)
    printf("\nEjercicio 1. E) \n");
    float promedio = promedioArreglo(arreglo, validos, sumaTotal);
    printf("El promedio del arreglo es de: %.2f \n", promedio);


    //Ejercicio 2
    ///a)
    printf("\nEjercicio 2. A) \n");
    int validos2 = 0;
    char arregloChar[validos2];
    validos2 = cargarArregloChar(arregloChar, validos2);
    printf("Hay ingresados %i caracteres en el arreglo. \n", validos2);

    ///b)
    printf("\nEjercicio 2. B) \n");
    int validos2b = 0;
    int arregloAux[validos2b];
    validos2b = cargarArreglo(arregloAux, validos2b);
    printf("ARREGLO CARGADO: \n");
    mostrarArreglo(arregloAux, validos2b);
    printf("\nARREGLO INVERTIDO: \n");
    arregloInvert(arregloAux, validos2b);

    ///c
    printf("\nEjercicio 2. C) \n");
    //mostrarArreglo(arregloAux, validos2b);


    //Ejercicio 3
    ///a)
    printf("\nEjercicio 3. A) \n");
    int decimal = valorDecimal(arregloAux, validos2b);
    printf("ARREGLO A DECIMAL: \n");
    mostrarArreglo(arregloAux, validos2b);

    //Ejercicio 4
    ///a)
    printf("\nEjercicio 4. A) \n");
    int posicionDelMayor = posicionMaximo(arregloAux, validos2b);
    printf("La posicion del valor maximo es: %i \n", posicionDelMayor);


    return 0;
}
