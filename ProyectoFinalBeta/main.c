#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> // Incluye la biblioteca necesaria para GetConsoleScreenBufferInfo en Windows

// Definici�n de la estructura Practica
typedef struct Practica
{
    int NroPractica;
    char Resultado[256]; // Suponiendo que los resultados de la Practica se puedan almacenar en una cadena
    struct Practica *siguiente; // Apuntador a la siguiente Practica en la lista
} Practica;

// Definici�n de las estructuras
typedef struct IngresoLaboratorio
{
    int NroIngreso;
    char FechaIngreso[11];
    char FechaRetiro[11];
    int DniPaciente;
    int MatriculaProfesional;
    int Eliminado; // 0 para no eliminado, 1 para eliminado
    struct IngresoLaboratorio *siguiente; // Apuntador al siguiente ingreso en la lista
    Practica *practicas; // Apuntador al primer elemento en la lista de practicas
} IngresoLaboratorio;

typedef struct Paciente
{
    char ApellidoNombre[41];
    int Edad;
    int Dni;
    char Direccion[31];
    char Telefono[16];
    int Eliminado; // 0 para no eliminado, 1 para eliminado
    struct Paciente *izquierda, *derecha; // Apuntadores al hijo izquierdo y derecho en el �rbol
    IngresoLaboratorio *ingresos; // Apuntador al primer ingreso en la lista de ingresos
} Paciente;

// Estructura para la lista ordenada
typedef struct NodoLista
{
    Paciente *paciente;
    struct NodoLista *siguiente;
} NodoLista;


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
void buscarPracticasMenu(Paciente *raiz);

///PROTOTIPADOS TEMP:
void mostrarPacienteYIngresos(Paciente *raiz, int dniPaciente);
void mostrarIngresos(IngresoLaboratorio *ingresos);
void mostrarTodosLosPacientesYIngresos(Paciente *raiz);

///PROTOTIPADOS ARCHIVO:
void guardarDatosEnArchivo(Paciente *raiz);
void guardarPacientesEnArchivo(FILE *archivo, Paciente *raiz);
void guardarIngresosEnArchivo(FILE *archivo, IngresoLaboratorio *ingresos);
void cargarDatosDesdeArchivo(Paciente **raiz);

///PROTOTIPADOS PRACTICAS POR INGRESO:
Practica *crearPractica(int NroPractica, char *Resultado);
void altaPractica(IngresoLaboratorio *ingreso, int NroPractica, char *Resultado);
Practica *buscarPractica(IngresoLaboratorio *ingreso, int NroPractica);
void modificacionPractica(IngresoLaboratorio *ingreso, int NroPractica, char *NuevoResultado);
void bajaPractica(IngresoLaboratorio *ingreso, int NroPractica);
void listarPracticasPorPrefijoFor(Practica *practicas, const char *prefijo);
void buscarPracticasConPrefijo(Paciente *raiz, const char *prefijo);

///PROTOTIPADOS PRACTICAS POR INGRESO MENU:
void agregarPracticaMenu(Paciente *raiz);
void modificarPracticaMenu(Paciente *raiz);
void eliminarPracticaMenu(Paciente *raiz);
void buscarPracticasMenu(Paciente *raiz);



int anchoConsola;
int ingresoEncontrado = 0;

// Funci�n para centrar el texto en la consola autom�ticamente
void centrarTextoAuto(const char *texto, int y)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    anchoConsola = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int longitudTexto = strlen(texto);
    int espaciosEnBlanco = (anchoConsola - longitudTexto) / 2;

    // Ajusta la posici�n del cursor en la fila "y" y centra el texto
    COORD posicionCursor;
    posicionCursor.X = espaciosEnBlanco;
    posicionCursor.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), posicionCursor);
    printf("%s", texto);

}


