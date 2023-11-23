#include "Paciente.h"
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

// Funcion para buscar un paciente
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

// Funcion para buscar un paciente por numero de ingreso NUEVA
Paciente *buscarPacientePorNumeroIngreso(Paciente* raiz, int numeroIngreso)
{
    if(raiz == NULL)
    {
        return NULL;
    }

    IngresoLaboratorio* actual = raiz->ingresos;
    while(actual != NULL)
    {
        if(actual->NroIngreso == numeroIngreso)
        {
            return raiz;
        }
        actual = actual->siguiente;
    }

    Paciente* encontradoIzquierda = buscarPacientePorNumeroIngreso(raiz->izquierda, numeroIngreso);
    if(encontradoIzquierda != NULL)
    {
        return encontradoIzquierda;
    }

    Paciente* encontradoDerecha = buscarPacientePorNumeroIngreso(raiz->derecha, numeroIngreso);
    return encontradoDerecha;

}

// Funcion para dar de alta un paciente
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

// Funcion para modificar un paciente
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

// Funcion para dar de baja un paciente
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

// Funcion para insertar en lista ordenada
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

// Funcion para recorrer el arbol y llenar la lista
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

// Funcion para mostrar pacientes e ingresos desde una lista
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
            printf("Numero de Ingreso: %d\n", actual->NroIngreso);
            printf("Fecha de Ingreso: %s\n", actual->FechaIngreso);
            printf("Fecha de Retiro: %s\n", actual->FechaRetiro);
            printf("Matricula Profesional: %d\n\n", actual->MatriculaProfesional);
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

// Funcion para dar de alta un ingreso
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

// Funcion para buscar un ingreso
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

// Funcion para modificar un ingreso
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

// Funcion para dar de baja un ingreso
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

// Funcion auxiliar para realizar la busqueda
int ingresoEncontrado = 0;
void buscarYVerificacionIngreso(Paciente *raiz, int nroIngreso, const char *fechaIngreso)
{
    if (raiz == NULL || ingresoEncontrado)
    {
        return;
    }

    // Busqueda en el subarbol izquierdo
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

    // Busqueda en el subarbol derecho
    buscarYVerificacionIngreso(raiz->derecha, nroIngreso, fechaIngreso);
}

///------------------------- FUNCIONES PACIENTE MENU -------------------------
void agregarPacienteMenu(Paciente **raiz)
{
    char ApellidoNombre[41], Edad[5], Dni[10], Direccion[31], Telefono[16];
    int nombreValido = 0, dniValido = 0, edadValida = 0, telefonoValido = 0;

    // Validar nombre y apellido del paciente
    do
    {
        printf("Ingrese el apellido y nombre del paciente: ");
        fflush(stdin);
        gets(ApellidoNombre);

        nombreValido = verificarApeYNombre(ApellidoNombre);

        if (!nombreValido)
        {
            printf("Nombre y apellido no valido. Intente nuevamente.\n");
        }
    }
    while (!nombreValido);

    // Validar edad del paciente
    do
    {
        printf("Ingrese la edad del paciente: ");
        fflush(stdin);
        scanf("%s", Edad);

        edadValida = 1;
        for(int i = 0; i < strlen(Edad); i++)
        {
            if(!isdigit(Edad[i]))
            {
                edadValida = 0;
                break;
            }
        }

        if(!edadValida || atoi(Edad) <= 0 || atoi(Edad) >= 120)
        {
            printf("Ingrese una edad valida.\n");
            edadValida = 0;
        }
    }
    while (!edadValida);

    // Validar DNI del paciente
    do
    {
        printf("Ingrese el DNI del paciente: ");
        fflush(stdin);
        scanf("%s", Dni);

        dniValido = 1;
        for(int i = 0; i < 8; i++)
        {
            if(!isdigit(Dni[i]))
            {
                dniValido = 0;
                break;
            }
        }

        if(!dniValido)
        {
            printf("Ingrese un DNI valido.\n");
        }
    }
    while (!dniValido);


    printf("Ingrese la direccion del paciente: ");
    fflush(stdin);
    gets(Direccion);

    // Validar Telefono del paciente
    do
    {
        printf("Ingrese el telefono del paciente: ");
        fflush(stdin);
        scanf("%s", Telefono);

        telefonoValido = 1;
        if(strlen(Telefono) != 10)
        {
            telefonoValido = 0;
        }
        else
        {
            for(int i = 0; i < 10; i++)
            {
                if(!isdigit(Telefono[i]))
                {
                    telefonoValido = 0;
                    break;
                }
            }
        }
        if(!telefonoValido)
        {
            printf("Ingrese un numero de telefono valido de 10 digitos.\n");
        }
    }
    while(!telefonoValido);

    Paciente *nuevoPaciente = crearPaciente(ApellidoNombre, atoi(Edad), atoi(Dni), Direccion, Telefono);
    altaPaciente(raiz, nuevoPaciente);
}

