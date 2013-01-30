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
 * Archivo: funciones.c
 *   Este archivo contiene TODAS las funciones que son requeridas tanto por 
 * bomba.c como por centro.c. La idea es no duplicar lineas de codigo, sino 
 * tener un archivo central que le pase a los mismos las funciones comunes
 *          
 *************************************************************/

// Includes de librerias basicas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include de librerias propias
#include "headers.c"

/*
  Funcion: verOp(Verificacion de Operaciones)
  Entrada: 
   * Entero Obj: Objetivo, de cuantos elementos debe recibir como parametro la
    funcion, la idea es que ctdd sea equivalente, sino hubo error en la llamada
   * Entero ctdd: Cantidad, cuantos elementos fueron recibidos con la llamada de
    la funcion.
   * Arreglo de Arreglos de Caracteres argv: Arguments Value, lleva el nombre
    de los valores por defecto en c, para denotar que es el mismo elemento. La
    idea es verificar todos los parametros que aqui se encuentran

  Salida:
   * Apuntador a Entero: Un arreglo que devuelve las posiciones de los 
    parametros de entrada

  Tarea:
    Esta funcion se encarga de procesar todos los argumentos de la llamada a la 
    funcion para poder verificar que los mismos cumplen las condiciones 
    necesarias para poder seguir ejecuntado el programa. Ademas de esto,
    devuelve u arreglo de enteros, en el cual se encuentran las posiciones
    de los parametross de manera ordenada y basica para poder utilizar cualquier
    el programa sin importar el factor de los operandos.
*/
int *verOp(int obj, int ctdd, char **argv) {
  int i = 1;
  char tmp[64];
  char nom[64] = "";
  int posNom = -1;
  int cap = -1;
  int posCap = -1;
  int inv = -1;
  int posInv = -1;
  int con = -1;
  int posCon = -1;
  int tie = -1;
  int posTie = -1;
  int sum = -1;
  int posSum = -1;
  int pue = -1;
  int posPue = -1;
  FILE *archivo = NULL;
  int posArchivo = -1;

  if (obj == ctdd) {
    for (i = 1; i < ctdd-1; i += 2) {
      strcpy(tmp,argv[i]);   
      if (strcmp("-n",tmp) == 0) {
	if ((i+1) < (ctdd)) {
	  strcpy(nom,argv[i+1]);
	  posNom = i +1;
	}
      } else if (strcmp("-cp",tmp) == 0) {
	if ((i+1) < (ctdd)) {
	  cap = atoi(argv[i+1]);
	  if (obj == 11) {
	    if ((cap < 0) || (cap > 380000)) {
	      cap = -2;
	    } else {
	      posCap = i+1;
	    }
	  } else {
	    if ((cap <38000) || (cap > 3800000)) {
	      cap = -2;
	    } else {
	      posCap = i+1;
	    }
	  }
	}
      } else if (strcmp("-i",tmp) == 0) {
	if ((i+1) < (ctdd)) {
	  inv = atoi(argv[i+1]);
	  if (inv < 0) {
	    inv = -2;
	  } else {
	    posInv = i+1;
	  }
	}
      } else if (strcmp("-c",tmp) == 0) {
	if ((i+1) < (ctdd)) {
	  con = atoi(argv[i+1]);
	  if ((con < 0) || (con > 1000)) {
	    con = -2;
	  } else {
	    posCon = i+1;
	  }
	}
      } else if (strcmp("-fc",tmp) == 0) {
	if ((i+1) < (ctdd)) {
	  archivo = fopen(tmp,"r");
	  posArchivo = i+1;
	}
      } else if (strcmp("-t",tmp) == 0) {
	if ((i+1) < (ctdd)) {
	  tie = atoi(argv[i+1]);
	  if ((tie < 0) || (tie > 180))  {
	    tie = -2;
	  } else {
	    posTie = i+1;
	  }
	}
      } else if (strcmp("-s",tmp) == 0) {
	if ((i+1) < (ctdd)) {
	  sum = atoi(argv[i+1]);
	  if ((sum < 0) || (sum > 10000)) {
	    sum = -2;
	  } else {
	    posSum=i+1;
	  }
	}
      } else if (strcmp("-p",tmp) == 0) {
	if ((i+1) < (ctdd)) {
	  pue = atoi(argv[i+1]);
	  if ((pue != 41104) && (pue != 41063)) {
	    pue = -2;
	  } else {
	    posPue = i+1;
	  }
	}
      }
    }
    
    if (inv > cap) {
      inv = -3;
      posInv = -1;
    }
    
    if (obj == 11) {
      if ((posNom >  0) && (posCap > 0) && (posInv >= 0) && (posCon >= 0) && (posArchivo > 0)) {
	int *res = xmalloc(5*sizeof(int));
	res[0] = posNom;
	res[1] = posCap;
	res[2] = posInv;
	res[3] = posCon;
	res[4] = posArchivo;
	return res;
      } else {
	msjError(-3);
      }
    } else if (obj == 13) {
      if ((posNom > 0) && (posCap >= 0) && (posInv >= 0) && (posTie >= 0) && (posSum >= 0) && (posPue >= 0)) {
	int *res = xmalloc(5*sizeof(int));
	res[0] = posNom;
	res[1] = posCap;
	res[2] = posInv;
	res[3] = posTie;
	res[4] = posSum;
	res[5] = posPue;
	return res;
      } else {
	msjError(-3);
      }
    }
  } else {
    msjError(-2);
  }
  return 0;
}
