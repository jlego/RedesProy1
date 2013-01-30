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
 * Archivo: lista.c
 *                             
 *************************************************************/


// Includes de librerias basicas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Includes de librerias de Internet
#include "headers.c"
#define true 1
#define false 0


/*
  Clase: lista 

  Componentes:
   * centro: TODA la informacion del centro almacenada en una cadena de
    caracteres(Nombre, Maquina, Puerto)
   * tiempoRespuesta: Un entero, que da el parametro de orden para la lista
    el requisitio es que el entero debe ser mayor que 0, se mantiene esta
    informacion por fuera porque es primordial para el orden
    * prox: Apuntador al proximo centro

  Explicacion:
   Una lista de TODOS los centros a los que puede acceder la bomba. Esta lista 
   esta enlazada solo a derecha (enlace simple). Y al agregar se realiza de 
   manera ordenada para obtener asi la respuesta optima al necesitar un elemento

*/
typedef struct lista lista;

struct lista{
  char *centro;
  int tiempoRespuesta;
  lista *prox;
};

/*
  Funcion: nombre()
  Entrada: 
   *
  Salida:
   *
  Tarea:
*/

lista *inicializarLista() {
  lista *crear = xmalloc(sizeof(lista));
  crear->centro="";
  crear->tiempoRespuesta=-1;
  crear->prox = NULL;
  return crear;
}


/*
  Funcion: nombre()
  Entrada: 
   *
  Salida:
   *
  Tarea:
*/

lista *agregarLista(lista *centros, char *infoCentro, int tiempoResp) {
  lista *principio = centros;
  lista *tmp = centros->prox;
  lista *papaTmp = centros;
  lista *nuevo = xmalloc(sizeof(lista));
  nuevo->centro = infoCentro;
  nuevo->tiempoRespuesta = tiempoResp;
  nuevo->prox = NULL;
  int listo = false;
  if (tmp == NULL) {
    centros->prox = nuevo;
  } else {
    while ((tmp != NULL) && (listo != true)) {
      printf("Entre");
      if (tmp->tiempoRespuesta > nuevo->tiempoRespuesta) {
	nuevo->prox = tmp;
	papaTmp->prox = nuevo;
	listo = true;
      } else {
	papaTmp= tmp;
	tmp = tmp->prox;
      }
    }
    if (listo != true) {
      papaTmp->prox=nuevo;
    }
  }
  printf("sali");
}

/*
  Funcion: nombre()
  Entrada: 
   *
  Salida:
   *
  Tarea:
*/
void mostrarLista(lista *centros) {
  lista *tmp = centros->prox;
  if (tmp == NULL) {
    printf("No hay elementos en la lista\n");
  } else {
    printf("Los elementos de la lista son los siguientes:\n");
    while (tmp != NULL) {
      printf("Elemento: %s y %d \n",tmp->centro,tmp->tiempoRespuesta);
      tmp = tmp->prox;
    }
  }
}

/*
  Funcion: nombre()
  Entrada: 
   *
  Salida:
   *
  Tarea:
*/
void limpiarLista(lista *centros) {
  lista *tmp = centros;
  lista *borrar;
  while (tmp != NULL) {
    borrar = tmp;
    tmp = tmp->prox;
    free(borrar);
  }
}

int main(int argc,char **argv) {
  lista *nueva = inicializarLista();
  mostrarLista(nueva);
  agregarLista(nueva,"medio",3);
  mostrarLista(nueva);
  agregarLista(nueva,"hola",1);
  mostrarLista(nueva);
  agregarLista(nueva,"chao",6);
  mostrarLista(nueva);
  limpiarLista(nueva);
}