int main()
{
    Paciente *raiz = NULL;
    cargarDatosDesdeArchivoMejorado(&raiz);
    int dniMostrar, dniAEliminar, dniConsulta;
    int opcion;
    char entrada[100];
    int entradaValida;

    char fechaDesde[11];
    char fechaHasta[11];

    do
    {
        system("cls");

        int fila = 5; // Fila donde se centrar� el texto
        centrarTextoAuto("----------------------------------------------", fila++);
        centrarTextoAuto("----------------MENU PRINCIPAL----------------", fila++);
        centrarTextoAuto("----------------------------------------------", fila++);
        centrarTextoAuto("1. Agregar paciente", fila++);
        centrarTextoAuto("2. Modificar paciente", fila++);
        centrarTextoAuto("3. Eliminar paciente", fila++);
        centrarTextoAuto("4. Agregar ingreso", fila++);
        centrarTextoAuto("5. Modificar ingreso", fila++);
        centrarTextoAuto("6. Eliminar ingreso", fila++);
        centrarTextoAuto("7. Mostrar Paciente e Ingreso", fila++);
        centrarTextoAuto("8. Mostrar todos los Pacientes e Ingresos", fila++);
        centrarTextoAuto("9. Filtrar ingresos por fecha", fila++);
        centrarTextoAuto("10. Mostrar un Paciente", fila++);
        centrarTextoAuto("11. Todos los Ingresos por Paciente", fila++);
        centrarTextoAuto("12. Consultar un Ingreso", fila++);
        centrarTextoAuto("13. Agregar practica a un Ingreso", fila++);
        centrarTextoAuto("14. Modificar practica de un Ingreso", fila++);
        centrarTextoAuto("15. Eliminar practica de un Ingreso", fila++);
        centrarTextoAuto("16. Buscar practica que comiencen con...", fila++);
        centrarTextoAuto("17. Salir\n", fila++);

        centrarTextoAuto("Seleccione una opcion: ", fila);

        do
        {
            COORD posicionCursor;
            posicionCursor.X = (anchoConsola - 1) / 2;
            posicionCursor.Y = fila;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), posicionCursor);


            fgets(entrada, sizeof(entrada), stdin);
            entradaValida = sscanf(entrada, "%d", &opcion);

            if (entradaValida != 1 || strcspn(entrada, "\n") != strlen(entrada) - 1)
            {
                entradaValida = 0;
                centrarTextoAuto("Por favor ingrese un numero valido\n", fila);
                centrarTextoAuto("Seleccione una opcion: ", ++fila);
            }
        }
        while (!entradaValida);

        system("cls");

        switch (opcion)
        {
        case 1:
            agregarPacienteMenu(&raiz);
            guardarDatosEnArchivo(&raiz);
            break;
        case 2:
            modificarPacienteMenu(raiz);
            guardarDatosEnArchivo(&raiz);
            break;
        case 3:
            printf("Ingrese el DNI del paciente a eliminar: ");
            scanf("%d", &dniAEliminar);
            eliminarPaciente(raiz, dniAEliminar);
            guardarDatosEnArchivo(&raiz);
            break;
        case 4:
            agregarIngresoMenu(raiz);
            guardarDatosEnArchivo(&raiz);
            break;
        case 5:
            modificarIngresoMenu(raiz);
            guardarDatosEnArchivo(&raiz);
            break;
        case 6:
            eliminarIngresoMenu(raiz);
            guardarDatosEnArchivo(raiz);
            break;
        case 7:
            mostrarPacienteYIngresosConFiltrado(raiz);
            guardarDatosEnArchivo(raiz);
            break;
        case 8:
            mostrarTodosLosPacientesYIngresos(raiz);
            guardarDatosEnArchivo(raiz);
            break;
        case 9:
            printf("Ingrese la fecha de inicio (YYYY-MM-DD): ");
            scanf("%s", fechaDesde);
            printf("Ingrese la fecha de fin (YYYY-MM-DD): ");
            scanf("%s", fechaHasta);
            mostrarIngresosEnRangoYDatosPacienteMenu(raiz, fechaDesde, fechaHasta);
            guardarDatosEnArchivo(raiz);
            break;
        case 10:
            printf("Ingrese el DNI del paciente a consultar: ");
            scanf("%d", &dniConsulta);
            consultarPacientePorDNI(raiz, dniConsulta);
            guardarDatosEnArchivo(raiz);
            break;
        case 11:
            listarIngresosPorPaciente(raiz);
            guardarDatosEnArchivo(raiz);
            break;
        case 12:
            printf("Ingrese el numero de Ingreso (0 para buscar por fecha): ");
            int nroIngreso;
            char fechaIngreso[11];
            scanf("%d", &nroIngreso);
            if (nroIngreso == 0)
            {
                printf("Ingrese la Fecha de Ingreso (YYYY-MM-DD): ");
                scanf("%s", fechaIngreso);
                consultarIngreso(raiz, 0, fechaIngreso);
            }
            else
            {
                consultarIngreso(raiz, nroIngreso, "");
            }
            break;
        case 13:
            agregarPracticaMenu(raiz);
            guardarDatosEnArchivo(&raiz);
            break;
        case 14:
            modificarPracticaMenu(raiz);
            guardarDatosEnArchivo(&raiz);
            break;
        case 15:
            eliminarPracticaMenu(raiz);
            guardarDatosEnArchivo(&raiz);
            break;
        case 16:
            buscarPracticasMenu(raiz);

            break;
        case 17:
            printf("Saliendo del programa...\n");
            guardarDatosEnArchivo(raiz);
            break;
        default:
            centrarTextoAuto("Opcion no valida. Por favor, intente de nuevo.\n", fila);
        }
        system("pause");
    }
    while (opcion != 17);
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

// Funci�n para buscar un paciente
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

