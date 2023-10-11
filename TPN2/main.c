#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nombre[30];
    char genero;
    int edad;
} persona;

typedef struct
{
    int valores[100];
    int posTope; //posición de nuevo tope, lugar en donde se almacenará el nuevo valor
} Pila;

typedef struct
{
    int matricula;
    char nombre[30];
} Alumno;

typedef struct
{
    int codigo;
    char nombreMat[20];
} Materia ;

typedef struct
{
    int matricula;
    int codigo;
    int nota;
} Nota;

///PROTOTIPADOS
int cargarPersona(persona arr[], int validos); //Ejercicio A
void mostrarPersona(persona arr[], int validos); ///Aux
void contarPersonaGenero(persona arr[], int validos, char generoParametro); //Ejercicio B
persona* copiarPersonasGenero(persona arr[], int validos, char generoParametro, int* copiados); //Ejercicio C
void ordenarPorEdadDescendente(persona arr[], int validos); //Ejercicio 2
void apilar(Pila* p, int valor); //Ejercicio 3
int desapilar(Pila *p); //Ejercicio 3
int tope(Pila *p); //Ejercicio 3
int pilavacia(Pila *p); //Ejercicio 3
void mostrar(Pila *p); //Ejercicio 3
void leer(Pila *p); //Ejercicio 3
void intercalarPilasOrdenadas(Pila *pila1, Pila *pila2, Pila *pilaResultante); //Ejercicio 4
void insertarArreglo(int arreglo[], int* tamanio, int valor); // Ejercicio 5
void mostrarArreglo(int arreglo[], int validos); ///AUX
void ordenamientoPorInsercion(int arreglo[], int validos); //Ejercicio 6
void eliminarElementoArreglo(int arreglo[], int* validos, int elementoBorrar); //Ejercicio 7
void cargarMaterias(Materia mats[]); //Ejercicio 8.1
void mostrarMaterias(Materia mats[]); ///Aux
void agregarUnAlumno(Alumno alus[], int *numAlumnos); //Ejercicio 8.2
void mostrarAlumno(Alumno alus[], int numAlumnos); ///Aux



void mostrarNotasPorAlumno(char nombre[], Nota notas[], Alumno alus[], Materia mats[], int numNotas, int numAlumnos);

