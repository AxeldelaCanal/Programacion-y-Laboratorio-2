#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

typedef struct
{
    char nombreAnimal[30];
    int cantidad;
    int idHabitat;
    int idEspecie;
    char especie[20];
} registroArchivo;

typedef struct
{
    char nombreAnimal[30];
    int cantidad;
    int idHabitat; // 1 - selva, 2- savana, 3-bosque, 4-mar
} Animal;

typedef struct nodoAnimal
{
    Animal dato;
    struct nodoAnimal* sig;
} nodoAnimal;

typedef struct nodoEspecie
{
    int idEspecie;
    char especie [20]; //"Mamiferos","Aves","Reptiles","Peces"
    nodoAnimal* animales;
    struct nodoEspecie* sig;
} nodoEspecie;

/*Se pide desarrollar un sistema que administre y gestione animales que viven en un zoológico, a partir del archivo que contiene registros del tipo “registroArchivo” que figura en el campus debajo de este enunciado (“animales.dat”), el cual fue cargado con los datos “mezclados”.
A fin de realizar esto, codifique las funciones necesarias para administrar la lista de especies y la sublista de animales teniendo en cuenta:
-La inserción en la lista se hace en orden creciente por idEspecie.
-La inserción en la sublista se hace en orden creciente por nombreAnimal.
Utilizando la información en el archivo, realice las siguientes funciones:
1)…cargarListaDeEspecies(…) →  esta función recorrerá el archivo y pasará la información a la lista (utilizando las funciones necesarias).
2)… EspeciesAFile (…) →  esta función pasará de la lista de especies a un nuevo archivo, que será uno por cada especie, todos los animales que existen en cada sublista.
3)Mostrar Los animales de una especie en particular.
4)Mostrar los animales de un hábitat en particular.
5)Informar el tipo de especie que posee mayor cantidad de animales.
6)Eliminar de la lista una especie, donde también se eliminarán todos los animales de esa especie (llega por parámetro el tipo de especie).
7)Desarrolle un main para probar todo el funcionamiento del sistema.
*/

///PROTOTIPADOS:
void cargarListaDeEspecies(nodoEspecie** especies, const char* archivo);
void mostrarListaDeEspecies(nodoEspecie* especies);
void EspeciesAFile(nodoEspecie* especies);
void mostrarEspeciesEnArchivos(nodoEspecie* especies);
void mostrarAnimalesDeEspecie(nodoEspecie* especies, int idEspecie);
void mostrarAnimalesDeHabitat(nodoEspecie* especies, int idHabitat);
char* especieConMasAnimales(nodoEspecie* especies);
void eliminarEspecie(nodoEspecie** especies, int idEspecie);



int main()
{
    nodoEspecie* especies = NULL;

    ///PUNTO 1:
    printf("PUNTO 1:\n");
    cargarListaDeEspecies(&especies, "animales.dat");
    mostrarListaDeEspecies(especies);

    ///PUNTO 2:
    printf("\nPUNTO 2:\n");
    EspeciesAFile(especies);
    mostrarEspeciesEnArchivos(especies);

    ///PUNTO 3:
    printf("\nPUNTO 3:\n");
    printf("Animales de una especie en particular:\n");
    mostrarAnimalesDeEspecie(especies, 1); // Cambia el ID de especie según tus datos

    ///PUNTO 4:
    printf("\nPUNTO 4:");
    printf("\nAnimales de un habitat en particular:\n");
    mostrarAnimalesDeHabitat(especies, 1); // Cambia el ID de hábitat según tus datos

    ///PUNTO 5:
    printf("\nPUNTO 5:\n");
    char* especieMayor = especieConMasAnimales(especies);
    if (especieMayor != NULL)
    {
        printf("\nLa especie con mas animales es: %s\n", especieMayor);
    }
    else
    {
        printf("No hay especies registradas.\n");
    }

    ///PUNTO 6:
    printf("\nPUNTO 6:\n");
    eliminarEspecie(&especies, 2); // Cambia el ID de especie a eliminar según tus datos

    return 0;
}

