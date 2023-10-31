#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> // Incluye la biblioteca necesaria para GetConsoleScreenBufferInfo en Windows

// Definición de las estructuras
typedef struct IngresoLaboratorio
{
    int NroIngreso;
    char FechaIngreso[11];
    char FechaRetiro[11];
    int DniPaciente;
    int MatriculaProfesional;
    int Eliminado; // 0 para no eliminado, 1 para eliminado
    struct IngresoLaboratorio *siguiente; // Apuntador al siguiente ingreso en la lista
} IngresoLaboratorio;

typedef struct Paciente
{
    char ApellidoNombre[41];
    int Edad;
    int Dni;
    char Direccion[31];
    char Telefono[16];
    int Eliminado; // 0 para no eliminado, 1 para eliminado
    struct Paciente *izquierda, *derecha; // Apuntadores al hijo izquierdo y derecho en el árbol
    IngresoLaboratorio *ingresos; // Apuntador al primer ingreso en la lista de ingresos
} Paciente;

// Prototipos de funciones

///PROTOTIPADOS PACIENTE:
Paciente *crearPaciente(char *ApellidoNombre, int Edad, int Dni, char *Direccion, char *Telefono);
Paciente *buscarPaciente(Paciente *raiz, int dni);
void altaPaciente(Paciente **raiz, Paciente *nuevoPaciente);
void modificarPaciente(Paciente *raiz, int dni, char *nuevoApellidoNombre, int nuevaEdad, char *nuevaDireccion, char *nuevoTelefono);
void bajaPaciente(Paciente *raiz, int dni);

///PROTOTIPADOS INGRESO LABORATORIO:
IngresoLaboratorio *crearIngreso(int NroIngreso, char *FechaIngreso, char *FechaRetiro, int DniPaciente, int MatriculaProfesional);
void agregarIngreso(Paciente *paciente, IngresoLaboratorio *ingreso);
void altaIngreso(Paciente *raiz, int dniPaciente, IngresoLaboratorio *nuevoIngreso);
IngresoLaboratorio *buscarIngreso(Paciente *paciente, int nroIngreso);
void modificarIngreso(Paciente *raiz, int dniPaciente, int nroIngreso, char *nuevaFechaIngreso, char *nuevaFechaRetiro, int nuevaMatricula, int numeroIngreso);
void bajaIngreso(Paciente *raiz, int dniPaciente, int nroIngreso);

///PROTOTIPADOS PACIENTE MENU:
void agregarPacienteMenu(Paciente **raiz);
void modificarPacienteMenu(Paciente *raiz);
void eliminarPaciente(Paciente *raiz, int dni);

///PROTOTIPADOS LABORATORIO MENU:
void agregarIngresoMenu(Paciente *raiz);
void modificarIngresoMenu(Paciente *raiz);
void eliminarIngresoMenu(Paciente *raiz);

///PROTOTIPADOS TEMP:
void mostrarPacienteYIngresos(Paciente *raiz, int dniPaciente);
void mostrarIngresos(IngresoLaboratorio *ingresos);
void mostrarTodosLosPacientesYIngresos(Paciente *raiz);


 int anchoConsola;
// Función para centrar el texto en la consola automáticamente
void centrarTextoAuto(const char *texto, int y) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    anchoConsola = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int longitudTexto = strlen(texto);
    int espaciosEnBlanco = (anchoConsola - longitudTexto) / 2;

    // Ajusta la posición del cursor en la fila "y" y centra el texto
    COORD posicionCursor;
    posicionCursor.X = espaciosEnBlanco;
    posicionCursor.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), posicionCursor);

    printf("%s", texto);
}



