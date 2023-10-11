#include "TPAdicionalPro.h"

int main()
{

///PUNTEROS SIMPLES:

//    //Ejercicio 1.)
//    printf("Ejercicio 1: \n");
//    int a = 5;
//    int b = 10;
//    intercambiar(&a, &b);
//    printf("EL valor actual de A es: %i, y el de B es: %i \n", a, b);
//
//    //Ejercicio 2.)
//    printf("\nEjercicio 2: \n");
//    int arregloNum[] = {1,2,3,4,5};
//    int dimension = sizeof(arregloNum) / sizeof(arregloNum[0]);
//    int suma = sumarElementos(arregloNum, dimension);
//    printf("La suma de los elementos es: %i", suma);
//
//    //Ejercicio 3.)
//    printf("\nEjercicio 3: \n");
//    char arregloString[] = "hola mundo";
//    ConvertirMayuscula(arregloString);
//    printf("Cadena en mayuscula: %s \n", arregloString);
//
//    //Ejercicio 4.)
//    printf("\nEjercicio 4:\n");
//    int numeros[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//    int dim = sizeof(numeros) / sizeof(numeros[0]);
//    eliminarPares(numeros, &dim);
//    mostrarArreglo(numeros, dim);
//
//    //Ejercicio 5.)
//    printf("\nEjercicio 5: \n");
//    int num1[] = {1, 2, 3, 4, 5};
//    int dimen = sizeof(num1) / sizeof(num1[0]);
//    invertirArreglo(num1, dimen);
//    mostrarArreglo(num1, dimen);
//
//    //Ejercicio 6.)
//    printf("\nEjercicio 6: \n");
//    char arrString[] = "hola mundo";
//    int vocalTotal = contarVocales(arregloString);
//    printf("Tiene %d \n",vocalTotal);
//
//    //Ejercicio 7.)
//    printf("\nEjercicio 7: \n");
//    char origen[] = "Hola, esto es una cadena";
//    char destino[100];
//    copiarCadena(origen, destino);
//    printf("Destino: %s \n", destino);
//
//    //Ejercicio 8.)
//    printf("\nEjercicio 8: \n");
//    int arrNumeros[] = {34, 12, 56, 89, 7, 23};
//    int dimension8 = sizeof(arrNumeros) / sizeof(arrNumeros[0]);
//    int min = 0;
//    int max = 0;
//    encontrarMinimoMaximo(arrNumeros, dimension8, &min, &max);
//    printf("Minimo: %i, Maximo: %i \n", min, max);
//
//    //Ejercicio 9.)
//    printf("\nEjercicio 9:\n");
//
//    // Definir las cadenas de origen y destino
//    char *arreCadenaOrigen = "Hola, soy ";
//    char *arreCadenaDestino = "una cadena.";
//    char cadenaResultado[100];// Declarar un arreglo para el resultado de la concatenaci n
//    sprintf(cadenaResultado, "%s%s", arreCadenaOrigen, arreCadenaDestino);// Concatenar las cadenas de origen y destino usando sprintf
//    printf("Resultado: %s\n", cadenaResultado);
//
//    //Ejercicio 10.)
//    printf("\nEjercicio 10: \n");
//    char cadena[] = "Hola, esto es una cadena de prueba.";
//    char caracter = 'c';
//    buscarCaracter(cadena, caracter);
/*________________________________________________________________________________________________________*/


///FUNCIONES QUE DEVUELVEN UN PUNTERO:

//    //Ejercicio 1.)
//    printf("Ejercicio 1: \n");
//    int dimension = 5;
//    int *puntero = crearArregloDinamico(dimension);
//
//    if(puntero == NULL)
//    {
//        printf("No se pudo asignar memoria. \n");
//    }
//
//    cargarArregloDinamico(puntero, dimension);
//    mostrarArregloDinamico(puntero, dimension);
//
//    free(puntero);
//
//    //Ejericicio 2.)
//    printf("\nEjercicio 2: \n");
//    char cadenaOriginal[] = "Hola, esto es una cadena de prueba.";
//    char *copia = duplicarCadena(cadenaOriginal);
//    printf("COPIA: %s \n", copia);
//    free(copia);
//
//    //Ejercicio 3.)
//    printf("\nEjercicio 3: \n");
//    int original[] = {1, 2, 3, 4, 5};
//    int dimension2 = sizeof(original) / sizeof(original[0]);
//
//    int *clon = clonarArregloDinamico(original, dimension2);
//    mostrarArregloDinamico(clon, dimension2);
//
//    free(clon);
//
//    //Ejercicio 4.)
//    printf("\nEjercicio 4: \n");
//    char texto[] = "Esta es una cadena dinamica.";
//    char *cadena = crearCadenaDinamica(texto);
//    printf("Cadena: %s \n", cadena);
//    free(cadena);
/*________________________________________________________________________________________________________*/

///PUNTEROS DOBLES:

    //Ejercicio 1.)
    printf("Ejercicio 1: \n");
    int num1 = 5;
    int num2 = 10;

    int *ptr1 = &num1;
    int *ptr2 = &num2;

    printf("Antes del intecambio: a = %i, b = %i \n", num1, num2);

    interValores(&ptr1, &ptr2);

    printf("Despues del intercambio: a = %i, b = %i \n", *ptr1, *ptr2);

    //Ejercicio 2.)
    printf("\nEjercicio 2: \n");
    int numeros[]= {1, 2, 3, 4, 5};
    int *ptr = numeros; // Puntero al primer elemento del arreglo.

    int dimension = sizeof(numeros) / sizeof(numeros[0]);

    mostrarArregloPunteroDoble(&ptr, dimension);

    //Ejercicio 3.)
    printf("\nEjercicio 3: \n");
    duplicarArregloPunteroDoble(&ptr, dimension);
    mostrarArregloPunteroDoble(&ptr, dimension);

    return 0;
}
