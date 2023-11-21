#include "Menu.h"
#include "Paciente.h"
#include "Empleado.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> // Incluye la biblioteca necesaria para GetConsoleScreenBufferInfo en Windows



// Función para centrar el texto en la consola automáticamente
void centrarTextoAuto(const char *texto, int y)
{
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

void opcion1()
{
    Paciente *raiz = NULL; // Declaración de la raíz del árbol
    cargarDatosDesdeArchivoMejorado(&raiz); // Cargar datos almacenados previamente
    int entradaValida = 1;
    int dniMostrar;
    int dniAEliminar;
    int dniConsulta;
    int dniABuscar;
    int opcion;
    char entrada[100];

    char fechaDesde[11];
    char fechaHasta[11];  // Variables para el rango de fechas

    char usuario[20]; // Variables para ingreso de empleado
    char contrasenia[20];
    int eleccion = 0;
    int fila = 5; // Fila donde se centrará el texto

    system("cls");
    printf("Ingrese usuario: \n");
    fflush(stdin);
    scanf("%s", usuario);

    printf("Ingrese contrasenia: \n");
    fflush(stdin);
    scanf("%s", contrasenia);


    empleados_laboratorio aux = buscarEmpleadoDeArchivo(usuario, contrasenia);

    if (strcmp(aux.perfil, "administrador")==0)
    {

        do
        {
            system("cls");

            int fila = 5; // Fila donde se centrará el texto
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
            centrarTextoAuto("9. Filtrar ingresos por fecha", fila++);  // Nueva opción para filtrar por fecha
            centrarTextoAuto("10. Mostrar un Paciente", fila++); // Nueva opcion para mostrar un paciente.
            centrarTextoAuto("11. Todos los Ingresos por Paciente", fila++);
            centrarTextoAuto("12. Consultar un Ingreso", fila++); // Nueva funcion para mostrar un ingreso.
            centrarTextoAuto("13. Agregar practica a un Ingreso", fila++);
            centrarTextoAuto("14. Modificar practica de un Ingreso", fila++);
            centrarTextoAuto("15. Eliminar practica de un Ingreso", fila++);
            centrarTextoAuto("16. Buscar practica que comiencen con...", fila++);
            centrarTextoAuto("17. Buscar empleado por su DNI", fila++);
            centrarTextoAuto("18. Mostrar todos los empleados", fila++);
            centrarTextoAuto("19. Salir", fila++);

            centrarTextoAuto("Seleccione una opcion: \n", fila);
            do
            {
                // Ajusta la posición del cursor para la entrada del usuario
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
                break;
            case 2:
                modificarPacienteMenu(raiz);
                break;
            case 3:
                printf("Ingrese el DNI del paciente a eliminar: ");
                scanf("%d", &dniAEliminar);
                eliminarPaciente(raiz, dniAEliminar);
                break;
            case 4:
                agregarIngresoMenu(raiz);
                break;
            case 5:
                modificarIngresoMenu(raiz);
                break;
            case 6:
                eliminarIngresoMenu(raiz);
                break;
            case 7:
                mostrarPacienteYIngresosConFiltrado(raiz);
                break;
            case 8:
                mostrarTodosLosPacientesYIngresos(raiz);
                break;
            case 9:
                printf("Ingrese la fecha de inicio (DD-MM-YYYY): ");
                scanf("%s", fechaDesde);
                printf("Ingrese la fecha de fin (DD-MM-YYYY): ");
                scanf("%s", fechaHasta);
                mostrarIngresosEnRangoYDatosPacienteMenu(raiz, fechaDesde, fechaHasta);
                break;
            case 10:
                printf("Ingrese el DNI del paciente a consultar: ");
                scanf("%d", &dniConsulta);
                consultarPacientePorDNI(raiz, dniConsulta);
                break;
            case 11:
                listarIngresosPorPaciente(raiz);
                break;
            case 12:
                printf("Ingrese el numero de Ingreso (0 para buscar por fecha): ");
                int nroIngreso;
                char fechaIngreso[11];
                scanf("%d", &nroIngreso);
                if (nroIngreso == 0)
                {
                    printf("Ingrese la Fecha de Ingreso (DD-MM-YYYY): ");
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
                break;
            case 14:
                modificarPracticaMenu(raiz);
                break;
            case 15:
                eliminarPracticaMenu(raiz);
                break;
            case 16:
                buscarPracticasMenu(raiz);
                break;
            case 17:
                printf("Ingrese DNI del empleado a buscar: ");
                fflush(stdin);
                scanf("%d", &dniABuscar);
                buscarDniSolicitado(dniABuscar);
                break;
            case 18:
                mostrarArchivoDeEmpleados();
                break;
            case 19:
                printf("Saliendo del programa...\n");
                guardarDatosEnArchivo(raiz);
                break;
            default:
                centrarTextoAuto("Opcion no valida. Por favor, intente de nuevo.", fila);
            }
            system("pause");
        }
        while (opcion != 19);

    }
    else if(strcmp(aux.perfil, "administrativo")==0)
    {
        do
        {
            system("cls");

            int fila = 5; // Fila donde se centrará el texto
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
            centrarTextoAuto("9. Filtrar ingresos por fecha", fila++);  // Nueva opción para filtrar por fecha
            centrarTextoAuto("10. Mostrar un Paciente", fila++); // Nueva opcion para mostrar un paciente.
            centrarTextoAuto("11. Todos los Ingresos por Paciente", fila++);
            centrarTextoAuto("12. Consultar un Ingreso", fila++); // Nueva funcion para mostrar un ingreso.
            centrarTextoAuto("13. Buscar practica que comiencen con...", fila++);
            centrarTextoAuto("14. Buscar empleado por su DNI", fila++);
            centrarTextoAuto("15. Mostrar todos los empleados", fila++);
            centrarTextoAuto("16. Salir", fila++);
            centrarTextoAuto("Seleccione una opcion: \n", fila);
            do
            {
                // Ajusta la posición del cursor para la entrada del usuario
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
                break;
            case 2:
                modificarPacienteMenu(raiz);
                break;
            case 3:
                printf("Ingrese el DNI del paciente a eliminar: ");
                scanf("%d", &dniAEliminar);
                eliminarPaciente(raiz, dniAEliminar);
                break;
            case 4:
                agregarIngresoMenu(raiz);
                break;
            case 5:
                modificarIngresoMenu(raiz);
                break;
            case 6:
                eliminarIngresoMenu(raiz);
                break;
            case 7:
                mostrarPacienteYIngresosConFiltrado(raiz);
                break;
            case 8:
                mostrarTodosLosPacientesYIngresos(raiz);
                break;
            case 9:
                printf("Ingrese la fecha de inicio (DD-MM-YYYY): ");
                scanf("%s", fechaDesde);
                printf("Ingrese la fecha de fin (DD-MM-YYYY): ");
                scanf("%s", fechaHasta);
                mostrarIngresosEnRangoYDatosPacienteMenu(raiz, fechaDesde, fechaHasta);
                break;
            case 10:
                printf("Ingrese el DNI del paciente a consultar: ");
                scanf("%d", &dniConsulta);
                consultarPacientePorDNI(raiz, dniConsulta);
                break;
            case 11:
                listarIngresosPorPaciente(raiz);
                break;
            case 12:
                printf("Ingrese el numero de Ingreso (0 para buscar por fecha): ");
                int nroIngreso;
                char fechaIngreso[11];
                scanf("%d", &nroIngreso);
                if (nroIngreso == 0)
                {
                    printf("Ingrese la Fecha de Ingreso (DD-MM-YYYY): ");
                    scanf("%s", fechaIngreso);
                    consultarIngreso(raiz, 0, fechaIngreso);
                }
                else
                {
                    consultarIngreso(raiz, nroIngreso, "");
                }
                break;
            case 13:
                buscarPracticasMenu(raiz);
                break;
            case 14:
                printf("Ingrese DNI del empleado a buscar: ");
                fflush(stdin);
                scanf("%d", &dniABuscar);
                buscarDniSolicitado(dniABuscar);
                break;
            case 15:
                mostrarArchivoDeEmpleadosConAsteriscos();
                break;
            case 16:
                printf("Saliendo del programa...\n");
                guardarDatosEnArchivo(raiz);
                break;
            default:
                centrarTextoAuto("Opcion no valida. Por favor, intente de nuevo.", fila);
            }
            system("pause");
        }
        while (opcion != 16);
    }
    else if(strcmp(aux.perfil, "profesional")==0)
    {
        do
        {
            system("cls");

            int fila = 5; // Fila donde se centrará el texto
            centrarTextoAuto("----------------------------------------------", fila++);
            centrarTextoAuto("----------------MENU PRINCIPAL----------------", fila++);
            centrarTextoAuto("----------------------------------------------", fila++);
            centrarTextoAuto("1. Mostrar Paciente e Ingreso", fila++);
            centrarTextoAuto("2. Mostrar todos los Pacientes e Ingresos", fila++);
            centrarTextoAuto("3. Filtrar ingresos por fecha", fila++);  // Nueva opción para filtrar por fecha
            centrarTextoAuto("4. Mostrar un Paciente", fila++); // Nueva opcion para mostrar un paciente.
            centrarTextoAuto("5. Todos los Ingresos por Paciente", fila++);
            centrarTextoAuto("6. Consultar un Ingreso", fila++); // Nueva funcion para mostrar un ingreso.
            centrarTextoAuto("7. Agregar practica a un Ingreso", fila++);
            centrarTextoAuto("8. Modificar practica de un Ingreso", fila++);
            centrarTextoAuto("9. Eliminar practica de un Ingreso", fila++);
            centrarTextoAuto("10. Buscar practica que comiencen con...", fila++);
            centrarTextoAuto("11. Salir", fila++);
            centrarTextoAuto("Seleccione una opcion: \n", fila);

            do
            {
                // Ajusta la posición del cursor para la entrada del usuario
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
                mostrarPacienteYIngresosConFiltrado(raiz);
                break;
            case 2:
                mostrarTodosLosPacientesYIngresos(raiz);
                break;
            case 3:
                printf("Ingrese la fecha de inicio (DD-MM-YYYY): ");
                scanf("%s", fechaDesde);
                printf("Ingrese la fecha de fin (DD-MM-YYYY): ");
                scanf("%s", fechaHasta);
                mostrarIngresosEnRangoYDatosPacienteMenu(raiz, fechaDesde, fechaHasta);
                break;
            case 4:
                printf("Ingrese el DNI del paciente a consultar: ");
                scanf("%d", &dniConsulta);
                consultarPacientePorDNI(raiz, dniConsulta);
                break;
            case 5:
                listarIngresosPorPaciente(raiz);
                break;
            case 6:
                printf("Ingrese el numero de Ingreso (0 para buscar por fecha): ");
                int nroIngreso;
                char fechaIngreso[11];
                scanf("%d", &nroIngreso);
                if (nroIngreso == 0)
                {
                    printf("Ingrese la Fecha de Ingreso (DD-MM-YYYY): ");
                    scanf("%s", fechaIngreso);
                    consultarIngreso(raiz, 0, fechaIngreso);
                }
                else
                {
                    consultarIngreso(raiz, nroIngreso, "");
                }
                break;
            case 7:
                agregarPracticaMenu(raiz);
                break;
            case 8:
                modificarPracticaMenu(raiz);
                break;
            case 9:
                eliminarPracticaMenu(raiz);
                break;
            case 10:
                buscarPracticasMenu(raiz);
                break;
            case 11:
                printf("Saliendo del programa...\n");
                guardarDatosEnArchivo(raiz);
                break;
            default:
                centrarTextoAuto("Opcion no valida. Por favor, intente de nuevo.", fila);
            }
            system("pause");
        }
        while (opcion != 11);
    }
    else
    {
        printf("Usuario o contrasenia incorrecto.\n");
    }
}

void opcion2()
{
    system("cls");
    empleados_laboratorio nuevoEmpleado = registrarEmpleado();
    guardarEmpleadoEnArchivo(nuevoEmpleado);
}

