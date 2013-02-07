#include "funciones.c"

int main(int argc, char **argv) {
  int tiempo = 8*60;
  int min = 100;
  int *parametros = verOp(13,argc,argv);
  char nom[64];
  strcpy(nom,argv[parametros[0]]);
  int cap = atoi(argv[parametros[1]]);
  int inv = atoi(argv[parametros[2]]);
  int tie = atoi(argv[parametros[3]]);
  int sum = atoi(argv[parametros[4]]);
  int pue = atoi(argv[parametros[5]]);
  while(tiempo > 0) {
  
    sleep(min);
    tiempo -= 1;
  }
  return 0;
}