int main()
{
    Paciente *raiz = NULL; // Declaración de la raíz del árbol
    cargarDatosDesdeArchivo(&raiz); // Cargar datos almacenados previamente
    int dniMostrar;
    int dniAEliminar;
    int opcion;

    do {
        system("cls");

        int fila = 5; // Fila donde se centrará el texto
        centrarTextoAuto("----------------------------------------------", fila);
        fila++;
        centrarTextoAuto("----------------MENU PRINCIPAL----------------", fila);
        fila++;
        centrarTextoAuto("----------------------------------------------", fila);
        fila++;
        centrarTextoAuto("1. Agregar paciente", fila);
        fila++;
        centrarTextoAuto("2. Modificar paciente", fila);
        fila++;
        centrarTextoAuto("3. Eliminar paciente", fila);
        fila++;
        centrarTextoAuto("4. Agregar ingreso", fila);
        fila++;
        centrarTextoAuto("5. Modificar ingreso", fila);
        fila++;
        centrarTextoAuto("6. Eliminar ingreso", fila);
        fila++;
        centrarTextoAuto("7. Mostrar Paciente e Ingreso", fila);
        fila++;
        centrarTextoAuto("8. Mostrar todos los Pacientes e Ingresos", fila);
        fila++;
        centrarTextoAuto("9. Salir", fila);
        fila++;

        centrarTextoAuto("Seleccione una opcion: \n", fila);

        // Ajusta la posición del cursor para la entrada del usuario
        COORD posicionCursor;
        posicionCursor.X = (anchoConsola - 1) / 2;
        posicionCursor.Y = fila;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), posicionCursor);

        scanf("%d", &opcion);
        system("cls");

        switch (opcion)
        {
        case 1:
            agregarPacienteMenu(&raiz);
            guardarDatosEnArchivo(*raiz);
            break;
        case 2:
            modificarPacienteMenu(raiz);
            guardarDatosEnArchivo(*raiz);
            break;
        case 3:
            printf("Ingrese el DNI del paciente a eliminar: ");
            scanf("%d", &dniAEliminar);
            eliminarPaciente(raiz, dniAEliminar);
            guardarDatosEnArchivo(raiz);
            break;
        case 4:
            agregarIngresoMenu(raiz);
            guardarDatosEnArchivo(*raiz);
            break;
        case 5:
            modificarIngresoMenu(raiz);
            guardarDatosEnArchivo(*raiz);
            break;
        case 6:
            eliminarIngresoMenu(raiz);
            break;
        case 7:
            printf("Ingrese el DNI del paciente a mostrar: ");
            scanf("%d", &dniMostrar);
            mostrarPacienteYIngresos(raiz, dniMostrar);
            break;
        case 8:
            mostrarTodosLosPacientesYIngresos(raiz);

            break;
        case 9:
            printf("Saliendo del programa...\n");
            break;
        default:
            centrarTextoAuto("Opcion no valida. Por favor, intente de nuevo.", fila);
        }
        system("pause");
    }
    while (opcion != 9);
    guardarDatosEnArchivo(raiz);

    return 0;
}



///------------------------- FUNCIONES PACIENTE -------------------------
Paciente *crearPaciente(char *ApellidoNombre, int Edad, int Dni, char *Direccion, char *Telefono)
{
    Paciente *nuevoPaciente = (Paciente *)malloc(sizeof(Paciente));
    strcpy(nuevoPaciente->ApellidoNombre, ApellidoNombre);
    nuevoPaciente->Edad = Edad;
    nuevoPaciente->Dni = Dni;
    strcpy(nuevoPaciente->Direccion, Direccion);
    strcpy(nuevoPaciente->Telefono, Telefono);
    nuevoPaciente->Eliminado = 0;
    nuevoPaciente->izquierda = nuevoPaciente->derecha = NULL;
    nuevoPaciente->ingresos = NULL;

    return nuevoPaciente;
}

// Función para buscar un paciente
Paciente *buscarPaciente(Paciente *raiz, int dni)
{
    if (raiz == NULL)
    {
        return NULL;
    }
    else if (raiz->Dni == dni)
    {
        return raiz;
    }
    else if (raiz->Dni > dni)
    {
        return buscarPaciente(raiz->izquierda, dni);
    }
    else
    {
        return buscarPaciente(raiz->derecha, dni);
    }
}

// Función para dar de alta un paciente
void altaPaciente(Paciente **raiz, Paciente *nuevoPaciente)
{
    if (*raiz == NULL)
    {
        *raiz = nuevoPaciente;
    }
    else if ((*raiz)->Dni > nuevoPaciente->Dni)
    {
        altaPaciente(&(*raiz)->izquierda, nuevoPaciente);
    }
    else if ((*raiz)->Dni < nuevoPaciente->Dni)
    {
        altaPaciente(&(*raiz)->derecha, nuevoPaciente);
    }
    else
    {
        printf("El paciente con DNI %d ya existe.\n", nuevoPaciente->Dni);
    }
}

