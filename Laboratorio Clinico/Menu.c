#include "Menu.h"
#include "Paciente.h"
#include "Empleado.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> // Incluye la biblioteca necesaria para GetConsoleScreenBufferInfo en Windows


// Funcion para centrar el texto en la consola autom�ticamente
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

void opcion1()
{
    Paciente *raiz = NULL; // Declaraci�n de la raiz del arbol
    cargarDatosDesdeArchivoMejorado(&raiz); // Cargar datos almacenados previamente
    int entradaValida = 1, dniMostrar, dniAEliminar, dniConsulta, dniABuscar, opcion, fechaValida = 0, dniValido = 0, nroIngresoValido = 0, eleccion = 0, fila = 5;
    char dniConsultas[10], entrada[100], nroIngreso[11], fechaIngreso[11], dniABuscarArrglo[10], fechaDesde[11], fechaHasta[11], usuario[20], contrasenia[20] ;

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
            centrarTextoAuto("9. Filtrar ingresos por fecha", fila++);  // Nueva Opcion para filtrar por fecha
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
                // Ajusta la posici�n del cursor para la entrada del usuario
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
                agregarPacienteMenu(&raiz); ///Validado
                break;
            case 2:
                modificarPacienteMenu(raiz); ///Validado
                break;
            case 3:
                printf("Ingrese el DNI del paciente a eliminar: ");
                scanf("%d", &dniAEliminar);
                eliminarPaciente(raiz, dniAEliminar); ///Validado, no modificada
                break;
            case 4:
                agregarIngresoMenu(raiz); ///Validado
                break;
            case 5:
                modificarIngresoMenu(raiz); ///Validado
                break;
            case 6:
                eliminarIngresoMenu(raiz); ///Validado
                break;
            case 7:
                mostrarPacienteYIngresosConFiltrado(raiz); ///Validado
                break;
            case 8:
                mostrarTodosLosPacientesYIngresos(raiz); ///No necesita validacion
                break;
            case 9:///Validado
                do
                {
                    printf("Ingrese la fecha de inicio (DD-MM-YYYY): ");
                    fflush(stdin);
                    scanf("%s", fechaDesde);

                    fechaValida = validarFecha(fechaDesde);
                    if (!fechaValida)
                    {
                        printf("Fecha invalida. Intente nuevamente.\n");
                    }
                }
                while (!fechaValida);
                do
                {
                    printf("Ingrese la fecha de fin (DD-MM-YYYY): ");
                    fflush(stdin);
                    scanf("%s", fechaHasta);

                    fechaValida = validarFecha(fechaHasta);
                    if (!fechaValida)
                    {
                        printf("Fecha invalida. Intente nuevamente.\n");
                    }
                }
                while (!fechaValida);
                mostrarIngresosEnRangoYDatosPacienteMenu(raiz, fechaDesde, fechaHasta);
                break;
            case 10: ///Validado
                do
                {
                    printf("Ingrese el DNI del paciente a consultar: ");
                    fflush(stdin);
                    scanf("%s", dniConsultas);

                    dniValido = 1;
                    if(strlen(dniConsultas) != 8)
                    {
                        dniValido = 0;
                    }
                    else
                    {
                        for(int i = 0; i < 8; i++)
                        {
                            if(!isdigit(dniConsultas[i]))
                            {
                                dniValido = 0;
                                break;
                            }
                        }
                    }
                    if(!dniValido)
                    {
                        printf("Ingrese un DNI valido de 8 digitos.\n");
                    }
                }
                while (!dniValido);
                consultarPacientePorDNI(raiz, atoi(dniConsultas));
                break;
            case 11: ///No necesita validacion
                listarIngresosPorPaciente(raiz);
                break;
            case 12: ///Validado
                do
                {
                    printf("Ingrese el numero de Ingreso (0 para buscar por fecha): ");
                    fflush(stdin);
                    scanf("%s", nroIngreso);
                    nroIngresoValido = 1;
                    for(int i = 0; i < strlen(nroIngreso); i++)
                    {
                        if(!isdigit(nroIngreso[i]))
                        {
                            nroIngresoValido = 0;
                            break;
                        }
                    }
                    if(!nroIngresoValido)
                    {
                        printf("Ingrese un numero de ingreso valido.\n");
                    }
                }
                while (!nroIngresoValido);
                if (atoi(nroIngreso) == 0)
                {
                    do
                    {
                        printf("Ingrese la Fecha de Ingreso (DD-MM-YYYY): ");
                        fflush(stdin);
                        scanf("%s", fechaIngreso);

                        fechaValida = validarFecha(fechaIngreso);
                        if (!fechaValida)
                        {
                            printf("Fecha invalida. Intente nuevamente.\n");
                        }
                    }
                    while (!fechaValida);
                    consultarIngreso(raiz, 0, fechaIngreso);
                }
                else
                {
                    consultarIngreso(raiz, atoi(nroIngreso), "");
                }
                break;
            case 13:
                agregarPracticaMenu(raiz); ///Validada
                break;
            case 14:
                modificarPracticaMenu(raiz); ///Validada
                break;
            case 15:
                eliminarPracticaMenu(raiz); ///Validada
                break;
            case 16:
                buscarPracticasMenu(raiz); ///No necesita validacion
                break;
            case 17: ///Validada
                do
                {
                    printf("Ingrese DNI del empleado a buscar: ");
                    fflush(stdin);
                    scanf("%s", dniABuscarArrglo);

                    dniValido = 1;
                    if(strlen(dniABuscarArrglo) != 8)
                    {
                        dniValido = 0;
                    }
                    else
                    {
                        for(int i = 0; i < 8; i++)
                        {
                            if(!isdigit(dniABuscarArrglo[i]))
                            {
                                dniValido = 0;
                                break;
                            }
                        }
                    }

                    if(!dniValido)
                    {
                        printf("Ingrese un DNI valido de 8 digitos.\n");
                    }
                }
                while (!dniValido);
                buscarDniSolicitado(atoi(dniABuscarArrglo));
                break;
            case 18:
                mostrarArchivoDeEmpleados(); ///No necesita validacion
                break;
            case 19:
                printf("Saliendo del programa...\n");
                guardarDatosEnArchivo(raiz); ///No necesita validacion
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

            int fila = 5; // Fila donde se centrara el texto
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
            centrarTextoAuto("9. Filtrar ingresos por fecha", fila++);  // Nueva opcion para filtrar por fecha
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
                // Ajusta la posicion del cursor para la entrada del usuario
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
                agregarPacienteMenu(&raiz); ///Validada
                break;
            case 2:
                modificarPacienteMenu(raiz); ///Validada
                break;
            case 3:
                printf("Ingrese el DNI del paciente a eliminar: "); ///No necesita validacion
                scanf("%d", &dniAEliminar);
                eliminarPaciente(raiz, dniAEliminar);
                break;
            case 4:
                agregarIngresoMenu(raiz); ///Validada
                break;
            case 5:
                modificarIngresoMenu(raiz); ///Validada
                break;
            case 6:
                eliminarIngresoMenu(raiz); ///Validada
                break;
            case 7:
                mostrarPacienteYIngresosConFiltrado(raiz); ///Validada
                break;
            case 8:
                mostrarTodosLosPacientesYIngresos(raiz); ///No necesita validacion
                break;
            case 9: ///Validada
                do
                {
                    printf("Ingrese la fecha de inicio (DD-MM-YYYY): ");
                    fflush(stdin);
                    scanf("%s", fechaDesde);

                    fechaValida = validarFecha(fechaDesde);
                    if (!fechaValida)
                    {
                        printf("Fecha invalida. Intente nuevamente.\n");
                    }
                }
                while (!fechaValida);
                do
                {
                    printf("Ingrese la fecha de fin (DD-MM-YYYY): ");
                    fflush(stdin);
                    scanf("%s", fechaHasta);

                    fechaValida = validarFecha(fechaHasta);
                    if (!fechaValida)
                    {
                        printf("Fecha invalida. Intente nuevamente.\n");
                    }
                }
                while (!fechaValida);
                mostrarIngresosEnRangoYDatosPacienteMenu(raiz, fechaDesde, fechaHasta);
                break;
            case 10:
                do
                {
                    printf("Ingrese el DNI del paciente a consultar: ");
                    fflush(stdin);
                    scanf("%s", dniConsultas);

                    dniValido = 1;
                    if(strlen(dniConsultas) != 8)
                    {
                        dniValido = 0;
                    }
                    else
                    {
                        for(int i = 0; i < 8; i++)
                        {
                            if(!isdigit(dniConsultas[i]))
                            {
                                dniValido = 0;
                                break;
                            }
                        }
                    }
                    if(!dniValido)
                    {
                        printf("Ingrese un DNI valido de 8 digitos.\n");
                    }
                }
                while (!dniValido);
                consultarPacientePorDNI(raiz, atoi(dniConsultas));
                break;
            case 11:
                listarIngresosPorPaciente(raiz); ///No necesita validacion
                break;
            case 12:
                do
                {
                    printf("Ingrese el numero de Ingreso (0 para buscar por fecha): ");
                    fflush(stdin);
                    scanf("%s", nroIngreso);
                    nroIngresoValido = 1;
                    for(int i = 0; i < strlen(nroIngreso); i++)
                    {
                        if(!isdigit(nroIngreso[i]))
                        {
                            nroIngresoValido = 0;
                            break;
                        }
                    }
                    if(!nroIngresoValido)
                    {
                        printf("Ingrese un numero de ingreso valido.\n");
                    }
                }
                while (!nroIngresoValido);
                if (atoi(nroIngreso) == 0)
                {
                    do
                    {
                        printf("Ingrese la Fecha de Ingreso (DD-MM-YYYY): ");
                        fflush(stdin);
                        scanf("%s", fechaIngreso);

                        fechaValida = validarFecha(fechaIngreso);
                        if (!fechaValida)
                        {
                            printf("Fecha invalida. Intente nuevamente.\n");
                        }
                    }
                    while (!fechaValida);
                    consultarIngreso(raiz, 0, fechaIngreso);
                }
                else
                {
                    consultarIngreso(raiz, atoi(nroIngreso), "");
                }
                break;
            case 13:
                buscarPracticasMenu(raiz); ///No necesita validacion
                break;
            case 14: ///Validada
                do
                {
                    printf("Ingrese DNI del empleado a buscar: ");
                    fflush(stdin);
                    scanf("%s", dniABuscarArrglo);

                    dniValido = 1;
                    if(strlen(dniABuscarArrglo) != 8)
                    {
                        dniValido = 0;
                    }
                    else
                    {
                        for(int i = 0; i < 8; i++)
                        {
                            if(!isdigit(dniABuscarArrglo[i]))
                            {
                                dniValido = 0;
                                break;
                            }
                        }
                    }

                    if(!dniValido)
                    {
                        printf("Ingrese un DNI valido de 8 digitos.\n");
                    }
                }
                while (!dniValido);
                buscarDniSolicitado(atoi(dniABuscarArrglo));
                break;
            case 15:
                mostrarArchivoDeEmpleadosConAsteriscos(); ///No necesita validacion
                break;
            case 16:
                printf("Saliendo del programa...\n");
                guardarDatosEnArchivo(raiz); ///No necesita validacion
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

            int fila = 5; // Fila donde se centrara el texto
            centrarTextoAuto("----------------------------------------------", fila++);
            centrarTextoAuto("----------------MENU PRINCIPAL----------------", fila++);
            centrarTextoAuto("----------------------------------------------", fila++);
            centrarTextoAuto("1. Mostrar Paciente e Ingreso", fila++);
            centrarTextoAuto("2. Mostrar todos los Pacientes e Ingresos", fila++);
            centrarTextoAuto("3. Filtrar ingresos por fecha", fila++);  // Nueva opcion para filtrar por fecha
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
                // Ajusta la posicion del cursor para la entrada del usuario
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
                mostrarPacienteYIngresosConFiltrado(raiz); ///Validada
                break;
            case 2:
                mostrarTodosLosPacientesYIngresos(raiz); ///No necesita validacion
                break;
            case 3: ///Validada
                do
                {
                    printf("Ingrese la fecha de inicio (DD-MM-YYYY): ");
                    fflush(stdin);
                    scanf("%s", fechaDesde);

                    fechaValida = validarFecha(fechaDesde);
                    if (!fechaValida)
                    {
                        printf("Fecha invalida. Intente nuevamente.\n");
                    }
                }
                while (!fechaValida);
                do
                {
                    printf("Ingrese la fecha de fin (DD-MM-YYYY): ");
                    fflush(stdin);
                    scanf("%s", fechaHasta);

                    fechaValida = validarFecha(fechaHasta);
                    if (!fechaValida)
                    {
                        printf("Fecha invalida. Intente nuevamente.\n");
                    }
                }
                while (!fechaValida);
                mostrarIngresosEnRangoYDatosPacienteMenu(raiz, fechaDesde, fechaHasta);
                break;
            case 4: ///Validada
                do
                {
                    printf("Ingrese el DNI del paciente a consultar: ");
                    fflush(stdin);
                    scanf("%s", dniConsultas);

                    dniValido = 1;
                    if(strlen(dniConsultas) != 8)
                    {
                        dniValido = 0;
                    }
                    else
                    {
                        for(int i = 0; i < 8; i++)
                        {
                            if(!isdigit(dniConsultas[i]))
                            {
                                dniValido = 0;
                                break;
                            }
                        }
                    }
                    if(!dniValido)
                    {
                        printf("Ingrese un DNI valido de 8 digitos.\n");
                    }
                }
                while (!dniValido);
                consultarPacientePorDNI(raiz, atoi(dniConsultas));
                break;
            case 5:
                listarIngresosPorPaciente(raiz); ///No necesita validacion
                break;
            case 6: ///Validada
                do
                {
                    printf("Ingrese el numero de Ingreso (0 para buscar por fecha): ");
                    fflush(stdin);
                    scanf("%s", nroIngreso);
                    nroIngresoValido = 1;
                    for(int i = 0; i < strlen(nroIngreso); i++)
                    {
                        if(!isdigit(nroIngreso[i]))
                        {
                            nroIngresoValido = 0;
                            break;
                        }
                    }
                    if(!nroIngresoValido)
                    {
                        printf("Ingrese un numero de ingreso valido.\n");
                    }
                }
                while (!nroIngresoValido);
                if (atoi(nroIngreso) == 0)
                {
                    do
                    {
                        printf("Ingrese la Fecha de Ingreso (DD-MM-YYYY): ");
                        fflush(stdin);
                        scanf("%s", fechaIngreso);

                        fechaValida = validarFecha(fechaIngreso);
                        if (!fechaValida)
                        {
                            printf("Fecha invalida. Intente nuevamente.\n");
                        }
                    }
                    while (!fechaValida);
                    consultarIngreso(raiz, 0, fechaIngreso);
                }
                else
                {
                    consultarIngreso(raiz, atoi(nroIngreso), "");
                }
                break;
            case 7:
                agregarPracticaMenu(raiz); ///Validada
                break;
            case 8:
                modificarPracticaMenu(raiz); ///Validada
                break;
            case 9:
                eliminarPracticaMenu(raiz); ///Validada
                break;
            case 10:
                buscarPracticasMenu(raiz); ///No necesita validacion
                break;
            case 11:
                printf("Saliendo del programa...\n");
                guardarDatosEnArchivo(raiz); ///No necesita validacion
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