// Funcion para buscar un paciente por numero de ingreso
Paciente *buscarPacientePorNumeroIngreso(Paciente *raiz, int numeroIngreso)
{
    if (raiz == NULL)
    {
        return NULL; // No se encontro el paciente
    }

    // Recursivamente, busca en el lado izquierdo y derecho del �rbol
    if (numeroIngreso == raiz->ingresos->NroIngreso)
    {
        return raiz; // Se encontro el paciente con el numero de ingreso
    }
    else if (numeroIngreso > raiz->ingresos->NroIngreso)
    {
        return buscarPacientePorNumeroIngreso(raiz->izquierda, numeroIngreso);
    }
    else
    {
        return buscarPacientePorNumeroIngreso(raiz->derecha, numeroIngreso);
    }
}

// Funci�n para dar de alta un paciente
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

// Funci�n para modificar un paciente
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

// Funci�n para dar de baja un paciente
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

// Funci�n para insertar en lista ordenada
void insertarOrdenado(NodoLista **cabeza, Paciente *paciente)
{
    NodoLista *nuevoNodo = (NodoLista *)malloc(sizeof(NodoLista));
    nuevoNodo->paciente = paciente;
    nuevoNodo->siguiente = NULL;

    // Insertar en la posici�n correcta
    if (*cabeza == NULL || strcmp((*cabeza)->paciente->ApellidoNombre, paciente->ApellidoNombre) > 0)
    {
        nuevoNodo->siguiente = *cabeza;
        *cabeza = nuevoNodo;
    }
    else
    {
        NodoLista *actual = *cabeza;
        while (actual->siguiente != NULL && strcmp(actual->siguiente->paciente->ApellidoNombre, paciente->ApellidoNombre) < 0)
        {
            actual = actual->siguiente;
        }
        nuevoNodo->siguiente = actual->siguiente;
        actual->siguiente = nuevoNodo;
    }
}

// Funci�n para recorrer el �rbol y llenar la lista
void recorrerYOrdenar(Paciente *raiz, NodoLista **listaOrdenada)
{
    if (raiz != NULL)
    {
        recorrerYOrdenar(raiz->izquierda, listaOrdenada);
        if (!raiz->Eliminado)
        {
            insertarOrdenado(listaOrdenada, raiz);
        }
        recorrerYOrdenar(raiz->derecha, listaOrdenada);
    }
}

// Funci�n para mostrar pacientes e ingresos desde una lista
void mostrarPacientesEIngresosOrdenados(NodoLista *lista)
{
    while (lista != NULL)
    {
        mostrarPacienteYIngresos(lista->paciente, lista->paciente->Dni);
        lista = lista->siguiente;
    }
}


///------------------------- FUNCIONES LABORATORIO -------------------------
IngresoLaboratorio *crearIngreso(int NroIngreso, char *FechaIngreso, char *FechaRetiro, int DniPaciente, int MatriculaProfesional)
{
    IngresoLaboratorio *nuevoIngreso = (IngresoLaboratorio *)malloc(sizeof(IngresoLaboratorio));

    if (nuevoIngreso != NULL)
    {
        nuevoIngreso->NroIngreso = NroIngreso;
        strcpy(nuevoIngreso->FechaIngreso, FechaIngreso);
        strcpy(nuevoIngreso->FechaRetiro, FechaRetiro);
        nuevoIngreso->DniPaciente = DniPaciente;
        nuevoIngreso->MatriculaProfesional = MatriculaProfesional;
        nuevoIngreso->Eliminado = 0;
        nuevoIngreso->siguiente = NULL;
        nuevoIngreso->practicas = NULL;
    }
    return nuevoIngreso;
}

void mostrarIngresosPorNumero(IngresoLaboratorio *ingresos, int numeroIngreso)
{
    IngresoLaboratorio *actual = ingresos;
    int encontrados = 0;

    while (actual != NULL)
    {
        if (!actual->Eliminado && actual->NroIngreso == numeroIngreso)
        {
            encontrados++;
            printf("numero de Ingreso: %d\n", actual->NroIngreso);
            printf("Fecha de Ingreso: %s\n", actual->FechaIngreso);
            printf("Fecha de Retiro: %s\n", actual->FechaRetiro);
            printf("Matr�cula Profesional: %d\n\n", actual->MatriculaProfesional);
        }
        actual = actual->siguiente;
    }

    if (encontrados == 0)
    {
        printf("No se encontraron ingresos con el numero especificado.\n");
    }
}

void agregarIngreso(Paciente *paciente, IngresoLaboratorio *ingreso)
{
    ingreso->siguiente = paciente->ingresos;
    paciente->ingresos = ingreso;
}

// Funci�n para dar de alta un ingreso
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

// Funci�n para buscar un ingreso
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

// Funci�n para modificar un ingreso
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

// Funci�n para dar de baja un ingreso
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