void modificarPacienteMenu(Paciente *raiz)
{
    char dni[10], nuevoApellidoNombre[41], nuevaEdad[5], nuevaDireccion[31], nuevoTelefono[16];
    int nombreValido = 0, dniValido = 0, edadValida = 0, telefonoValido = 0;

    // Validar DNI del paciente
    do
    {
        printf("Ingrese el DNI del paciente a modificar: ");
        fflush(stdin);
        scanf("%s", dni);

        dniValido = 1;
        for(int i = 0; i < 8; i++)
        {
            if(!isdigit(dni[i]))
            {
                dniValido = 0;
                break;
            }
        }

        if(!dniValido)
        {
            printf("Ingrese un DNI valido.\n");
        }
    }
    while (!dniValido);

    Paciente *paciente = buscarPaciente(raiz, atoi(dni));
    if (paciente != NULL)
    {
        // Validar nombre y apellido del paciente
        do
        {
            printf("Ingrese el nuevo apellido y nombre: ");
            fflush(stdin);
            gets(nuevoApellidoNombre);

            nombreValido = verificarApeYNombre(nuevoApellidoNombre);

            if (!nombreValido)
            {
                printf("Nombre y apellido no valido. Intente nuevamente.\n");
            }
        }
        while (!nombreValido);

        // Validar edad del paciente
        do
        {
            printf("Ingrese la nueva edad: ");
            fflush(stdin);
            scanf("%s", nuevaEdad);

            edadValida = 1;
            for(int i = 0; i < strlen(nuevaEdad); i++)
            {
                if(!isdigit(nuevaEdad[i]))
                {
                    edadValida = 0;
                    break;
                }
            }

            if(!edadValida || atoi(nuevaEdad) < 0 || atoi(nuevaEdad) > 120)
            {
                printf("Ingrese una edad valida.\n");
                edadValida = 0;
            }
        }
        while (!edadValida);

        printf("Ingrese la nueva direccion: ");
        fflush(stdin);
        gets(nuevaDireccion);

        // Validar número de teléfono del paciente
        do
        {
            printf("Ingrese el nuevo telefono: ");
            fflush(stdin);
            scanf("%s", nuevoTelefono);

            telefonoValido = 1;
            if(strlen(nuevoTelefono) != 10)
            {
                telefonoValido = 0;
            }
            else
            {
                for(int i = 0; i < 10; i++)
                {
                    if(!isdigit(nuevoTelefono[i]))
                    {
                        telefonoValido = 0;
                        break;
                    }
                }
            }

            if(!telefonoValido)
            {
                printf("Ingrese un numero de telefono valido de 10 digitos.\n");
            }
        }
        while (!telefonoValido);

        modificarPaciente(raiz, atoi(dni), nuevoApellidoNombre, atoi(nuevaEdad), nuevaDireccion, nuevoTelefono);
        printf("Paciente modificado con exito.\n");
    }
    else
    {
        printf("El paciente con DNI %s no existe.\n", dni);
    }
}

