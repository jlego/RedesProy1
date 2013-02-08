/**************************************************************
 *                                                
 * Asunto: Codigo fuente de Proyecto 1            
 * Materia: Laboratorio de Redes                  
 * Trimestre: Enero-Marzo 2013                     
 *                                                 
 * Grupo:                                          
 * Integrantes:                  Carnet:           
 * * Maria Isabel  Jilo          (07-41063)        
 * * Jose Gregorio Lezama        (07-41104)        
 *                         
 * Archivo: headers.c
 *   Este archivo se utiliza para todas las definiciones importantes de TODO el
 * proyecto, se encuentran por separado para que cualquier archivo pueda acceder
 * sin mayor problema o importaciones de mas, al manejador de errores realizado
 * para esta entrega.
 *
 *************************************************************/
#ifndef HEADERS_H
#define HEADERS_H
// Includes de librerias basicas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Includes de librerias de Internes
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

// Definicion de los boolean True y False
#define true 1
#define false 0

/*
  Funcion: msjError(int numError)
  Entrada: 
   * Un int numError: Hace referencia al numero de error que ha ocurrido durante
     el uso de la aplicacion
  Salida:
   * Ninguna
  Tarea:
    Comunicar al usuario en que fallo el programa. Ademas de realizar de manera 
    ordenada la salida y concusion de la aplicacion como consecuencia del error
*/
void msjError (int numError) {
  int error = -numError;
  printf("Error - Numero %d:\n",error);

  switch(error) {
  case 1:
    printf("No se pudo realizar la reservacion de informacion solicitada");
    break;
  case 2:
    printf("No ha pasado los parametros completos. Para inicializar el programa");
    break;
  case 3:
    printf("No ha introducido parametros validos para el programa");
    break;
  }

   
  printf("\n\nEl uso del programa es el siguiente:\n"
         "Los argumentos son:\n"
	 "  -n          Nombre del centro o bomba\n"
	 "  -o          Escribe la salida al fichero\n"
	 "  -v          Imprime mas informacion a la salida\n");
  exit(error);
}

/*
  Funcion: xmalloc(size_t size)
  Entrada: 
   * Un size_t llamado size: A pesar de ser size, es un entero, que hace 
    referencia al tamaño en Memoria
  Salida:
   * Apuntador: Si, a pesar de ser void, devuelve un apuntador a la direccion de
    memoria donde comienza la Memoria
  Tarea:
    Se encarga de reservar de manera elegante Memoria del sistema, se dice 
    manera elegante porque se encarga de manejar los posibles errores que 
    pudiera generar malloc sin utilizar una funcion contenedora de malloc
*/
void *xmalloc(size_t size) {
  int listo = false;
  void *tmp;
  while (!listo) {
    tmp = malloc(size);
    if (tmp == NULL) {
      msjError(-1);
    } else {
      listo = true;
    }
  }
  return tmp;
}

#endif