int main()
{
//    //Ejercicio 1. A)
//    printf("Ejercicio 1-A \n");
//    persona personas[30];
//    int validos = 0;
//    validos = cargarPersona(personas, validos);
//    mostrarPersona(personas, validos);
//
//    //Ejercicio 1. B)
//    printf("\nEjercicio 1-B \n");
//    char generoParametro;
//    printf("Ingrese el genero a buscar: \n");
//    fflush(stdin);
//    scanf("%c", &generoParametro);
//
//    contarPersonaGenero(personas, validos, generoParametro);
//
//    //Ejercicio 1. C)
//    printf("\nEjercicio 1-C \n");
//    int copiados;
//    persona* copiaPersona = copiarPersonasGenero(personas, validos, generoParametro, &copiados);
//    printf("PERSONAS COPIADAS: \n");
//    mostrarPersona(copiaPersona, copiados);
//    free(copiaPersona);
//
//    //Ejercicio 2.
//    printf("\nEjercicio 2 \n");
//    ordenarPorEdadDescendente(personas, validos);
//    mostrarPersona(personas, validos);

//    //Ejercicio 3.
//    printf("\nEjercicio 3 \n");
//    printf("Se crearon todas las funciones que necesita una PILA. \n");
//
//    //Ejercicio 4.
//    printf("\nEjercicio 4 \n");
//    Pila a;
//    Pila b;
//    Pila resultado;
//    inicPila(&a);
//    inicPila(&b);
//    inicPila(&resultado);
//    printf("Ingrese el primer valor en Pila A:");
//    leer(&a);
//    printf("Ingrese el segundo valor en Pila A:");
//    leer(&a);
//    printf("Ingrese el tercer valor en Pila A:");
//    leer(&a);
//    printf("Ingrese el primer valor en Pila B:");
//    leer(&b);
//    printf("Ingrese el segundo valor en Pila B:");
//    leer(&b);
//    printf("Ingrese el tercer valor en Pila B:");
//    leer(&b);
//    intercalarPilasOrdenadas(&a, &b, &resultado);
//
//    //Ejercicio 5.
//    printf("\nEjercicio 5 \n");
//    int arreglo[100] = {1, 2, 3, 5, 6};
//    int tamanio = 5;
//    int nuevoValor = 4;
//    insertarArreglo(arreglo, &tamanio, nuevoValor);
//    mostrarArreglo(arreglo, tamanio);
//
//    //Ejercicio 6.
//    printf("\nEjercicio 6 \n");
//    int arreglo2[] = {4, 2, 7, 1, 9 ,3};
//    int validos = sizeof(arreglo2) / sizeof(arreglo2[0]);
//    ordenamientoPorInsercion(arreglo2, validos);
//    mostrarArreglo(arreglo2, validos);

    //Ejercicio 7.
    printf("\nEjercicio 7 \n");
    int arreglo3[] = {1, 2, 3, 4};
    int validos3 = sizeof(arreglo3)/ sizeof(arreglo3[0]);
    int elementoBorrar = 3;
    eliminarElementoArreglo(arreglo3, &validos3, elementoBorrar);
    mostrarArreglo(arreglo3, validos3);

    //Ejercicio 8. 1
    printf("\nEjercicio 8-1 \n");

    Alumno alus[20];
    Materia mats[5];
    Nota notas[100];

    cargarMaterias(mats);
    mostrarMaterias(mats);

    //Ejercicio 8. 2
    printf("\nEjercicio 8-2 \n");
    int numAlumnos = 0;
    agregarUnAlumno(alus, &numAlumnos);
    mostrarAlumno(alus, numAlumnos);

    //Ejercicio 8. 3
    printf("\nEjercicio 8-3 \n");
    int numNotas = 0;

    for (int i = 0; i < 2; i++)
    {
        int resultCarga = agregarNota(notas, alus, mats, &numNotas, numAlumnos);

        if (resultCarga == 1)
        {
            printf("Carga exitosa.\n");
        }
        else
        {
        printf("ERROR.\n");
        }
    }

    //Ejercicio 8. 4
    printf("\nEjercicio 8-4 \n");
    char nombre[30];
    printf("Ingrese el nombre del alumno: ");
    scanf("%s", &nombre);

    mostrarNotasPorAlumno(nombre, notas, alus, mats, numNotas, numAlumnos);

    return 0;
}

///Ejercicio 1. A) Crear un arreglo estático de 30 elementos de esta estructura y cargarlo mediante una función.
int cargarPersona(persona arr[], int validos)
{
    char continuar;
    int i = validos;

    do
    {
        printf("Ingrese los datos de las persona: \n");

        printf("NOMBRE: ");
        fflush(stdin);
        scanf("%s", &arr[i].nombre);

        printf("GENERO: ");
        fflush(stdin);
        scanf("%c", &arr[i].genero);

        printf("EDAD: ");
        fflush(stdin);
        scanf("%i", &arr[i].edad);

        i++;

        printf("Quiere agregar otra persona? s/n \n");
        fflush(stdin);
        scanf("%c", &continuar);
    }
    while(continuar == 's' || continuar == 'S');

    return i;
}

//AUX
void mostrarPersona(persona arr[], int validos)
{
    for(int i = 0; i < validos; i++)
    {
        printf("Persona %i: \n", i + 1);
        printf("Nombre: %s \n", arr[i].nombre);
        printf("Genero: %c \n", arr[i].genero);
        printf("Edad: %i \n", arr[i].edad);
        printf("\n");
    }
}

///Ejercicio 1. B) Hacer una función que cuente la cantidad de un género determinado.
void contarPersonaGenero(persona arr[], int validos, char generoParametro)
{
    int contador = 0;

    for(int i = 0; i < validos; i++)
    {
        if(arr[i].genero == generoParametro)
        {
            contador++;
        }
    }
    printf("Se han encontrado %i generos que considen con la busqueda. \n ", contador);
}

