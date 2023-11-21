#ifndef PACIENTE_H_INCLUDED
#define PACIENTE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de la estructura Practica
typedef struct Practica
{
    int NroPractica;
    char Resultado[256]; // Suponiendo que los resultados de la Practica se puedan almacenar en una cadena
    struct Practica *siguiente; // Apuntador a la siguiente Practica en la lista
} Practica;

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
    struct Paciente *izquierda, *derecha; // Apuntadores al hijo izquierdo y derecho en el árbol
    IngresoLaboratorio *ingresos; // Apuntador al primer ingreso en la lista de ingresos
} Paciente;


// Estructura para la lista ordenada
typedef struct NodoLista
{
    Paciente *paciente;
    struct NodoLista *siguiente;
} NodoLista;


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


#endif // PACIENTE_H_INCLUDED