// Funci�n auxiliar para realizar la b�squeda
void buscarYVerificacionIngreso(Paciente *raiz, int nroIngreso, const char *fechaIngreso)
{
    if (raiz == NULL || ingresoEncontrado)
    {
        return;
    }

    // B�squeda en el sub�rbol izquierdo
    buscarYVerificacionIngreso(raiz->izquierda, nroIngreso, fechaIngreso);

    if (!raiz->Eliminado)
    {
        IngresoLaboratorio *actual = raiz->ingresos;
        while (actual != NULL)
        {
            if (!actual->Eliminado && (actual->NroIngreso == nroIngreso || (fechaIngreso[0] != '\0' && strcmp(actual->FechaIngreso, fechaIngreso) == 0)))
            {
                printf("\nDetalle del Ingreso:\n");
                printf("Paciente DNI: %d, Nombre: %s\n", raiz->Dni, raiz->ApellidoNombre);
                printf("Numero de Ingreso: %d\n", actual->NroIngreso);
                printf("Fecha de Ingreso: %s\n", actual->FechaIngreso);
                printf("Fecha de Retiro: %s\n", actual->FechaRetiro);


                // Verificar y mostrar resultados de las practicas asociadas al ingreso
                if (actual->practicas != NULL)
                {
                    Practica *practicaActual = actual->practicas;
                    while (practicaActual != NULL)
                    {
                        printf("Practica N: %i, Resultado: %s\n", practicaActual->NroPractica, practicaActual->Resultado);
                        practicaActual = practicaActual->siguiente;
                    }
                }
                ingresoEncontrado = 1; // Marcar como encontrado
                return;
            }
            actual = actual->siguiente;
        }
    }

    // B�squeda en el sub�rbol derecho
    buscarYVerificacionIngreso(raiz->derecha, nroIngreso, fechaIngreso);
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
    altaPaciente(raiz, nuevoPaciente); // Agrega el paciente al �rbol
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
        printf("Paciente modificado con exito.\n");
    }
    else
    {
        printf("El paciente con DNI %d no existe.\n", dni);
    }
}

// Funci�n para eliminar un paciente
void eliminarPaciente(Paciente *raiz, int dni)
{
    Paciente *paciente = buscarPaciente(raiz, dni);
    if (paciente != NULL)
    {
        if (!paciente->Eliminado)
        {
            bajaPaciente(raiz, dni); // Marca el paciente como eliminado
            printf("El paciente ha sido eliminado correctamente.\n");
            guardarDatosEnArchivo(&raiz); // Guarda los cambios en el archivo
        }
        else
        {
            printf("El paciente con DNI %d ya esta eliminado.\n", dni);
        }
    }
    else
    {
        printf("El paciente no existe.\n");
    }
}

// Funci�n para consultar un paciente por DNI
void consultarPacientePorDNI(Paciente *raiz, int dni)
{
    Paciente *pacienteEncontrado = buscarPaciente(raiz, dni);
    if (pacienteEncontrado != NULL && !pacienteEncontrado->Eliminado)
    {
        printf("\nInformacion del Paciente:\n");
        printf("DNI: %d\n", pacienteEncontrado->Dni);
        printf("Nombre: %s\n", pacienteEncontrado->ApellidoNombre);
        printf("Edad: %d\n", pacienteEncontrado->Edad);
        printf("Direccion: %s\n", pacienteEncontrado->Direccion);
        printf("Telefono: %s\n", pacienteEncontrado->Telefono);

        printf("\nIngresos del Paciente:\n");
        mostrarIngresos(pacienteEncontrado->ingresos);
    }
    else
    {
        printf("No se encontro un paciente con DNI %d.\n", dni);
    }
}