///Ejercicio 1. C) Hacer una función que copie los datos de todos los registros de un género determinado del arreglo anterior en
///otro arreglo del tamaño justo. Usar malloc dentro de la función y retornarlo o usar dos parámetros de tipo arreglo
///y crear el arreglo dinámico antes de la invocación.
persona* copiarPersonasGenero(persona arr[], int validos, char generoParametro, int* copiados)
{
    *copiados = 0; // Inicializa la variable que almacenará la cantidad de personas copiadas

    for(int i = 0; i < validos; i++)
    {
        if(arr[i].genero == generoParametro)
        {
            (*copiados)++; // Si el género de la persona coincide con el parámetro, incrementa la cantidad de copiados
        }
    }

    persona* copiaPersonas = (persona*)malloc(sizeof(persona) * (*copiados)); // Asigna memoria para el arreglo dinámico de copiaPersonas

    int j = 0;

    for(int i = 0; i < validos; i++) // Recorre nuevamente el arreglo original para copiar las personas del género especificado
    {
        if(arr[i].genero == generoParametro)
        {
            copiaPersonas[j] = arr[i]; // Copia la persona en el arreglo dinámico
            j++;
        }
    }

    return copiaPersonas; // Devuelve el arreglo dinámico con las personas copiadas
}

///Ejercicio 2. Codificar el algoritmo de ordenamiento por selección, sobre la estructura anterior teniendo en cuenta la edad como criterio de ordenación.
void ordenarPorEdadDescendente(persona arr[], int validos)
{
    for(int i = 0; i < validos; i++) // Itera a través de todo el arreglo
    {
        int maxIndice = i; // Inicializa el índice del elemento máximo como el índice actual

        for(int j = i + 1; j < validos; j++) // Itera a través del subarreglo no ordenado
        {
            if(arr[j].edad > arr[maxIndice].edad) // Compara edades para encontrar el máximo
            {
                maxIndice = j; // Actualiza el índice del elemento máximo
            }
        }

        persona temp = arr[i];
        arr[i] = arr[maxIndice];
        arr[maxIndice] = temp;
    }
}

///Ejercicio 3. Simular el uso de una pila de enteros a partir de la siguiente estructura:
void apilar(Pila* p, int valor)
{
    p->posTope = p->posTope + 1; // Sube la posición del tope como cuando agregas una carta encima.
    p->valores[p->posTope] = valor; // Pone el nuevo valor en la posición del tope.
}

void inicPila(Pila *p)
{
    p->posTope = -1; // Pone la pila vacía al principio, sin ninguna carta.
}

int desapilar(Pila *p)
{
    int valorSacado = p->valores[p->posTope]; // Tomar el valor en la posición del tope
    p->posTope -= 1; // Disminuir la posición del tope para indicar que quitaste una carta
    return valorSacado; // Devolver el valor que sacaste
}

int tope(Pila *p)
{
    return p->valores[p->posTope];
}

int pilavacia(Pila *p)
{
    return p->posTope == -1;
}

void mostrar(Pila *p)
{
    printf("\n--------------------------------------------------\n\n");
    for(int i = 0; i <= p->posTope; i++)
    {
        printf(" | %i | ", p->valores[i]);
    }
    printf("\n--------------------------------------------------\n\n");
}

void leer(Pila *p)
{
    int valor;
    printf("\nIngrese un valor: ");
    fflush(stdin);
    scanf("%i", &valor);

    apilar(p, valor);
}

///Ejercicio 4. Dadas dos pilas (como las anteriores) que se supone que tienen sus datos ordenados, generar una tercer pila que
///contenga los datos de las dos anteriores intercalados, de forma tal que queden ordenados.

