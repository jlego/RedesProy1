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
 *   Este archivo se plantea como una herramienta para facilitar el trabajo de
 * de las bombas, ya que se encarga de llevar una lista ordenada de todos los
 * dentros para que la bomba pueda acceder a los de menor tiempo de respuesta
 * de una manera rapida y eficiente
 *
 *************************************************************/

// Includes de librerias basicas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Includes 
#include "headers.c"
#define true 1
#define false 0

/*
  Clase: elemento 

  Componentes:
   * centro: TODA la informacion del centro almacenada en una cadena de
    caracteres(Nombre, Maquina, Puerto)
   * tResp: Un entero, que da el parametro de orden para la lista
    el requisitio es que el entero debe ser mayor que 0, se mantiene esta
    informacion por fuera porque es primordial para el orden
    * sig: Apuntador al proximo centro

  Explicacion:
   Una lista de TODOS los centros a los que puede acceder la bomba. Esta lista 
   esta enlazada solo a derecha (enlace simple). Y al agregar se realiza de 
   manera ordenada para obtener asi la respuesta optima al necesitar un elemento

*/
typedef struct elemento elemento;

/*
  Clase: lista 

  Componentes:
    * numE: Un entero, que indica la cantidad de Elementos que hay en la lista
     para asi no tener que realizar busquedas en caso de que la lista este vacia
     o no llegue hasta algun elemento solicitado

   * primero: Apuntador al centro con el mejor tiempo

  Explicacion:
   Nuestra clase lista es en realidad una cabecera de lista de Elementos, se
   hace de esta manera para que el apuntador sea siempre el mismo. esto le da
   una mayor legibilidad al codigo. ademas de aportar facilidades al no tener
   que devolver el valor de la nueva direccion donde comienza la lista

*/
typedef struct lista lista;

struct elemento{
  char *centro;
  int tResp;
  elemento *sig;
};

struct lista{
  int numE;
  elemento *prim;
};

/*
  Funcion: msjError()
  Entrada: 
   * Ninguna
  Salida:
   * Apuntador a lista, la direccion de memoria donde esta localizado la 
    cabecera de la lista. 
  Tarea:
   Inicializar de buena manera la lista con un manejador de la llamada al 
   sistema de malloc. llamado xmalloc
*/
lista *iniciarLista(){
  lista *l = xmalloc(sizeof(lista));
  l->numE = 0;
  l->prim = NULL;
}

/*
  Funcion: *agregarElemento(lista *l, char info, int tResp)
  Entrada: 
   * Un apuntador a lista l: Que es el apuntador a la cabeza de la lista, a la
    cual se le desea agregar la informacion
   * Una cadena de caracteres info: que es la informacion del centro (servidor)
    con el cual se establecera la conexion, es la informacion que se desea
    guardar 
   * Un entero tResp: que es el tiempo de respuesta del centro, ademas de esto
    se utiliza para agregar de manera ordenada
  Salida:
   * Ninguna
  Tarea:
   Agrega de manera ordenada, de menor a mayor, un nuevo elemento a la lista 
   que se le pasa como parametro. siendo el elemento la composicion de la info
   y el tiempo de respuesta 
*/
void *agregarElemento(lista *l, char *info, int tResp){
  elemento *e = xmalloc(sizeof(elemento));
  e->centro = info;
  e->tResp = tResp;
  e->sig = NULL;
  
  if (l->numE == 0) {
    l->prim = e;
  } else {
    elemento *tmp = l->prim;
    elemento *tmpPapa = NULL;
    int listo = false;
    while ((tmp != NULL) && (listo != true)) {
      if (tmp->tResp > tResp) {
	e->sig = tmp;
	if (tmpPapa == NULL) {
	  l->prim = e;
	}
	listo = true;
      } else {
	tmpPapa = tmp;
	tmp = tmp->sig;
      }
    }
    if (listo != true) {
      tmpPapa->sig=e;
    }
  }
  l->numE = ((l->numE)+1);
}

int tamLista(lista *l) {
  return l->numE;
}
/*
  Funcion: mostrarLista(lista *l)
  Entrada: 
   * Un apuntador a lista *l: Que es la lista de la cual se desea mostrar todos
    los elementos
  Salida:
   * Ninguna
  Tarea:
   Mostrar de manera ordenada todos los elementos de la lista
*/
void mostrarLista(lista *l){
  elemento *e = l->prim;
  if (l->numE == 0) {
    printf("La lista esta vacia. No tiene elementos\n");
  } else {
    if (l->numE == 1) {
      printf("La lista tiene 1 elemento. Se muestran a continuacion\n");
      printf("Elemento: %s(%d)\n",e->centro,e->tResp);
    } else {
      printf("La lista tiene %d elementos. Se muestran a continuacion\n",l->numE);
      while (e!=NULL) {
	printf("Elemento: %s(%d)\n",e->centro,e->tResp);
	e = e->sig;
      }
    }
  }
}

/*
  Funcion: obtenerElemento(lista *l, int pos)
  Entrada: 
   * Un apuntador a lista *l: Que es la lista de la cual se desea mostrar todos
    los elementos
   * Un int pos que es la posicion del elemento que se desea
  Salida:
   * *elemento: El elemento en la posicion pos
  Tarea:
   Mostrar de manera ordenada todos los elementos de la lista
*/
elemento *obtenerElemento(lista *l, int pos){ 
  if (pos >= (l->numE)) {
    msjError(-9);
  } else { 
    elemento *e = l->prim;
    int i = 0;
    while (i < pos) {
      e = e->sig;
      i += 1;
    }
    return e;
  }
}

/*
  Funcion:
  Entrada:
  Salida:
  Tarea:
*/
void mostrarElemento(elemento *e) {
  printf("Elemento:%s:%d\n",e->centro,e->tResp);
}
/*
  Funcion: limpiarLista(lista *l)
  Entrada: 
   * Un apuntador a lista *l: Que es la lista de la cual se debe limpiar de 
    memoria
  Salida:
   * Ninguna
  Tarea:
   Limpiar la memoria, es decir liberar de memoria todas las direcciones 
   ocupada por la lista, es decir, por la cabecera y cada uno de los elementos
*/
void limpiarLista(lista *l) {
  elemento *e = l->prim;
  elemento *ePapa = NULL;
  while (e!=NULL) {
    ePapa = e;
    e = e->sig;
    free(ePapa);
  }
  free(l);
}

/*
int main(int argc, char **argv) {
  lista *l = iniciarLista();
  mostrarLista(l);
  agregarElemento(l,"medio",3);
  mostrarLista(l);
  agregarElemento(l,"chao",6);
  mostrarLista(l);
  agregarElemento(l,"hola",1);
  mostrarLista(l);
  printf("Mostrar todos los elementos\n");
  int i = 0;
  while (i<tamLista(l)) {
    mostrarElemento(obtenerElemento(l,i));
    i += 1;
  }
  limpiarLista(l);
}
*/
//\n
