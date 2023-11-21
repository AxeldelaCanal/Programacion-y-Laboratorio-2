#include "Empleado.h"

///--------------------FUNCIONES PARA EMPLEADOS--------------------
//Funcion para registrar un nuevo empleado
empleados_laboratorio registrarEmpleado()
{
    empleados_laboratorio empleado;
    int flagDNI = 0, nombreValido = 0;
    int flag = 0;

    // Validación del DNI
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

    // Validación del nombre y apellido
    do
    {
        printf("Ingrese apellido y nombre: \n");
        fflush(stdin);
        scanf("%s", empleado.apellidoYnombre);

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

    printf("Ingrese perfil: \n");
    fflush(stdin);
    scanf("%s", empleado.perfil);

    return empleado;
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

//Funcion para guardar el nuevo empleado en el archivo
void guardarEmpleadoEnArchivo(empleados_laboratorio empleado)
{
    FILE *archivoE = fopen("empleados.bin", "ab");

    if (archivoE == NULL)
    {
        printf("Error al abrir el archivo. \n");
    }
    else
    {
        fwrite(&empleado, sizeof(empleados_laboratorio), 1, archivoE);
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
            printf("Contraseña: %s \n", aux.contrasenia);
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

            // Mostrar la contraseña como asteriscos
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
                printf("Contraseña: %s \n", aux.contrasenia);
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

///AUXILIAR:
// Función para validar el apellido y nombre del empleado
int verificarApeYNombre(const char *apeYnombreEmpleado)
{
    int apeYnombreValido = 1;
    int longitud = strlen(apeYnombreEmpleado); // Obtener la longitud del nombre y el apellido

    // Validar la longitud y el primer carácter
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