void intercalarPilasOrdenadas(Pila *pila1, Pila *pila2, Pila *pilaResultante)
{
    while (!pilavacia(pila1) && !pilavacia(pila2)) // Mientras ambas pilas no estén vacías
    {
        if (tope(pila1) >= tope(pila2)) // Compara el tope de ambas pilas
        {
            apilar(pilaResultante, desapilar(pila1)); // Apila el tope de pila1 en la pila resultante
        }
        else
        {
            apilar(pilaResultante, desapilar(pila2)); // Apila el tope de pila2 en la pila resultante
        }
    }

    while (!pilavacia(pila1)) // Si pila2 está vacía, pero aún hay elementos en pila1
    {
        apilar(pilaResultante, desapilar(pila1)); // Apila los elementos restantes de pila1 en la pila resultante
    }

    while (!pilavacia(pila2)) // Si pila1 está vacía, pero aún hay elementos en pila2
    {
        apilar(pilaResultante, desapilar(pila2)); // Apila los elementos restantes de pila2 en la pila resultante
    }
    mostrar(pilaResultante);
}

///Ejercicio 5. Función insertar orden en un arreglo.
void insertarArreglo(int arreglo[], int* tamanio, int valor)
{
    int i = *tamanio - 1; //Inicializa 'i' en la posicion del ultimo elemento

    while(i >= 0 && arreglo[i] > valor) // Mientras 'i' sea valido y el valor en arreglo[i] sea mayor que valor.
    {
        arreglo[i + 1] = arreglo[i]; // Desplaza los elemento hacia adelante para hacer espacio para el nuevo valor.
        i--; // Decrementa 'i' para moverte hacia atras en el arreglo
    }

    arreglo[i + 1] = valor; // Inserta el valor en la posicion correcta.
    (*tamanio++); // Incrementa el tamaño del arreglo
}

void mostrarArreglo(int arreglo[], int validos)
{
    for(int i = 0; i < validos; i++)
    {
        printf("%i ", arreglo[i]);
    }
}

///Ejercicio 6. Algoritmo de ordenamiento por inserción.
void ordenamientoPorInsercion(int arreglo[], int validos)
{
    for(int i = 1; i < validos; i++) // Recorremos el arreglo desde el segundo elemento (índice 1)
    {
        int valorActual = arreglo[i]; // Tomamos el elemento actual que deseamos insertar en la parte ordenada
        int j = i; // Inicializamos 'j' con el índice actual

        while(j > 0 && arreglo[j - 1] > valorActual) // Mientras 'j' sea mayor que 0 y el elemento previo sea mayor que el valor actual
        {
            arreglo[j] = arreglo[j - 1]; // Desplazamos el elemento previo hacia adelante
            j--; // Movemos 'j' hacia atrás para comparar con el siguiente elemento previo
        }

        arreglo[j] = valorActual; // Insertamos el valor actual en su posición correcta en la parte ordenada
    }
}

///Ejercicio 7. Función eliminar un elemento de un arreglo. (ver por desplazamiento si es ordenado)
void eliminarElementoArreglo(int arreglo[], int* validos, int elementoBorrar)
{
    for(int i = 0; i < *validos; i++)
    {
        if(arreglo[i] == elementoBorrar)
        {
            (*validos)--;
            printf("Elemento Borrado\n");
            return;
        }
    }
    printf("Elemento no encontrado. \n");
}

///Ejercicio 8. 1) Cargar el arreglo de Materia
void cargarMaterias(Materia mats[])
{
    for(int i = 0; i < 5; i++)
    {
        printf("Ingrese el codigo de la materia %i: ", i + 1);
        fflush(stdin);
        scanf("%i", &mats[i].codigo);

        printf("Ingrese el nombre de la materia %i: ", i + 1);
        fflush(stdin);
        scanf("%s", &mats[i].nombreMat);
    }
}

void mostrarMaterias(Materia mats[])
{
    for(int i  = 0; i < 5; i++)
    {
        printf("Codigo: %i, Nombre: %s\n", mats[i].codigo, mats[i].nombreMat);
    }
}

