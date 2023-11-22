#include "Empleado.h"

///--------------------FUNCIONES PARA EMPLEADOS--------------------
//Funcion para registrar un nuevo empleado
empleados_laboratorio registrarEmpleado()
{
    empleados_laboratorio empleado;
    int flagDNI = 0, nombreValido = 0;
    int flag = 0;

    // Validacion del DNI
    do
    {
        printf("Ingrese DNI: \n");
        fflush(stdin);
        scanf("%d", &empleado.dni);

        flagDNI = comprobarDNIRepetido(empleado.dni);

        if (flagDNI != 0)
        {
            printf("El DNI ya existe. Pruebe con otro. \n");
        }
    }
    while (flagDNI != 0);

    // Validacion del nombre y apellido
    do
    {
        printf("Ingrese apellido y nombre: \n");
        fflush(stdin);
        gets(&empleado.apellidoYnombre);


        nombreValido = verificarApeYNombre(empleado.apellidoYnombre);

        if (!nombreValido)
        {
            printf("Nombre y apellido no valido. Intente nuevamente.\n");
        }
    }
    while (!nombreValido);

    do
    {
        printf("Ingrese usuario: \n");
        fflush(stdin);
        scanf("%s", empleado.usuario);

        flag = comprobarUsuarioRepetido(empleado.usuario);

        if(flag!=0)
            printf("El usuario ya existe. Pruebe con otro \n");

    }
    while(flag!=0);
    //strcpy(empleado.usuario, usuario);

    printf("Ingrese contrasenia: \n");
    fflush(stdin);
    scanf("%s", empleado.contrasenia);

    do
    {
        printf("Ingrese perfil: (administrativo / administrador / profesional)\n");
        fflush(stdin);
        scanf("%s", empleado.perfil);
    }
    while(comprobarPerfilValido(empleado.perfil));

    return empleado;
}

int comprobarPerfilValido(char perfil[])
{
    int flag = 1;

    if (strcmp(perfil, "administrativo") == 0 || strcmp(perfil, "administrador") == 0 || strcmp(perfil, "profesional") == 0)
    {
        flag = 0;
    }

    if(flag)
    {
        printf("Debes ingresar un perfil valido. \n");
    }

    return flag;
}

int comprobarDNIRepetido(int dni)
{
    FILE* archivoE = fopen("empleados.bin", "rb");
    empleados_laboratorio aux;
    int flag=0;

    if(archivoE!=NULL)
    {
        while(fread(&aux, sizeof(empleados_laboratorio), 1, archivoE)==1)
        {
            if(aux.dni== dni)//el dni ya existe
            {
                flag=1;
            }

        }
        fclose(archivoE);
    }

    return flag;
}

int comprobarUsuarioRepetido(char usuario[])
{
    FILE* archivoE = fopen("empleados.bin", "rb");
    empleados_laboratorio aux;
    int flag=0;

    if(archivoE!=NULL)

    {
        while(fread(&aux, sizeof(empleados_laboratorio), 1, archivoE)==1)
        {
            if(strcmp(aux.usuario, usuario)==0)//el nombre de usuario ya existe
            {
                flag=1;
            }

        }
        fclose(archivoE);
    }

    return flag;
}

// Función para comparar dos empleados por su nombre
int compararEmpleados(const void *a, const void *b)
{
    empleados_laboratorio *empleadoA = (empleados_laboratorio *)a;
    empleados_laboratorio *empleadoB = (empleados_laboratorio *)b;
    return strcmp(empleadoA->apellidoYnombre, empleadoB->apellidoYnombre);
}

void guardarEmpleadoEnArchivo(empleados_laboratorio empleado)
{
    FILE *archivoE = fopen("empleados.bin", "rb");
    empleados_laboratorio empleados[100];  // Asumiendo que no hay más de 100 empleados
    int numEmpleados = 0;

    if (archivoE != NULL)
    {
        while (fread(&empleados[numEmpleados], sizeof(empleados_laboratorio), 1, archivoE) == 1)
        {
            numEmpleados++;
        }
        fclose(archivoE);
    }

    // Agregar el nuevo empleado
    empleados[numEmpleados] = empleado;
    numEmpleados++;

    // Ordenar la lista de empleados alfabeticamente
    /*La función qsort en C se utiliza para ordenar arreglos. Esta función esta presente en la biblioteca stdlib.h y ordena un arreglo internamente, es decir, lo modifica.
    La sintaxis de qsort es la siguiente: qsort (arreglo, longitud del arreglo, tamaño de cada elemento del arreglo, función que compara)*/
    qsort(empleados, numEmpleados, sizeof(empleados_laboratorio), compararEmpleados);

    // Escribir todos los empleados de nuevo en el archivo
    archivoE = fopen("empleados.bin", "wb");
    if (archivoE == NULL)
    {
        printf("Error al abrir el archivo. \n");
    }
    else
    {
        for (int i = 0; i < numEmpleados; i++)
        {
            fwrite(&empleados[i], sizeof(empleados_laboratorio), 1, archivoE);
        }
        fclose(archivoE);
        printf("Empleado registrado exitosamente.\n");
    }
}