// Función para modificar un paciente
void modificarPaciente(Paciente *raiz, int dni, char *nuevoApellidoNombre, int nuevaEdad, char *nuevaDireccion, char *nuevoTelefono)
{
    Paciente *paciente = buscarPaciente(raiz, dni);
    if (paciente != NULL)
    {
        strcpy(paciente->ApellidoNombre, nuevoApellidoNombre);
        paciente->Edad = nuevaEdad;
        strcpy(paciente->Direccion, nuevaDireccion);
        strcpy(paciente->Telefono, nuevoTelefono);
    }
    else
    {
        printf("El paciente con DNI %d no existe.\n", dni);
    }
}

// Función para dar de baja un paciente
void bajaPaciente(Paciente *raiz, int dni)
{
    Paciente *paciente = buscarPaciente(raiz, dni);
    if (paciente != NULL)
    {
        while (paciente->ingresos != NULL)
        {
            IngresoLaboratorio *ingreso = paciente->ingresos;
            paciente->ingresos = paciente->ingresos->siguiente;
            free(ingreso); // Libera la memoria del ingreso
        }
        paciente->Eliminado = 1;
    }
}



///------------------------- FUNCIONES LABORATORIO -------------------------
IngresoLaboratorio *crearIngreso(int NroIngreso, char *FechaIngreso, char *FechaRetiro, int DniPaciente, int MatriculaProfesional)
{
    IngresoLaboratorio *nuevoIngreso = (IngresoLaboratorio *)malloc(sizeof(IngresoLaboratorio));
    nuevoIngreso->NroIngreso = NroIngreso;
    strcpy(nuevoIngreso->FechaIngreso, FechaIngreso);
    strcpy(nuevoIngreso->FechaRetiro, FechaRetiro);
    nuevoIngreso->DniPaciente = DniPaciente;
    nuevoIngreso->MatriculaProfesional = MatriculaProfesional;
    nuevoIngreso->Eliminado = 0;

    return nuevoIngreso;
}

void agregarIngreso(Paciente *paciente, IngresoLaboratorio *ingreso)
{
    ingreso->siguiente = paciente->ingresos;
    paciente->ingresos = ingreso;
}

// Función para dar de alta un ingreso
void altaIngreso(Paciente *raiz, int dniPaciente, IngresoLaboratorio *nuevoIngreso)
{
    Paciente *pacienteEncontrado = buscarPaciente(raiz, dniPaciente);
    if (pacienteEncontrado != NULL)
    {
        agregarIngreso(pacienteEncontrado, nuevoIngreso);
    }
    else
    {
        printf("El paciente con DNI %d no existe.\n", dniPaciente);
    }
}

// Función para buscar un ingreso
IngresoLaboratorio *buscarIngreso(Paciente *paciente, int nroIngreso)
{
    IngresoLaboratorio *ingreso = paciente->ingresos;
    while (ingreso != NULL)
    {
        if (ingreso->NroIngreso == nroIngreso)
        {
            return ingreso;
        }
        ingreso = ingreso->siguiente;
    }
    return NULL;
}

// Función para modificar un ingreso
void modificarIngreso(Paciente *raiz, int dniPaciente, int nroIngreso, char *nuevaFechaIngreso, char *nuevaFechaRetiro, int nuevaMatricula, int numeroIngreso)
{
    Paciente *paciente = buscarPaciente(raiz, dniPaciente);
    if (paciente != NULL)
    {
        IngresoLaboratorio *ingreso = buscarIngreso(paciente, nroIngreso);
        if (ingreso != NULL)
        {
            strcpy(ingreso->FechaIngreso, nuevaFechaIngreso);
            strcpy(ingreso->FechaRetiro, nuevaFechaRetiro);
            ingreso->MatriculaProfesional = nuevaMatricula;
            ingreso->NroIngreso = numeroIngreso;
        }
        else
        {
            printf("El ingreso con numero %d no existe.\n", nroIngreso);
        }
    }
    else
    {
        printf("El paciente con DNI %d no existe.\n", dniPaciente);
    }
}