///Ejercicio 8. 2)  Agregar un Alumno
void agregarUnAlumno(Alumno alus[], int *numAlumnos)
{
    if(*numAlumnos < 20)
    {
        printf("Ingrese la matricula del alumno: ");
        fflush(stdin);
        scanf("%i", &alus[*numAlumnos].matricula);

        printf("Ingrese el nombre del alumno: ");
        fflush(stdin);
        scanf("%s", &alus[*numAlumnos].nombre);

        (*numAlumnos)++;
        printf("Alumno agregado correctamente. \n");
    }
    else
    {
        printf("No se pueden agregar mas alumnos, el limite es 20. \n");
    }
}

void mostrarAlumno(Alumno alus[], int numAlumnos)
{
    for(int i = 0; i < numAlumnos; i++)
    {
        printf("Matricula: %i, Nombre %s\n", alus[i].matricula, alus[i].nombre);
    }
}

///Ejercicio 8. 3) Agregar una nota con validaciones
int agregarNota(Nota notas[], Alumno alus[], Materia mats[], int *numNotas, int numAlumnos)
{
    if (*numNotas < 100)
    {
        int matricula, codigo;

        printf("Ingrese la matricula: ");
        scanf("%i", &matricula);

        int indiceAlumno = obtenerAlumnoPorMatricula(matricula, alus, numAlumnos);

        if (indiceAlumno == -1)
        {
            return 0;
        }

        printf("Ingrese el codigo: ");
        scanf("%i", &codigo);

        int indiceMateria = obtenerMateriaPorCodigo(mats, 5, codigo);

        if (indiceMateria == -1)
        {
            return 0;
        }

        printf("Ingrese la nota a cargar: ");
        scanf("%i", &notas[*numNotas].nota);

        notas[*numNotas].codigo = mats[indiceMateria].codigo;
        notas[*numNotas].matricula = alus[indiceAlumno].matricula;
        (*numNotas)++;

        return 1;
    }
    else
    {
        printf("No se pueden agregar más notas, el límite es 100.\n");
        return 0;
    }
}

int obtenerAlumnoPorMatricula(int matricula, Alumno alus[], int numAlumnos)
{
    for (int i = 0; i < numAlumnos; i++)
    {
        if (matricula == alus[i].matricula)
        {
            return i;
        }
    }

    printf("Alumno no encontrado.\n");
    return -1;
}

int obtenerMateriaPorCodigo(Materia mats[], int validosMateria, int codigo)
{
    for (int i = 0; i < validosMateria; i++)
    {
        if (codigo == mats[i].codigo)
        {
            return i;
        }
    }

    printf("Materia no encontrada.\n");
    return -1;
}

///Ejercicio 8. 4)
void mostrarNotasPorAlumno(char nombre[], Nota notas[], Alumno alus[], Materia mats[], int numNotas, int numAlumnos)
{
    int indiceAlumno = obtenerAlumnoPorNombre(nombre, alus, numAlumnos);  // Buscar el índice del alumno por su nombre

    if (indiceAlumno == -1)
    {
        printf("Alumno no encontrado.\n");
        return;
    }

    printf("Notas de %s:\n", alus[indiceAlumno].nombre); // Mostrar el encabezado con el nombre del alumno

    for (int i = 0; i < numNotas; i++) // Recorrer las notas
    {
        if (notas[i].matricula == alus[indiceAlumno].matricula ) // Si la matrícula de la nota coincide con la del alumno
        {
            int indiceMateria = obtenerMateriaPorCodigo(mats, 5, notas[i].codigo); // Obtener el índice de la materia asociada a la nota

            if (indiceMateria != -1) // Si se encuentra la materia, mostrar la nota
            {
                printf("Materia: %s, Nota: %d\n", mats[indiceMateria].nombreMat, notas[i].nota);
            }
        }
    }
}

int obtenerAlumnoPorNombre(char nombre[], Alumno alus[], int numAlumnos)
{
    for (int i = 0; i < numAlumnos; i++)
    {
        if (strcmp(nombre, alus[i].nombre) == 0)
        {
            return i;
        }
    }

    printf("Alumno no encontrado.\n");
    return -1;
}