// Funcion para eliminar un paciente
void eliminarPaciente(Paciente *raiz, int dni)
{
    Paciente *paciente = buscarPaciente(raiz, dni);
    if (paciente != NULL)
    {
        if (!paciente->Eliminado)
        {
            bajaPaciente(raiz, dni); // Marca el paciente como eliminado
            printf("El paciente ha sido eliminado correctamente.\n");
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

// Funcion para consultar un paciente por DNI
void consultarPacientePorDNI(Paciente *raiz, int dni)
{
    Paciente *pacienteEncontrado = buscarPaciente(raiz, dni);
    if (pacienteEncontrado != NULL && !pacienteEncontrado->Eliminado)
    {
        printf("\nInformacion del Paciente:\n");
        printf("==========================================\n");
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

// Funcion para listar ingresos por paciente
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
    char dniPaciente[10], nroIngreso[11], fechaIngreso[11], fechaRetiro[11], matriculaProfesional[11];
    int fechaValida = 0, dniValido = 0, nroIngresoValido = 0, matriculaProfesionalValida = 0;

    // Validar DNI del paciente
    do
    {
        printf("Ingrese el DNI del paciente: ");
        fflush(stdin);
        scanf("%s", dniPaciente);

        dniValido = 1;
        if(strlen(dniPaciente) != 8)
        {
            dniValido = 0;
        }
        else
        {
            for(int i = 0; i < 8; i++)
            {
                if(!isdigit(dniPaciente[i]))
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

    Paciente *paciente = buscarPaciente(raiz, atoi(dniPaciente));
    if (paciente != NULL)
    {
        // Validar número de ingreso
        do
        {
            printf("Ingrese el Numero de ingreso: ");
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

        do
        {
            printf("Ingrese la fecha de ingreso (DD-MM-YYYY): ");
            fflush(stdin);
            scanf("%s", fechaIngreso);

            fechaValida = validarFecha(fechaIngreso);
            if (!fechaValida)
            {
                printf("Fecha invalida. Intente nuevamente.\n");
            }
        }
        while (!fechaValida);

        fechaValida = 0; // Reiniciar el indicador de validez para la siguiente fecha
        do
        {
            printf("Ingrese la fecha de retiro (DD-MM-YYYY): ");
            fflush(stdin);
            scanf("%s", fechaRetiro);

            fechaValida = validarFecha(fechaRetiro);
            if (!fechaValida)
            {
                printf("Fecha invalida. Intente nuevamente.\n");
            }
        }
        while (!fechaValida);

        // Validar matrícula profesional
        do
        {
            printf("Ingrese la Matricula profesional: ");
            fflush(stdin);
            scanf("%s", matriculaProfesional);

            matriculaProfesionalValida = 1;
            for(int i = 0; i < strlen(matriculaProfesional); i++)
            {
                if(!isdigit(matriculaProfesional[i]))
                {
                    matriculaProfesionalValida = 0;
                    break;
                }
            }

            if(!matriculaProfesionalValida)
            {
                printf("Ingrese una matricula profesional valida.\n");
            }
        }
        while (!matriculaProfesionalValida);

        IngresoLaboratorio *nuevoIngreso = crearIngreso(atoi(nroIngreso), fechaIngreso, fechaRetiro, atoi(dniPaciente), atoi(matriculaProfesional));
        altaIngreso(raiz, atoi(dniPaciente), nuevoIngreso);
        printf("Ingreso agregado correctamente.\n");
    }
    else
    {
        printf("El paciente con DNI %s no existe.\n", dniPaciente);
    }
}

void modificarIngresoMenu(Paciente *raiz)
{
    char dniPaciente[10], nroIngreso[11], nuevaFechaIngreso[11], nuevaFechaRetiro[11], nuevaMatriculaProfesional[11];
    int fechaValida = 0, dniValido = 0, nroIngresoValido = 0, matriculaProfesionalValida = 0, nuevoNroIngreso;

    // Validar DNI del paciente
    do
    {
        printf("Ingrese el DNI del paciente: ");
        fflush(stdin);
        scanf("%s", dniPaciente);

        dniValido = 1;
        if(strlen(dniPaciente) != 8)
        {
            dniValido = 0;
        }
        else
        {
            for(int i = 0; i < 8; i++)
            {
                if(!isdigit(dniPaciente[i]))
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

    // Validar número de ingreso
    do
    {
        printf("Ingrese el Numero de ingreso: ");
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

    printf("Ingrese el nuevo Numero de ingreso: ");
    fflush(stdin);
    scanf("%i", &nuevoNroIngreso);

    // Validar fecha de ingreso
    do
    {
        printf("Ingrese la nueva fecha de ingreso (DD-MM-YYYY): ");
        fflush(stdin);
        scanf("%s", nuevaFechaIngreso);

        fechaValida = validarFecha(nuevaFechaIngreso);
        if (!fechaValida)
        {
            printf("Fecha invalida. Intente nuevamente.\n");
        }
    }
    while (!fechaValida);

    fechaValida = 0; // Reiniciar el indicador de validez para la siguiente fecha

    // Validar fecha de retiro
    do
    {
        printf("Ingrese la nueva fecha de retiro (DD-MM-YYYY): ");
        fflush(stdin);
        scanf("%s", nuevaFechaRetiro);

        fechaValida = validarFecha(nuevaFechaRetiro);
        if (!fechaValida)
        {
            printf("Fecha invalida. Intente nuevamente.\n");
        }
    }
    while (!fechaValida);

    // Validar matrícula profesional
    do
    {
        printf("Ingrese la nueva Matricula profesional: ");
        fflush(stdin);
        scanf("%s", nuevaMatriculaProfesional);

        matriculaProfesionalValida = 1;
        for(int i = 0; i < strlen(nuevaMatriculaProfesional); i++)
        {
            if(!isdigit(nuevaMatriculaProfesional[i]))
            {
                matriculaProfesionalValida = 0;
                break;
            }
        }

        if(!matriculaProfesionalValida)
        {
            printf("Ingrese una matricula profesional valida.\n");
        }
    }
    while (!matriculaProfesionalValida);

    modificarIngreso(raiz, atoi(dniPaciente), atoi(nroIngreso), nuevaFechaIngreso, nuevaFechaRetiro, atoi(nuevaMatriculaProfesional), nuevoNroIngreso);
    printf("Ingreso modificado correctamente.\n");
}

void eliminarIngresoMenu(Paciente *raiz)
{
    char dniPaciente[10], nroIngreso[11];
    int dniValido = 0, nroIngresoValido = 0;

    // Validar DNI del paciente
    do
    {
        printf("Ingrese el DNI del paciente al que pertenece el ingreso: ");
        fflush(stdin);
        scanf("%s", dniPaciente);

        dniValido = 1;
        if(strlen(dniPaciente) != 8)
        {
            dniValido = 0;
        }
        else
        {
            for(int i = 0; i < 8; i++)
            {
                if(!isdigit(dniPaciente[i]))
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

    // Validar número de ingreso
    do
    {
        printf("Ingrese el Numero de ingreso a eliminar: ");
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

    bajaIngreso(raiz, atoi(dniPaciente), atoi(nroIngreso));
    printf("Ingreso eliminado correctamente.\n");
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
                // Verificar si la fecha de ingreso esta dentro del rango
                if (strcmp(actual->FechaIngreso, fechaDesde) >= 0 && strcmp(actual->FechaIngreso, fechaHasta) <= 0)
                {
                    // Mostrar los datos del paciente e ingreso
                    printf("\n==========================================\n");
                    printf("DNI: %d\n", raiz->Dni);
                    printf("Nombre: %s\n", raiz->ApellidoNombre);
                    printf("Edad: %d\n", raiz->Edad);
                    printf("Direccion: %s\n", raiz->Direccion);
                    printf("Telefono: %s\n", raiz->Telefono);
                    printf("Numero de Ingreso: %d\n", actual->NroIngreso);
                    printf("Fecha de Ingreso: %s\n", actual->FechaIngreso);
                    printf("Fecha de Retiro: %s\n", actual->FechaRetiro);
                    printf("Matricula Profesional: %d\n", actual->MatriculaProfesional);
                    printf("==========================================\n");
                }
            }
            actual = actual->siguiente;
        }
    }

    mostrarIngresosEnRangoYDatosPacienteMenu(raiz->izquierda, fechaDesde, fechaHasta);
    mostrarIngresosEnRangoYDatosPacienteMenu(raiz->derecha, fechaDesde, fechaHasta);
}

// Funcion principal para consultar un ingreso espec�fico
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
// Funcion para mostrar la informaci�n de un paciente y sus ingresos
void mostrarPacienteYIngresos(Paciente *raiz, int dniPaciente)
{
    Paciente *paciente = buscarPaciente(raiz, dniPaciente);
    if (paciente != NULL && !paciente->Eliminado)
    {
        printf("\n==========================================\n");
        printf("DNI: %d\n", paciente->Dni);
        printf("Nombre: %s\n", paciente->ApellidoNombre);
        printf("Edad: %d\n", paciente->Edad);
        printf("Direccion: %s\n", paciente->Direccion);
        printf("Telefono: %s\n", paciente->Telefono);

        printf("*INGRESO:\n");
        mostrarIngresos(paciente->ingresos);
    }
    else
    {
        printf("El paciente con DNI %d no existe o esta eliminado.\n", dniPaciente);
    }
}

// Funcion para mostrar informaci�n de un paciente y sus ingresos filtrados por numero de ingreso
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
        printf("No se encontro un paciente con ingreso numero %d o esta eliminado.\n", numeroIngreso);
    }
}

// Funcion para mostrar la informaci�n de un paciente y sus ingresos filtrados por fecha de ingreso
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
                // Verificar si la fecha de ingreso esta dentro del rango
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

// Funcion para mostrar la informaci�n de un paciente y sus ingresos con opciones de filtrado
void mostrarPacienteYIngresosConFiltrado(Paciente *raiz)
{
    char fechaDesde[11], dniFiltrar[10], numeroIngreso[11];
    int fechaValida = 0, dniValido = 0, nroIngresoValido = 0;

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
        do
        {
            printf("Ingrese el DNI a filtrar: ");
            fflush(stdin);
            scanf("%s", dniFiltrar);

            dniValido = 1;
            if(strlen(dniFiltrar) != 8)
            {
                dniValido = 0;
            }
            else
            {
                for(int i = 0; i < 8; i++)
                {
                    if(!isdigit(dniFiltrar[i]))
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

        system("cls");
        mostrarPacienteYIngresos(raiz, atoi(dniFiltrar));
        break;
    case 2:
        // Filtrar por numero de ingreso
        do
        {
            printf("Ingrese el numero de ingreso a filtrar: ");
            fflush(stdin);
            scanf("%s", numeroIngreso);

            nroIngresoValido = 1;
            for(int i = 0; i < strlen(numeroIngreso); i++)
            {
                if(!isdigit(numeroIngreso[i]))
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

        system("cls");
        mostrarPacienteYIngresosPorNumeroIngreso(raiz, atoi(numeroIngreso));
        break;
    case 3:
        // Filtrar por fecha de ingreso
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

        system("cls");
        mostrarPacienteYIngresosPorFecha(raiz,fechaDesde);
        break;
    default:
        printf("Opcion de filtrado no valida.\n");
    }
}

// Funcion para mostrar los ingresos de un paciente
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
            printf("Matricula Profesional: %d\n", actual->MatriculaProfesional);
            printf("==========================================\n");
        }
        actual = actual->siguiente;
    }
}

// Funcion para mostrar todos los pacientes y sus ingresos
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
// Funcion para guardar los datos de pacientes e ingresos en un archivo
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

// Funcion para guardar los datos de pacientes en un archivo
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

// Funcion para guardar los datos de ingresos en un archivo
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

// Funcion mejorada para cargar los datos desde un archivo
void cargarDatosDesdeArchivoMejorado(Paciente **raiz)
{
    FILE *archivo = fopen("datos.txt", "r");
    if (archivo == NULL)
    {
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
// Funcion para crear una nueva Practica
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

// Funcion para buscar una Practica espec�fica por numero
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
            printf("Practica N: %d, Resultado: %s\n", p->NroPractica, p->Resultado);
        }
    }
}

void buscarPracticasConPrefijo(Paciente *raiz, const char *prefijo)
{
    if (raiz == NULL) return;

    // Buscar en subarbol izquierdo
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

    // Buscar en subarbol derecho
    buscarPracticasConPrefijo(raiz->derecha, prefijo);
}

///------------------------- FUNCIONES PRACTICA POR INGREGO MENU-------------------------
void agregarPracticaMenu(Paciente *raiz)
{
    char dniPaciente[10], nroIngreso[11], nroPractica[11], resultado[256]; // Asumiendo que el resultado es una cadena de texto
    int dniValido = 0, nroIngresoValido = 0, nroPracticaValido = 0;

    // Validar DNI del paciente
    do
    {
        printf("Ingrese el DNI del paciente: ");
        fflush(stdin);
        scanf("%s", dniPaciente);

        dniValido = 1;
        if(strlen(dniPaciente) != 8)
        {
            dniValido = 0;
        }
        else
        {
            for(int i = 0; i < 8; i++)
            {
                if(!isdigit(dniPaciente[i]))
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

    Paciente *paciente = buscarPaciente(raiz, atoi(dniPaciente));

    if (paciente != NULL)
    {
        // Validar número de ingreso
        do
        {
            printf("Ingrese el numero de ingreso: ");
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

        IngresoLaboratorio *ingreso = buscarIngreso(paciente, atoi(nroIngreso));

        if (ingreso != NULL)
        {
            // Validar número de práctica
            do
            {
                printf("Ingrese el numero de la Practica: ");
                fflush(stdin);
                scanf("%s", nroPractica);

                nroPracticaValido = 1;
                for(int i = 0; i < strlen(nroPractica); i++)
                {
                    if(!isdigit(nroPractica[i]))
                    {
                        nroPracticaValido = 0;
                        break;
                    }
                }

                if(!nroPracticaValido)
                {
                    printf("Ingrese un numero de practica valido.\n");
                }
            }
            while (!nroPracticaValido);

            printf("Ingrese el resultado de la Practica: ");
            fflush(stdin);
            gets(resultado);

            altaPractica(ingreso, atoi(nroPractica), resultado);
            printf("Practica agregada correctamente.\n");
        }
        else
        {
            printf("No se encontro el ingreso con el numero %s.\n", nroIngreso);
        }
    }
    else
    {
        printf("No se encontro un paciente con DNI %s.\n", dniPaciente);
    }
}

void modificarPracticaMenu(Paciente *raiz)
{
    char dniPaciente[10], nroIngreso[11], nroPractica[11], nuevoResultado[50]; // Asumiendo que el resultado es una cadena de texto
    int dniValido = 0, nroIngresoValido = 0, nroPracticaValido = 0;

    do
    {
        printf("Ingrese el DNI del paciente: ");
        fflush(stdin);
        scanf("%s", dniPaciente);

        dniValido = 1;
        if(strlen(dniPaciente) != 8)
        {
            dniValido = 0;
        }
        else
        {
            for(int i = 0; i < 8; i++)
            {
                if(!isdigit(dniPaciente[i]))
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

    Paciente *paciente = buscarPaciente(raiz, atoi(dniPaciente));

    if (paciente != NULL)
    {
        do
        {
            printf("Ingrese el numero de ingreso: ");
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

        IngresoLaboratorio *ingreso = buscarIngreso(paciente, atoi(nroIngreso));

        if (ingreso != NULL)
        {
            // Validar número de práctica
            do
            {
                printf("Ingrese el numero de la Practica a modificar: ");
                fflush(stdin);
                scanf("%s", nroPractica);

                nroPracticaValido = 1;
                for(int i = 0; i < strlen(nroPractica); i++)
                {
                    if(!isdigit(nroPractica[i]))
                    {
                        nroPracticaValido = 0;
                        break;
                    }
                }

                if(!nroPracticaValido)
                {
                    printf("Ingrese un numero de practica valido.\n");
                }
            }
            while (!nroPracticaValido);

            printf("Ingrese el nuevo resultado de la Practica: ");
            fflush(stdin);
            gets(nuevoResultado);

            modificacionPractica(ingreso, atoi(nroPractica), nuevoResultado);
            printf("Practica modificada correctamente.\n");
        }
        else
        {
            printf("No se encontro el ingreso con el numero %s.\n", nroIngreso);
        }
    }
    else
    {
        printf("No se encontro un paciente con DNI %s.\n", dniPaciente);
    }
}

void eliminarPracticaMenu(Paciente *raiz)
{
    char dniPaciente[10], nroIngreso[11], nroPractica[11];
    int dniValido = 0, nroIngresoValido = 0, nroPracticaValido = 0;

    // Validar DNI del paciente
    do
    {
        printf("Ingrese el DNI del paciente: ");
        fflush(stdin);
        scanf("%s", dniPaciente);

        dniValido = 1;
        if(strlen(dniPaciente) != 8)
        {
            dniValido = 0;
        }
        else
        {
            for(int i = 0; i < 8; i++)
            {
                if(!isdigit(dniPaciente[i]))
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

    Paciente *paciente = buscarPaciente(raiz, atoi(dniPaciente));

    if (paciente != NULL)
    {
        // Validar número de ingreso
        do
        {
            printf("Ingrese el numero de ingreso: ");
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

        IngresoLaboratorio *ingreso = buscarIngreso(paciente, atoi(nroIngreso));

        if (ingreso != NULL)
        {
            // Validar número de práctica
            do
            {
                printf("Ingrese el numero de la Practica a eliminar: ");
                fflush(stdin);
                scanf("%s", nroPractica);

                nroPracticaValido = 1;
                for(int i = 0; i < strlen(nroPractica); i++)
                {
                    if(!isdigit(nroPractica[i]))
                    {
                        nroPracticaValido = 0;
                        break;
                    }
                }

                if(!nroPracticaValido)
                {
                    printf("Ingrese un numero de practica valido.\n");
                }
            }
            while (!nroPracticaValido);

            bajaPractica(ingreso, atoi(nroPractica));
            printf("Practica eliminada correctamente, si no tenia resultados asociados.\n");
        }
        else
        {
            printf("No se encontro el ingreso con el numero %s.\n", nroIngreso);
        }
    }
    else
    {
        printf("No se encontro un paciente con DNI %s.\n", dniPaciente);
    }
}

void buscarPracticasMenu(Paciente *raiz)
{
    char prefijo[256];
    printf("Ingrese el prefijo para filtrar las Practicas (por ejemplo 'he'): ");
    scanf("%255s", prefijo);  // Usar %255s para prevenir desbordamiento de bufer
    buscarPracticasConPrefijo(raiz, prefijo);
}

///AUX
int validarFecha(char fecha[])
{
    int fechaValida = 1, exitoConversionFecha = 0, longitudFecha = strlen(fecha), i = 0;

    if (longitudFecha == 0 || longitudFecha < 6 || longitudFecha > 11 || fecha[0] == ' ')
    {
        fechaValida = 0;
    }
    else
    {
        while (i < longitudFecha && fechaValida == 1)
        {
            if ((fecha[i] >= '0' && fecha[i] <= '9') || (fecha[i] == '/') || (fecha[i] == '-'))
            {
                i++;
            }
            else
            {
                fechaValida = 0;
            }
        }
    }

    if (longitudFecha != 0 && fechaValida == 1)
    {
        exitoConversionFecha = convertirFecha(fecha);

        if (exitoConversionFecha == 1)
        {
            fechaValida = 1;
        }
        else
        {
            fechaValida = 0;
        }
    }

    return fechaValida;
}

int convertirFecha(char fecha[])
{
    int fechaValida = 0, dia = 0, mes = 0, year = 0;

    if (sscanf(fecha, "%d/%d/%d", &dia, &mes, &year) == 3 || sscanf(fecha, "%d-%d-%d", &dia, &mes, &year) == 3)
    {
        if ((dia >= 1 && dia <= 31) && (mes >= 1 && mes <= 12) && ((year >= 2023 && year <= 2033) || (year >= 23 && year <= 33)))
        {
            fechaValida = 1;
        }
    }

    return fechaValida;
}
