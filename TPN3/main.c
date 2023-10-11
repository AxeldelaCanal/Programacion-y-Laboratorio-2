#include <stdio.h>
#include <stdlib.h>

///Prototipados:
int factorial(int numero); //Ejercicio  1.
int potencia(int base, int exponente); //Ejercicio 2.
void mostrarArregloRecursivo(int arreglo[], int tamano, int indice); //Ejercicio 3
void mostrarArregloInvertidoRecursivo(int arreglo[], int tamano, int indice); //Ejercicio 4
void arregloCapicua(int arreglo[], int inicio, int fin); //Ejercicio 5
int sumarArregloRecursivo(int arreglo[], int dimension, int i); //Ejercicio 6
int buscarMenor(int arreglo[], int validos, int pos, int menor); //Ejercicio 7
float promedioArregloRecursivo(int arreglo[], int dimension, int i);

int main()
{
//    printf("\nEjercicio 1.) \n");
//    int numero = 5;
//    int resultado = factorial(numero);
//    printf("El factorial de %i es: %i ",numero, resultado);
//
//    printf("\nEjercicio 2.) \n");
//    int base = 2;
//    int exponente = 3;
//    int resultado1 = potencia(base, exponente);
//    printf("%i ^ %i = %i", base, exponente, resultado1);

    printf("\nEjercicio ARREGLO.) \n");
    int arreglo[] = {1, 2, 3, 4, 5};
    int tamano = sizeof(arreglo) / sizeof(arreglo[0]);
    int indice = 0;
    printf("Arreglo Recursivo: \n");
    mostrarArregloRecursivo(arreglo, tamano, indice);

    printf("\nEjercicio INVERTIDO.) \n"); //SALON ARREGLO INVERTIDO
    printf("Arreglo Recursivo Invertido: \n");
    mostrarArregloInvertidoRecursivo(arreglo, tamano, indice);

//    printf("\nEjercicio 5.) \n");
//    int arregloNum[] = {1, 2, 3, 2, 1};
//    int longitud = sizeof(arregloNum) / sizeof(arregloNum[0]);
//    arregloCapicua(arregloNum, 0, longitud - 1);

    printf("\nEjercicio MENOR) \n"); //SALON MENOR
    int arregloEj7[] = {2, 1, 7, 4, 6};
    int validos = sizeof(arregloEj7) / sizeof(arregloEj7[0]);
    int posicion = 0;
    int menor = arregloEj7[0];
    int valorMenor = buscarMenor(arregloEj7, validos, posicion, menor);
    printf("El valor menor es: %i \n", valorMenor);

    printf("\nEjercicio SUMA) \n"); //SALON SUMA
    int arr[] = {1, 2, 3, 4, 5};
    int dimension = sizeof(arr) / sizeof(arr[0]);
    int i = 0;
    int sumaTotal = sumarArregloRecursivo(arr, dimension, i);
    printf("El resultado es: %i \n", sumaTotal);


    printf("\nEjercicio PROMEDIO.) \n"); //SALON PROMEDIO
    float promedio = promedioArregloRecursivo(arr, dimension, i);
    printf("El promedio es: %.2f \n", promedio);

    return 0;
}

///Ejercicio 1.) Calcular el factorial de un n mero en forma recursiva.
int factorial(int numero)
{
    if(numero == 1)
    {
        return 1;
    }
    else
    {
        return numero * factorial(numero - 1);
    }
}

///Ejercicio 2.) Calcular la potencia de un n mero en forma recursiva.
int potencia(int base, int exponente)
{
    if (exponente <= 0)
    {
        return 1;
    }
    else
    {
        return base * potencia(base, exponente - 1);
    }
}

///Ejercicio 3.) Recorrer un arreglo y mostrar sus elementos en forma recursiva.
void mostrarArregloRecursivo(int arreglo[], int tamano, int indice)
{
    if(indice < tamano)
    {
        printf("%i ", arreglo[indice]);
        mostrarArregloRecursivo(arreglo, tamano, indice + 1);
    }
}

///Ejercicio 4.) Recorrer un arreglo comenzando desde la posici n 0 y mostrar sus elementos en forma invertida (recursivo). ---------------------------SALON
void mostrarArregloInvertidoRecursivo(int arreglo[], int tamano, int indice)
{
    if(indice < tamano)
    {
        mostrarArregloInvertidoRecursivo(arreglo, tamano, indice + 1);
        printf("%i ", arreglo[indice]);
    }
}/*la funci n mostrarArregloInvertidoRecursivo se llama a s  misma primero para recorrer el arreglo desde la posici n 0 hasta la  ltima.
Luego, muestra el elemento en el  ndice actual despu s de haber recorrido todos los elementos posteriores en la llamada recursiva.
Esto logra que los elementos se muestren en orden invertido.*/

///Ejercicio 5.) Determinar en forma recursiva si un arreglo es capic a.
void arregloCapicua(int arreglo[], int inicio, int fin)
{
    if(inicio >= fin)
    {
        printf("El arreglo es capicua.\n");
        return;
    }
    if(arreglo[inicio] != arreglo[fin])
    {
        printf("El arreglo no es capicua. \n");
        return;
    }

    arregloCapicua(arreglo, inicio + 1, fin - 1);
}

///Ejercicio 6.) Sumar en forma recursiva los elementos de un arreglo de enteros y retornar el total de la suma. ---------------------------SALON
int sumarArregloRecursivo(int arreglo[], int dimension, int i)
{
    if(i >= dimension)
    {
        return 0;
    }
    else
    {
        return arreglo[i] + sumarArregloRecursivo(arreglo, dimension, i + 1);
    }
}

///Ejercicio 7.) Buscar el menor elemento de un arreglo en forma recursiva.  ---------------------------SALON
int buscarMenor(int arreglo[], int validos, int pos, int menor)
{
    if(pos == validos)
    {
        return menor;
    }
    else if(menor > arreglo[pos])
    {
        menor = arreglo[pos];
    }

    return buscarMenor(arreglo, validos, pos + 1, menor);
}

///---------------------------SALON
float promedioArregloRecursivo(int arreglo[], int dimension, int i)
{
    if(i >= dimension)
    {
        return 0;
    }
    else
    {
        return (arreglo[i] / (float)dimension) + promedioArregloRecursivo(arreglo, dimension, i + 1);
    }
}