///PUNTO 1)
// Función para cargar la lista de especies a partir del archivo
void cargarListaDeEspecies(nodoEspecie** especies, const char* archivo)
{
    FILE* file = fopen(archivo, "rb");
    if (file == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    registroArchivo registro;
    while (fread(&registro, sizeof(registroArchivo), 1, file) == 1)
    {
        // Buscar la especie en la lista de especies
        nodoEspecie* especieActual = *especies;
        nodoEspecie* especieAnterior = NULL;
        while (especieActual != NULL && registro.idEspecie != especieActual->idEspecie)
        {
            especieAnterior = especieActual;
            especieActual = especieActual->sig;
        }

        // Si no encontramos la especie, la creamos y la insertamos en orden
        if (especieActual == NULL)
        {
            nodoEspecie* nuevaEspecie = (nodoEspecie*)malloc(sizeof(nodoEspecie));
            nuevaEspecie->idEspecie = registro.idEspecie;
            strcpy(nuevaEspecie->especie, registro.especie);
            nuevaEspecie->animales = NULL;

            if (especieAnterior == NULL)
            {
                nuevaEspecie->sig = *especies;
                *especies = nuevaEspecie;
            }
            else
            {
                nuevaEspecie->sig = especieAnterior->sig;
                especieAnterior->sig = nuevaEspecie;
            }

            especieActual = nuevaEspecie;
        }

        // Insertar el animal en la sublista en orden por nombreAnimal
        nodoAnimal* animalActual = especieActual->animales;
        nodoAnimal* animalAnterior = NULL;
        while (animalActual != NULL && strcmp(registro.nombreAnimal, animalActual->dato.nombreAnimal) > 0)
        {
            animalAnterior = animalActual;
            animalActual = animalActual->sig;
        }

        // Crear un nuevo Animal y asignarle los campos relevantes de registroArchivo
        Animal nuevoAnimalData;
        strcpy(nuevoAnimalData.nombreAnimal, registro.nombreAnimal);
        nuevoAnimalData.cantidad = registro.cantidad;
        nuevoAnimalData.idHabitat = registro.idHabitat;

        nodoAnimal* nuevoAnimal = (nodoAnimal*)malloc(sizeof(nodoAnimal));
        nuevoAnimal->dato = nuevoAnimalData;

        if (animalAnterior == NULL)
        {
            nuevoAnimal->sig = especieActual->animales;
            especieActual->animales = nuevoAnimal;
        }
        else
        {
            nuevoAnimal->sig = animalAnterior->sig;
            animalAnterior->sig = nuevoAnimal;
        }
    }

    fclose(file);
}
///PUNTO 1) AUX
void mostrarListaDeEspecies(nodoEspecie* especies)
{
    printf("Lista de Especies:\n");
    while (especies != NULL)
    {
        printf("\nID de Especie: %d, Nombre de Especie: %s\n", especies->idEspecie, especies->especie);

        nodoAnimal* animal = especies->animales;
        printf("Animales:\n");
        while (animal != NULL)
        {
            printf("Nombre: %s, Cantidad: %d, Habitat: %d\n",
                   animal->dato.nombreAnimal, animal->dato.cantidad, animal->dato.idHabitat);
            animal = animal->sig;
        }

        especies = especies->sig;
    }
}

///PUNTO 2)
// Función para guardar las especies en archivos separados
void EspeciesAFile(nodoEspecie* especies)
{
    // Recorre la lista de especies y crea un archivo por cada especie con sus animales.
    while (especies != NULL)
    {
        FILE* file = fopen(especies->especie, "wb");
        if (file == NULL)
        {
            printf("No se pudo crear el archivo para %s.\n", especies->especie);
            especies = especies->sig;
            continue;
        }

        nodoAnimal* animal = especies->animales;
        while (animal != NULL)
        {
            fwrite(&animal->dato, sizeof(Animal), 1, file);
            animal = animal->sig;
        }

        fclose(file);
        especies = especies->sig;
    }
}
///PUNTO 2) AUX
void mostrarEspeciesEnArchivos(nodoEspecie* especies)
{
    printf("Especies en Archivos:\n");
    while (especies != NULL)
    {
        printf("\nEspecie: %s\n", especies->especie);

        // Abre el archivo de la especie y muestra sus animales
        FILE* file = fopen(especies->especie, "rb");
        if (file == NULL)
        {
            printf("No se pudo abrir el archivo para %s.\n", especies->especie);
        }
        else
        {
            Animal animal;
            while (fread(&animal, sizeof(Animal), 1, file) == 1)
            {
                printf("Nombre: %s, Cantidad: %d, Habitat: %d\n",
                       animal.nombreAnimal, animal.cantidad, animal.idHabitat);
            }
            fclose(file);
        }

        especies = especies->sig;
    }
}

///PUNTO 3)
// Función para mostrar los animales de una especie en particular
void mostrarAnimalesDeEspecie(nodoEspecie* especies, int idEspecie)
{
    // Busca la especie por su idEspecie y muestra los animales.
    while (especies != NULL)
    {
        if (especies->idEspecie == idEspecie)
        {
            nodoAnimal* animal = especies->animales;
            while (animal != NULL)
            {
                printf("Nombre: %s, Cantidad: %d, Habitat: %d\n",
                       animal->dato.nombreAnimal, animal->dato.cantidad, animal->dato.idHabitat);
                animal = animal->sig;
            }
            return;
        }
        especies = especies->sig;
    }
}

///PUNTO 4)
// Función para mostrar los animales de un hábitat en particular
void mostrarAnimalesDeHabitat(nodoEspecie* especies, int idHabitat)
{
    while (especies != NULL)
    {
        nodoAnimal* animal = especies->animales;
        while (animal != NULL)
        {
            if (animal->dato.idHabitat == idHabitat)
            {
                printf("Especie: %s, Nombre: %s, Cantidad: %d, Habitat: %i\n",
                       especies->especie, animal->dato.nombreAnimal, animal->dato.cantidad, animal->dato.idHabitat);
            }
            animal = animal->sig;
        }
        especies = especies->sig;
    }
}

///PUNTO 5)
// Función para determinar la especie con mayor cantidad de animales
char* especieConMasAnimales(nodoEspecie* especies)
{
    char* especieMayor = NULL;
    int cantidadMayor = 0;

    while (especies != NULL)
    {
        int cantidadTotal = 0;
        nodoAnimal* animal = especies->animales;
        while (animal != NULL)
        {
            cantidadTotal += animal->dato.cantidad;
            animal = animal->sig;
        }

        if (cantidadTotal > cantidadMayor)
        {
            cantidadMayor = cantidadTotal;
            especieMayor = especies->especie;
        }

        especies = especies->sig;
    }

    return especieMayor;
}

///PUNTO 6)
// Función para eliminar una especie y sus animales
void eliminarEspecie(nodoEspecie** especies, int idEspecie)
{
    nodoEspecie* prev = NULL;
    nodoEspecie* current = *especies;

    while (current != NULL)
    {
        if (current->idEspecie == idEspecie)
        {
            // Eliminar la especie y sus animales
            if (prev == NULL)
                *especies = current->sig;
            else
                prev->sig = current->sig;

            free(current);

            return;
        }
        prev = current;
        current = current->sig;
    }
}