// Función para dar de baja un ingreso
void bajaIngreso(Paciente *raiz, int dniPaciente, int nroIngreso)
{
    Paciente *paciente = buscarPaciente(raiz, dniPaciente);
    if (paciente != NULL)
    {
        IngresoLaboratorio *ingreso = buscarIngreso(paciente, nroIngreso);
        if (ingreso != NULL)
        {
            ingreso->Eliminado = 1;
            printf("\nIngreso eliminado...\n");
        }
        else
        {
            printf("El ingreso con numero %d no existe.\n", nroIngreso);
        }
    }
    else
    {
        printf("El paciente con DNI %d no existe.\n", dniPaciente);
    }
}


///------------------------- FUNCIONES PACIENTE MENU -------------------------
void agregarPacienteMenu(Paciente **raiz)
{
    char ApellidoNombre[41];
    int Edad;
    int Dni;
    char Direccion[31];
    char Telefono[16];

    printf("Ingrese el apellido y nombre del paciente: ");
    fflush(stdin);
    gets(&ApellidoNombre);

    printf("Ingrese la edad del paciente: ");
    fflush(stdin);
    scanf("%d", &Edad);

    printf("Ingrese el DNI del paciente: ");
    fflush(stdin);
    scanf("%d", &Dni);

    printf("Ingrese la direccion del paciente: ");
    fflush(stdin);
    gets(&Direccion);

    printf("Ingrese el telefono del paciente: ");
    fflush(stdin);
    gets(&Telefono);

    Paciente *nuevoPaciente = crearPaciente(ApellidoNombre, Edad, Dni, Direccion, Telefono);
    altaPaciente(raiz, nuevoPaciente); // Agrega el paciente al árbol
}

void modificarPacienteMenu(Paciente *raiz)
{
    int dni;
    char nuevoApellidoNombre[41];
    int nuevaEdad;
    char nuevaDireccion[31];
    char nuevoTelefono[16];

    printf("Ingrese el DNI del paciente a modificar: ");
    scanf("%d", &dni);

    Paciente *paciente = buscarPaciente(raiz, dni);
    if (paciente != NULL)
    {
        printf("Ingrese el nuevo apellido y nombre: ");
        fflush(stdin);
        gets(&nuevoApellidoNombre);

        printf("Ingrese la nueva edad: ");
        fflush(stdin);
        scanf("%d", &nuevaEdad);

        printf("Ingrese la nueva direccion: ");
        fflush(stdin);
        gets(&nuevaDireccion);

        printf("Ingrese el nuevo telefono: ");
        fflush(stdin);
        gets(nuevoTelefono);

        modificarPaciente(raiz, dni, nuevoApellidoNombre, nuevaEdad, nuevaDireccion, nuevoTelefono);
        printf("Paciente modificado con éxito.\n");
    }
    else
    {
        printf("El paciente con DNI %d no existe.\n", dni);
    }
}

// Función para eliminar un paciente
void eliminarPaciente(Paciente *raiz, int dni)
{
    Paciente *paciente = buscarPaciente(raiz, dni);
    if (paciente != NULL)
    {
        if (!paciente->Eliminado)
        {
            bajaPaciente(raiz, dni); // Marca el paciente como eliminado
            printf("El paciente ha sido eliminado correctamente.\n");
            guardarDatosEnArchivo(*raiz); // Guarda los cambios en el archivo
        }
        else
        {
            printf("El paciente con DNI %d ya está eliminado.\n", dni);
        }
    }
    else
    {
        printf("El paciente no existe.\n");
    }
}