// Funci�n para listar ingresos por paciente
void listarIngresosPorPaciente(Paciente *raiz)
{
    if (raiz != NULL)
    {
        // Llamada recursiva al hijo izquierdo
        listarIngresosPorPaciente(raiz->izquierda);

        if (!raiz->Eliminado)
        {
            printf("\nDNI: %d, Nombre: %s\n", raiz->Dni, raiz->ApellidoNombre);
            printf("Ingresos:\n");
            IngresoLaboratorio *actual = raiz->ingresos;
            while (actual != NULL)
            {
                if (!actual->Eliminado)
                {
                    printf("  Numero de Ingreso: %d, Fecha de Ingreso: %s, Fecha de Retiro: %s\n", actual->NroIngreso, actual->FechaIngreso, actual->FechaRetiro);
                }
                actual = actual->siguiente;
            }
            if (raiz->ingresos == NULL)
            {
                printf("  No hay ingresos registrados.\n");
            }
        }

        // Llamada recursiva al hijo derecho
        listarIngresosPorPaciente(raiz->derecha);
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

    // Aqu� puedes agregar c�digo para obtener los nuevos datos de ingreso
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
    // Verificar si se modific� correctamente o no y mostrar un mensaje apropiado
}

void eliminarIngresoMenu(Paciente *raiz)
{
    int dniPaciente, nroIngreso;
    printf("Ingrese el DNI del paciente al que pertenece el ingreso: ");
    scanf("%d", &dniPaciente);

    printf("Ingrese el Numero de ingreso a eliminar: ");
    scanf("%d", &nroIngreso);

    bajaIngreso(raiz, dniPaciente, nroIngreso);
    // Verificar si se elimin� el ingreso correctamente o no y mostrar un mensaje apropiado
}

void mostrarIngresosEnRangoYDatosPacienteMenu(Paciente *raiz, char *fechaDesde, char *fechaHasta)
{
    if (raiz == NULL)
    {
        return;
    }

    if (!raiz->Eliminado)
    {
        IngresoLaboratorio *actual = raiz->ingresos;
        while (actual != NULL)
        {
            if (!actual->Eliminado)
            {
                // Verificar si la fecha de ingreso est� dentro del rango
                if (strcmp(actual->FechaIngreso, fechaDesde) >= 0 && strcmp(actual->FechaIngreso, fechaHasta) <= 0)
                {
                    // Mostrar los datos del paciente e ingreso
                    printf("\nDNI: %d\n", raiz->Dni);
                    printf("Nombre: %s\n", raiz->ApellidoNombre);
                    printf("Edad: %d\n", raiz->Edad);
                    printf("Direccion: %s\n", raiz->Direccion);
                    printf("Telefono: %s\n", raiz->Telefono);
                    printf("Numero de Ingreso: %d\n", actual->NroIngreso);
                    printf("Fecha de Ingreso: %s\n", actual->FechaIngreso);
                    printf("Fecha de Retiro: %s\n", actual->FechaRetiro);
                    printf("Matricula Profesional: %d\n\n", actual->MatriculaProfesional);
                }
            }
            actual = actual->siguiente;
        }
    }

    mostrarIngresosEnRangoYDatosPacienteMenu(raiz->izquierda, fechaDesde, fechaHasta);
    mostrarIngresosEnRangoYDatosPacienteMenu(raiz->derecha, fechaDesde, fechaHasta);
}

// Funci�n principal para consultar un ingreso espec�fico
void consultarIngreso(Paciente *raiz, int nroIngreso, char *fechaIngreso)
{
    ingresoEncontrado = 0; // Reiniciar la bandera
    buscarYVerificacionIngreso(raiz, nroIngreso, fechaIngreso);

    if (!ingresoEncontrado)
    {
        printf("Ingreso no encontrado o datos erroneos.\n");
    }
}

///------------------------- FUNCIONES TEMP -------------------------
// Funci�n para mostrar la informaci�n de un paciente y sus ingresos
void mostrarPacienteYIngresos(Paciente *raiz, int dniPaciente)
{
    Paciente *paciente = buscarPaciente(raiz, dniPaciente);
    if (paciente != NULL && !paciente->Eliminado)
    {
        printf("\nDNI: %d\n", paciente->Dni);
        printf("Nombre: %s\n", paciente->ApellidoNombre);
        printf("Edad: %d\n", paciente->Edad);
        printf("Direccion: %s\n", paciente->Direccion);
        printf("Telefono: %s\n", paciente->Telefono);

        printf("INGRESO:\n");
        mostrarIngresos(paciente->ingresos);
    }
    else
    {
        printf("El paciente con DNI %d no existe o est� eliminado.\n", dniPaciente);
    }
}

// Funci�n para mostrar informaci�n de un paciente y sus ingresos filtrados por numero de ingreso
void mostrarPacienteYIngresosPorNumeroIngreso(Paciente *raiz, int numeroIngreso)
{
    Paciente *paciente = buscarPacientePorNumeroIngreso(raiz, numeroIngreso);
    if (paciente != NULL && !paciente->Eliminado)
    {
        printf("\nDNI: %d\n", paciente->Dni);
        printf("Nombre: %s\n", paciente->ApellidoNombre);
        printf("Edad: %d\n", paciente->Edad);
        printf("Direccion: %s\n", paciente->Direccion);
        printf("Telefono: %s\n", paciente->Telefono);

        printf("INGRESO:\n");
        mostrarIngresosPorNumero(paciente->ingresos, numeroIngreso);
    }
    else
    {
        printf("No se encontro un paciente con ingreso numero %d o est� eliminado.\n", numeroIngreso);
    }
}

// Funci�n para mostrar la informaci�n de un paciente y sus ingresos filtrados por fecha de ingreso
void mostrarPacienteYIngresosPorFecha(Paciente *raiz, char *fechaDesde)
{
    if (raiz == NULL)
    {
        return;
    }

    if (!raiz->Eliminado)
    {
        IngresoLaboratorio *actual = raiz->ingresos;
        while (actual != NULL)
        {
            if (!actual->Eliminado)
            {
                // Verificar si la fecha de ingreso est� dentro del rango
                if (strcmp(actual->FechaIngreso, fechaDesde) == 0)
                {
                    // Mostrar los datos del paciente e ingreso
                    printf("\nDNI: %d\n", raiz->Dni);
                    printf("Nombre: %s\n", raiz->ApellidoNombre);
                    printf("Edad: %d\n", raiz->Edad);
                    printf("Direccion: %s\n", raiz->Direccion);
                    printf("Telefono: %s\n", raiz->Telefono);
                    printf("Numero de Ingreso: %d\n", actual->NroIngreso);
                    printf("Fecha de Ingreso: %s\n", actual->FechaIngreso);
                    printf("Fecha de Retiro: %s\n", actual->FechaRetiro);
                    printf("Matricula Profesional: %d\n\n", actual->MatriculaProfesional);
                }
            }
            actual = actual->siguiente;
        }
    }

    mostrarPacienteYIngresosPorFecha(raiz->izquierda, fechaDesde);
    mostrarPacienteYIngresosPorFecha(raiz->derecha, fechaDesde);
}

// Funci�n para mostrar la informaci�n de un paciente y sus ingresos con opciones de filtrado
void mostrarPacienteYIngresosConFiltrado(Paciente *raiz)
{
    char fechaDesde[11];
    int dniFiltrar;
    int numeroIngreso = 0;

    printf("Seleccione una opcion de filtrado:\n");
    printf("1. Filtrar por DNI\n");
    printf("2. Filtrar por numero de ingreso\n");
    printf("3. Filtrar por fecha de ingreso\n");

    int opcionFiltrado;
    scanf("%d", &opcionFiltrado);

    system("cls");
    switch (opcionFiltrado)
    {
    case 1:
        // Filtrar por DNI
        printf("Ingrese el DNI a filtrar: ");
        scanf("%d", &dniFiltrar);
        system("cls");
        mostrarPacienteYIngresos(raiz, dniFiltrar);
        break;
    case 2:
        // Filtrar por numero de ingreso
        printf("Ingrese el numero de ingreso a filtrar: ");
        scanf("%d", &numeroIngreso);
        system("cls");
        mostrarPacienteYIngresosPorNumeroIngreso(raiz, numeroIngreso);
        break;
    case 3:
        // Filtrar por fecha de ingreso
        printf("Ingrese la fecha de inicio (YYYY-MM-DD): ");
        scanf("%s", &fechaDesde);
        system("cls");
        mostrarPacienteYIngresosPorFecha(raiz,fechaDesde);
        break;
    default:
        printf("Opci�n de filtrado no v�lida.\n");
    }
}

// Funci�n para mostrar los ingresos de un paciente
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

// Funci�n para mostrar todos los pacientes y sus ingresos
void mostrarTodosLosPacientesYIngresos(Paciente *raiz)
{
    NodoLista *listaOrdenada = NULL;
    recorrerYOrdenar(raiz, &listaOrdenada);
    mostrarPacientesEIngresosOrdenados(listaOrdenada);

    // Liberar memoria de la lista
    NodoLista *temp;
    while (listaOrdenada != NULL)
    {
        temp = listaOrdenada;
        listaOrdenada = listaOrdenada->siguiente;
        free(temp);
    }
}

///------------------------- FUNCIONES ARCHIVO -------------------------
// Funci�n para guardar los datos de pacientes e ingresos en un archivo
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

// Funci�n para guardar los datos de pacientes en un archivo
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

// Funci�n para guardar los datos de ingresos en un archivo
void guardarIngresosEnArchivo(FILE *archivo, IngresoLaboratorio *ingresos)
{
    IngresoLaboratorio *actual = ingresos;
    while (actual != NULL)
    {
        if (!actual->Eliminado)
        {
            fprintf(archivo, "Ingreso,%d,%s,%s,%d,%d\n", actual->NroIngreso, actual->FechaIngreso, actual->FechaRetiro, actual->DniPaciente, actual->MatriculaProfesional);

            // Guardar las pr�cticas asociadas a este ingreso
            Practica *practicaActual = actual->practicas;
            while (practicaActual != NULL)
            {
                fprintf(archivo, "Practica,%d,%d,%s\n", actual->NroIngreso, practicaActual->NroPractica, practicaActual->Resultado);
                practicaActual = practicaActual->siguiente;
            }
        }
        actual = actual->siguiente;
    }
}

// Funci�n mejorada para cargar los datos desde un archivo
void cargarDatosDesdeArchivoMejorado(Paciente **raiz)
{
    FILE *archivo = fopen("datos.txt", "r");
    if (archivo == NULL)
    {
        perror("Error al abrir el archivo");
        return;
    }

    char linea[200];
    IngresoLaboratorio *ingresoTemp = NULL; // Variable temporal para almacenar el �ltimo ingreso cargado

    while (fgets(linea, sizeof(linea), archivo) != NULL)
    {
        char *token = strtok(linea, ",");
        if (token == NULL) continue;

        if (strcmp(token, "Paciente") == 0)
        {
            // Procesar paciente
            int dni = atoi(strtok(NULL, ","));
            char *apellidoNombre = strtok(NULL, ",");
            int edad = atoi(strtok(NULL, ","));
            char *direccion = strtok(NULL, ",");
            char *telefono = strtok(NULL, "\n");

            if (apellidoNombre && direccion && telefono)
            {
                Paciente *nuevoPaciente = crearPaciente(apellidoNombre, edad, dni, direccion, telefono);
                altaPaciente(raiz, nuevoPaciente);
                ingresoTemp = NULL; // Restablecer la variable temporal para el nuevo paciente
            }
        }
        else if (strcmp(token, "Ingreso") == 0)
        {
            // Procesar ingreso
            int nroIngreso = atoi(strtok(NULL, ","));
            char *fechaIngreso = strtok(NULL, ",");
            char *fechaRetiro = strtok(NULL, ",");
            int dniPaciente = atoi(strtok(NULL, ","));
            int matriculaProfesional = atoi(strtok(NULL, "\n"));

            Paciente *paciente = buscarPaciente(*raiz, dniPaciente);
            if (paciente != NULL && fechaIngreso && fechaRetiro)
            {
                // Usa el valor real de la matr�cula profesional le�do del archivo
                IngresoLaboratorio *nuevoIngreso = crearIngreso(nroIngreso, fechaIngreso, fechaRetiro, dniPaciente, matriculaProfesional);
                agregarIngreso(paciente, nuevoIngreso);
                ingresoTemp = nuevoIngreso; // Guardar referencia al ingreso reci�n creado
            }
        }
        else if (strcmp(token, "Practica") == 0 && ingresoTemp != NULL)
        {
            // Es una pr�ctica, asociarla al �ltimo ingreso cargado
            int nroIngreso = atoi(strtok(NULL, ","));
            int nroPractica = atoi(strtok(NULL, ","));
            char *resultado = strtok(NULL, "\n");
            if (nroIngreso == ingresoTemp->NroIngreso)
            {
                altaPractica(ingresoTemp, nroPractica, resultado);
            }
        }
    }

    fclose(archivo);
}


///------------------------- FUNCIONES PRACTICA POR INGREGO -------------------------
// Funci�n para crear una nueva Practica
Practica *crearPractica(int NroPractica, char *Resultado)
{
    Practica *nuevaPractica = (Practica *)malloc(sizeof(Practica));
    nuevaPractica->NroPractica = NroPractica;
    strcpy(nuevaPractica->Resultado, Resultado);
    nuevaPractica->siguiente = NULL;
    return nuevaPractica;
}

void altaPractica(IngresoLaboratorio *ingreso, int NroPractica, char *Resultado)
{
    // Crear una nueva Practica
    Practica *nuevaPractica = crearPractica(NroPractica, Resultado);

    // Agregar la nueva Practica a la lista de practicas del ingreso
    nuevaPractica->siguiente = ingreso->practicas;
    ingreso->practicas = nuevaPractica;
}

// Funci�n para buscar una Practica espec�fica por numero
Practica *buscarPractica(IngresoLaboratorio *ingreso, int NroPractica)
{
    Practica *actual = ingreso->practicas;
    while (actual != NULL)
    {
        if (actual->NroPractica == NroPractica)
        {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

void modificacionPractica(IngresoLaboratorio *ingreso, int NroPractica, char *NuevoResultado)
{
    // Buscar la Practica por su numero
    Practica *practica = buscarPractica(ingreso, NroPractica);

    // Si la Practica existe, modificar su nombre (resultado)
    if (practica != NULL)
    {
        strcpy(practica->Resultado, NuevoResultado);
    }
    else
    {
        printf("La Practica con numero %d no existe.\n", NroPractica);
    }
}

void bajaPractica(IngresoLaboratorio *ingreso, int NroPractica)
{
    Practica **indirecto = &(ingreso->practicas);
    while (*indirecto && (*indirecto)->NroPractica != NroPractica)
    {
        indirecto = &((*indirecto)->siguiente);
    }
    if (*indirecto)
    {
        // Encontramos la Practica, ahora verificamos si no ha sido incluida en un ingreso
        if (strcmpi((*indirecto)->Resultado, "") == 0)
        {
            // La Practica no tiene resultados, por lo tanto, se puede eliminar
            Practica *aEliminar = *indirecto;
            *indirecto = aEliminar->siguiente;
            free(aEliminar);
        }
        else
        {
            printf("La Practica con numero %d no se puede eliminar porque ya fue incluida en un ingreso.\n", NroPractica);
        }
    }
    else
    {
        printf("La Practica con numero %d no existe.\n", NroPractica);
    }
}

void listarPracticasPorPrefijoFor(Practica *practicas, const char *prefijo)
{
    for (Practica *p = practicas; p != NULL; p = p->siguiente)
    {
        if (strncmp(p->Resultado, prefijo, strlen(prefijo)) == 0)
        {
            printf("Practica N� %d, Resultado: %s\n", p->NroPractica, p->Resultado);
        }
    }
}

void buscarPracticasConPrefijo(Paciente *raiz, const char *prefijo)
{
    if (raiz == NULL) return;

    // Buscar en sub�rbol izquierdo
    buscarPracticasConPrefijo(raiz->izquierda, prefijo);

    // Listar Practicas del paciente actual que comiencen con el prefijo
    if (!raiz->Eliminado && raiz->ingresos)
    {
        IngresoLaboratorio *ingreso = raiz->ingresos;
        while (ingreso != NULL)
        {
            if (!ingreso->Eliminado)
            {
                listarPracticasPorPrefijoFor(ingreso->practicas, prefijo);
            }
            ingreso = ingreso->siguiente;
        }
    }

    // Buscar en sub�rbol derecho
    buscarPracticasConPrefijo(raiz->derecha, prefijo);
}

///------------------------- FUNCIONES PRACTICA POR INGREGO MENU-------------------------
void agregarPracticaMenu(Paciente *raiz)
{
    int dniPaciente, nroIngreso, nroPractica;
    char resultado[256]; // Asumiendo que el resultado es una cadena de texto

    printf("Ingrese el DNI del paciente: ");
    scanf("%d", &dniPaciente);

    Paciente *paciente = buscarPaciente(raiz, dniPaciente);

    if (paciente != NULL)
    {
        printf("Ingrese el numero de ingreso: ");
        scanf("%d", &nroIngreso);
        IngresoLaboratorio *ingreso = buscarIngreso(paciente, nroIngreso);

        if (ingreso != NULL)
        {
            printf("Ingrese el numero de la Practica: ");
            fflush(stdin);
            scanf("%d", &nroPractica);

            printf("Ingrese el resultado de la Practica: ");
            fflush(stdin);
            gets(&resultado);

            altaPractica(ingreso, nroPractica, resultado);
            printf("Practica agregada correctamente.\n");
        }
        else
        {
            printf("No se encontro el ingreso con el numero %d.\n", nroIngreso);
        }
    }
    else
    {
        printf("No se encontro un paciente con DNI %d.\n", dniPaciente);
    }
}

void modificarPracticaMenu(Paciente *raiz)
{
    int dniPaciente, nroIngreso, nroPractica;
    char nuevoResultado[50]; // Asumiendo que el resultado es una cadena de texto

    printf("Ingrese el DNI del paciente: ");
    scanf("%d", &dniPaciente);


    Paciente *paciente = buscarPaciente(raiz, dniPaciente);

    if (paciente != NULL)
    {
        printf("Ingrese el numero de ingreso: ");
        scanf("%d", &nroIngreso);
        IngresoLaboratorio *ingreso = buscarIngreso(paciente, nroIngreso);

        if (ingreso != NULL)
        {
            printf("Ingrese el numero de la Practica a modificar: ");
            fflush(stdin);
            scanf("%d", &nroPractica);

            printf("Ingrese el nuevo resultado de la Practica: ");
            fflush(stdin);
            gets(&nuevoResultado);


            modificacionPractica(ingreso, nroPractica, nuevoResultado);
            printf("Practica modificada correctamente.\n");
        }
        else
        {
            printf("No se encontro el ingreso con el numero %d.\n", nroIngreso);
        }
    }
    else
    {
        printf("No se encontro un paciente con DNI %d.\n", dniPaciente);
    }
}

void eliminarPracticaMenu(Paciente *raiz)
{
    int dniPaciente, nroIngreso, nroPractica;

    printf("Ingrese el DNI del paciente: ");
    scanf("%d", &dniPaciente);

    Paciente *paciente = buscarPaciente(raiz, dniPaciente);

    if (paciente != NULL)
    {
        printf("Ingrese el numero de ingreso: ");
        scanf("%d", &nroIngreso);
        IngresoLaboratorio *ingreso = buscarIngreso(paciente, nroIngreso);

        if (ingreso != NULL)
        {
            printf("Ingrese el numero de la Practica a eliminar: ");
            scanf("%d", &nroPractica);

            bajaPractica(ingreso, nroPractica);
            printf("Practica eliminada correctamente, si no ten�a resultados asociados.\n");
        }
        else
        {
            printf("No se encontro el ingreso con el numero %d.\n", nroIngreso);
        }
    }
    else
    {
        printf("No se encontro un paciente con DNI %d.\n", dniPaciente);
    }
}

void buscarPracticasMenu(Paciente *raiz)
{
    char prefijo[256];
    printf("Ingrese el prefijo para filtrar las Practicas (por ejemplo 'he'): ");
    scanf("%255s", prefijo);  // Usar %255s para prevenir desbordamiento de b�fer
    buscarPracticasConPrefijo(raiz, prefijo);
}

