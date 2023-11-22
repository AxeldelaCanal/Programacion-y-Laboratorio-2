#include "Empleado.h"
#include "Paciente.h"
#include "Menu.h"
#include <windows.h>

int main()
{
    Paciente *raiz = NULL;
    cargarDatosDesdeArchivoMejorado(&raiz);
    int dniMostrar, dniAEliminar, dniConsulta, dniABuscar, opcion, eleccion = 0, fila = 5;
    char entrada[100], fechaDesde[11], fechaHasta[11], usuario[20], contrasenia[20];

    do
    {
        centrarTextoAuto("Bienvenido. Ya estas registrado?\n", fila++);
        centrarTextoAuto("1. Si\n", fila++);
        centrarTextoAuto("2. No\n", fila++);
        centrarTextoAuto("Seleccione una opcion: \n", fila);

        COORD posicionCursor;
        posicionCursor.X = (anchoConsola - 1) / 2;
        posicionCursor.Y = fila;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), posicionCursor);

        fgets(entrada, sizeof(entrada), stdin); // Leer entrada como texto
        int entradaValida = sscanf(entrada, "%d", &eleccion);


        // Validar la entrada
        if (entradaValida != 1 || (eleccion != 1 && eleccion != 2))
        {
            centrarTextoAuto("Error. Vuelva a intentarlo: \n", fila);
            system("pause");
            system("cls");
        }

        if (eleccion == 1)
        {
            opcion1();
        }
        else if (eleccion == 2)
        {
            opcion2();
            printf("Por favor a continuacion ingrese con su usuario. \n");
            system("pause");
            opcion1();
        }
    }
    while(eleccion != 1 && eleccion != 2);
    return 0;
}