///------------------------- FUNCIONES LABORATORIO MENU -------------------------
void agregarIngresoMenu(Paciente *raiz)
{
    int dniPaciente;
    int nroIngreso;
    char fechaIngreso[11];
    char fechaRetiro[11];
    int matriculaProfesional;

    printf("Ingrese el DNI del paciente: ");
    scanf("%d", &dniPaciente);

    Paciente *paciente = buscarPaciente(raiz, dniPaciente);
    if (paciente != NULL)
    {
        printf("Ingrese el Numero de ingreso: ");
        fflush(stdin);
        scanf("%d", &nroIngreso);

        printf("Ingrese la fecha de ingreso (YYYY-MM-DD): ");
        fflush(stdin);
        scanf("%s", fechaIngreso);

        printf("Ingrese la fecha de retiro (YYYY-MM-DD): ");
        fflush(stdin);
        scanf("%s", fechaRetiro);

        printf("Ingrese la Matricula profesional: ");
        fflush(stdin);
        scanf("%d", &matriculaProfesional);

        IngresoLaboratorio *nuevoIngreso = crearIngreso(nroIngreso, fechaIngreso, fechaRetiro, dniPaciente, matriculaProfesional);
        altaIngreso(raiz, dniPaciente, nuevoIngreso);
        printf("Ingreso agregado correctamente.\n");
    }
    else
    {
        printf("El paciente con DNI %d no existe.\n", dniPaciente);
    }
}

void modificarIngresoMenu(Paciente *raiz)
{
    int dniPaciente;
    int nroIngreso;
    int nuevoNroIngreso;
    char nuevaFechaIngreso[11];
    char nuevaFechaRetiro[11];
    int nuevaMatriculaProfesional;

    printf("Ingrese el DNI del paciente: ");
    fflush(stdin);
    scanf("%d", &dniPaciente);

    printf("Ingrese el Numero de ingreso: ");
    fflush(stdin);
    scanf("%d", &nroIngreso);

    printf("Ingrese el nuevo Numero de ingreso: ");
    fflush(stdin);
    scanf("%i", &nuevoNroIngreso);

    // Aquí puedes agregar código para obtener los nuevos datos de ingreso
    printf("Ingrese la nueva fecha de ingreso (YYYY-MM-DD): ");
    fflush(stdin);
    scanf("%s", nuevaFechaIngreso);

    printf("Ingrese la nueva fecha de retiro (YYYY-MM-DD): ");
    fflush(stdin);
    scanf("%s", nuevaFechaRetiro);

    printf("Ingrese la nueva Matricula profesional: ");
    fflush(stdin);
    scanf("%d", &nuevaMatriculaProfesional);

    modificarIngreso(raiz, dniPaciente, nroIngreso, nuevaFechaIngreso, nuevaFechaRetiro, nuevaMatriculaProfesional, nuevoNroIngreso);
    // Verificar si se modificó correctamente o no y mostrar un mensaje apropiado
}

void eliminarIngresoMenu(Paciente *raiz)
{
    int dniPaciente, nroIngreso;
    printf("Ingrese el DNI del paciente al que pertenece el ingreso: ");
    scanf("%d", &dniPaciente);

    printf("Ingrese el Numero de ingreso a eliminar: ");
    scanf("%d", &nroIngreso);

    bajaIngreso(raiz, dniPaciente, nroIngreso);
    // Verificar si se eliminó el ingreso correctamente o no y mostrar un mensaje apropiado
}

///------------------------- FUNCIONES TEMP -------------------------
// Función para mostrar la información de un paciente y sus ingresos
void mostrarPacienteYIngresos(Paciente *raiz, int dniPaciente)
{
    Paciente *paciente = buscarPaciente(raiz, dniPaciente);
    if (paciente != NULL && !paciente->Eliminado)
    {
        printf("DNI: %d\n", paciente->Dni);
        printf("Nombre: %s\n", paciente->ApellidoNombre);
        printf("Edad: %d\n", paciente->Edad);
        printf("Direccion: %s\n", paciente->Direccion);
        printf("Telefono: %s\n", paciente->Telefono);

        printf("INGRESO:\n");
        mostrarIngresos(paciente->ingresos);
    }
    else
    {
        printf("El paciente con DNI %d no existe o está eliminado.\n", dniPaciente);
    }
}

// Función para mostrar los ingresos de un paciente
void mostrarIngresos(IngresoLaboratorio *ingresos)
{
    IngresoLaboratorio *actual = ingresos;
    while (actual != NULL)
    {
        if (!actual->Eliminado)
        {
            printf("Numero de Ingreso: %d\n", actual->NroIngreso);
            printf("Fecha de Ingreso: %s\n", actual->FechaIngreso);
            printf("Fecha de Retiro: %s\n", actual->FechaRetiro);
            printf("Matricula Profesional: %d\n\n", actual->MatriculaProfesional);
        }
        actual = actual->siguiente;
    }
}