//Funcion para mostrar TODOS los empleados
void mostrarArchivoDeEmpleados()
{
    FILE *archivoE = fopen("empleados.bin", "rb");
    empleados_laboratorio aux;

    if (archivoE != NULL)
    {
        while (fread(&aux, sizeof(empleados_laboratorio), 1, archivoE) == 1)
        {
            printf("==========================================\n");
            printf("DNI: %i \n", aux.dni);
            printf("Apellido y nombre: %s \n", aux.apellidoYnombre);
            printf("Usuario: %s \n", aux.usuario);
            printf("Contrasenia: %s \n", aux.contrasenia);
            printf("Perfil: %s \n", aux.perfil);
            printf("==========================================\n");
        }
        fclose(archivoE);
    }
}

void mostrarArchivoDeEmpleadosConAsteriscos()
{
    FILE *archivoE = fopen("empleados.bin", "rb");
    empleados_laboratorio aux;

    if (archivoE != NULL)
    {
        while (fread(&aux, sizeof(empleados_laboratorio), 1, archivoE) == 1)
        {
            printf("==========================================\n");
            printf("DNI: %i \n", aux.dni);
            printf("Apellido y nombre: %s \n", aux.apellidoYnombre);
            printf("Usuario: %s \n", aux.usuario);

            // Mostrar la contrasenia como asteriscos
            printf("Contrasenia: ");
            for (size_t i = 0; i < strlen(aux.contrasenia); i++)
            {
                printf("*");
            }
            printf("\n");

            printf("Perfil: %s \n", aux.perfil);
            printf("==========================================\n");
        }
        fclose(archivoE);
    }
}

//Funcion para buscar si un empleado esta o no registrado
empleados_laboratorio buscarEmpleadoDeArchivo(char usuario[], char contrasenia[])
{
    FILE *archivoE = fopen("empleados.bin", "rb");

    empleados_laboratorio empleados;
    if (archivoE != NULL)
    {
        while (fread(&empleados, sizeof(empleados_laboratorio), 1, archivoE) == 1)
        {
            if ((strcmp(empleados.usuario, usuario) == 0) && (strcmp(empleados.contrasenia, contrasenia) == 0))
            {
                return empleados;
            }
        }
        fclose(archivoE);
    }
}

void buscarDniSolicitado(int dniABuscar)
{
    FILE* archivoE = fopen("empleados.bin", "rb");
    empleados_laboratorio aux;

    if (archivoE != NULL)
    {
        while (fread(&aux, sizeof(empleados_laboratorio), 1, archivoE) == 1)
        {
            if (aux.dni == dniABuscar)
            {
                printf("============USUARIO ENCONTRADO============\n");
                printf("DNI: %i \n", aux.dni);
                printf("Apellido y nombre: %s \n", aux.apellidoYnombre);
                printf("Usuario: %s \n", aux.usuario);
                printf("Contrasenia: %s \n", aux.contrasenia);
                printf("Perfil: %s \n", aux.perfil);
                printf("==========================================\n");

            }
        }

        fclose(archivoE);
    }
    else
    {
        printf("Error al abrir el archivo.\n");
    }
}

// Funcion para validar el apellido y nombre del empleado
int verificarApeYNombre(const char *apeYnombreEmpleado)
{
    int apeYnombreValido = 1;
    int longitud = strlen(apeYnombreEmpleado); // Obtener la longitud del nombre y el apellido

    // Validar la longitud y el primer caracter
    if ((longitud == 0) || (apeYnombreEmpleado[0] == ' ') || (longitud < 3) || (longitud > 30))
    {
        apeYnombreValido = 0;
    }
    else
    {
        for (int i = 0; i < longitud; i++)
        {
            // Verificar que los caracteres sean letras o espacios
            if (!((apeYnombreEmpleado[i] >= 'A' && apeYnombreEmpleado[i] <= 'Z') ||
                    (apeYnombreEmpleado[i] >= 'a' && apeYnombreEmpleado[i] <= 'z') ||
                    (apeYnombreEmpleado[i] == ' ')))
            {
                apeYnombreValido = 0;
                break;
            }
        }
    }

    return apeYnombreValido;
}
