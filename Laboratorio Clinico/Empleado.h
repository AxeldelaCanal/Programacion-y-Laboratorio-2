#ifndef EMPLEADO_H_INCLUDED
#define EMPLEADO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

//Estructura para menu de empleados
typedef struct empleados_laboratorio
{
    int dni;
    char apellidoYnombre[40];
    char usuario[20];
    char contrasenia[20];
    char perfil[20];
} empleados_laboratorio;


///PROTOTIPADO MENU EMPLEADOS
empleados_laboratorio registrarEmpleado();
int comprobarDNIRepetido(int dni);
int comprobarUsuarioRepetido(char usuario[]);
void guardarEmpleadoEnArchivo(empleados_laboratorio empleado);
void mostrarArchivoDeEmpleados();
void mostrarArchivoDeEmpleadosConAsteriscos();
empleados_laboratorio buscarEmpleadoDeArchivo(char usuario[], char contrasenia[]);
void buscarDniSolicitado(int dniABuscar);


#endif // EMPLEADO_H_INCLUDED