// Función para mostrar todos los pacientes y sus ingresos
void mostrarTodosLosPacientesYIngresos(Paciente *raiz)
{
    if (raiz != NULL)
    {
        if (!raiz->Eliminado)
        {
            printf("DNI: %d\n", raiz->Dni);
            printf("Nombre: %s\n", raiz->ApellidoNombre);
            printf("Edad: %d\n", raiz->Edad);
            printf("Direccion: %s\n", raiz->Direccion);
            printf("Telefono: %s\n", raiz->Telefono);
            printf("INGRESOS:\n");
            mostrarIngresos(raiz->ingresos);
            printf("\n");
        }
        mostrarTodosLosPacientesYIngresos(raiz->izquierda);
        mostrarTodosLosPacientesYIngresos(raiz->derecha);
    }
}


///FUNCIONES ARCHIVO:
// Función para guardar los datos de pacientes e ingresos en un archivo
void guardarDatosEnArchivo(Paciente *raiz)
{
    FILE *archivo = fopen("datos.txt", "w");
    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo para escritura.\n");
        return;
    }

    guardarPacientesEnArchivo(archivo, raiz);
    fclose(archivo);
}

// Función para guardar los datos de pacientes en un archivo
void guardarPacientesEnArchivo(FILE *archivo, Paciente *raiz)
{
    if (raiz == NULL)
    {
        return;
    }

    if (!raiz->Eliminado)
    {
        fprintf(archivo, "Paciente,%d,%s,%d,%s,%s\n", raiz->Dni, raiz->ApellidoNombre, raiz->Edad, raiz->Direccion, raiz->Telefono);
        guardarIngresosEnArchivo(archivo, raiz->ingresos);
    }

    guardarPacientesEnArchivo(archivo, raiz->izquierda);
    guardarPacientesEnArchivo(archivo, raiz->derecha);
}

// Función para guardar los datos de ingresos en un archivo
void guardarIngresosEnArchivo(FILE *archivo, IngresoLaboratorio *ingresos)
{
    IngresoLaboratorio *actual = ingresos;
    while (actual != NULL)
    {
        if (!actual->Eliminado)
        {
            fprintf(archivo, "Ingreso,%d,%s,%s,%d,%d\n", actual->NroIngreso, actual->FechaIngreso, actual->FechaRetiro, actual->DniPaciente, actual->MatriculaProfesional);
        }
        actual = actual->siguiente;
    }
}

// Función para cargar los datos de pacientes e ingresos desde un archivo
void cargarDatosDesdeArchivo(Paciente **raiz)
{
    FILE *archivo = fopen("datos.txt", "r");
    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo para lectura.\n");
        return;
    }

    char linea[200];
    while (fgets(linea, sizeof(linea), archivo) != NULL)
    {
        char *token = strtok(linea, ",");
        if (token != NULL)
        {
            if (strcmp(token, "Paciente") == 0)
            {
                // Es un paciente
                int dni = atoi(strtok(NULL, ","));
                char *apellidoNombre = strtok(NULL, ",");
                int edad = atoi(strtok(NULL, ","));
                char *direccion = strtok(NULL, ",");
                char *telefono = strtok(NULL, "\n");
                Paciente *nuevoPaciente = crearPaciente(apellidoNombre, edad, dni, direccion, telefono);
                altaPaciente(raiz, nuevoPaciente);
            }
            else if (strcmp(token, "Ingreso") == 0)
            {
                // Es un ingreso
                int nroIngreso = atoi(strtok(NULL, ","));
                char *fechaIngreso = strtok(NULL, ",");
                char *fechaRetiro = strtok(NULL, ",");
                int dniPaciente = atoi(strtok(NULL, ","));
                int matriculaProfesional = atoi(strtok(NULL, "\n"));
                IngresoLaboratorio *nuevoIngreso = crearIngreso(nroIngreso, fechaIngreso, fechaRetiro, dniPaciente, matriculaProfesional);
                altaIngreso(*raiz, dniPaciente, nuevoIngreso);
            }
        }
    }

    fclose(archivo);
}

