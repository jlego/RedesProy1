// Includes de librerias basicas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Includes de librerias de Internes
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

/*
#define true (1)
#endif
#ifndef (false)
#define false (1)
#endif
*/

int msjError (int numError) {
  int error = -numError;
  printf("Error:");
  switch(numError) {
  case 1:
    printf("No se paso la cantidad de parametros completos");
    break;
  case 2:
    printf("No inicializo todos los parametros");
  }
  printf("El uso del programa es el siguiente: ");
  printf("Los argumentos son:"
	 "    -n                nombre del centro o bomba"
	 "    -o  --output fichero        Escribe la salida al fichero\n"
	 "    -v  --verbose               Imprime más información a la salida\n");
  exit(error);
}

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
	if ((i+1) < (ctdd-1)) {
	  strcpy(nom,argv[i+1]);
	  posNom = i +1;
	}
      } else if (strcmp("-cp",tmp) == 0) {
	if ((i+1) < (ctdd-1)) {
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
	if ((i+1) < (ctdd-1)) {
	  inv = atoi(argv[i+1]);
	  if (inv < 0) {
	    inv = -2;
	  } else {
	    posInv = i+1;
	  }
	}
      } else if (strcmp("-c",tmp) == 0) {
	if ((i+1) < (ctdd-1)) {
	  con = atoi(argv[i+1]);
	  if ((con < 0) || (con > 1000)) {
	    con = -2;
	  } else {
	    posInv = i+1;
	  }
	}
      } else if (strcmp("-fc",tmp) == 0) {
	if ((i+1) < (ctdd-1)) {
	  archivo = fopen(tmp,"r");
	  posArchivo = i+1;
	}
      } else if (strcmp("-t",tmp) == 0) {
	if ((i+1) < (ctdd-1)) {
	  tie = atoi(argv[i+1]);
	  if ((tie < 0) || (tie > 180))  {
	    tie = -2;
	  } else {
	    posTie = i+1;
	  }
	}
      } else if (strcmp("-s",tmp) == 0) {
	if ((i+1) < (ctdd-1)) {
	  sum = atoi(argv[i+1]);
	  if ((sum < 0) || (sum > 10000)) {
	    sum = -2;
	  } else {
	    posSum=i+1;
	  }
	}
      } else if (strcmp("-p",tmp) == 0) {
	if ((i+1) < (ctdd-1)) {
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
    }
    if (obj == 11) {
      if ((strcmp("",nom) != 0) && (cap >= 0) && (inv >= 0) && (con >= 0) && (archivo != NULL)) {
	int res[5] = {posNom,posCap,posInv,posCon,posArchivo};
	return *res;
      } else {
	msjError(-2);
      }
    } else if (obj == 13) {
      if ((strcmp("",nom) != 0) && (cap >= 0) && (inv >= 0) && (tie >= 0) && (sum >= 0) && (pue >= 0)) {
	int res[6] = {posNom,posCap,posInv,posTie,posSum,posPue};
	return *res;
      } else {
	msjError(-2);
      }
    }
  } else {
    msjError(-1);
  }
  return 0;
}
