#include "funciones.c"

int main(int argc, char **argv) {
  int tiempo = 8*60;
  int min = 100;
  int *parametros = verOp(11,argc,argv);
  char nom[64];
  strcpy(nom,argv[parametros[0]]);
  int cap = atoi(argv[parametros[1]]);
  int inv = atoi(argv[parametros[2]]);
  int con = atoi(argv[parametros[3]]);
  char tmp[64];
  strcpy(tmp,argv[parametros[4]]);
  FILE *archivo = fopen(tmp,"r");
  while(tiempo > 0) {
    printf("%d",tiempo);
    sleep(min);
    tiempo -= 1;
  }
  return 0;
}
