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

typedef struct elemento elemento;
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

lista *iniciarLista(){
  lista *l = xmalloc(sizeof(lista));
  l->numE = 0;
  l->prim = NULL;
}

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

void mostrarLista(lista *l){
  elemento *e = l->prim;
  if (l->numE == 0) {
    printf("La lista esta vacia. No tiene elementos\n");
  } else {
    if (l->numE == 1) {
      printf("La lista tiene 1 elemento. Se muestran a continuacion\n",l->numE);
    } else {
      printf("La lista tiene %d elementos. Se muestran a continuacion\n",l->numE);
      while (e!=NULL) {
	printf("Elemento: %s(%d)\n",e->centro,e->tResp);
	e = e->sig;
      }
    }
  }
}

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
  limpiarLista(l);
}
*/
