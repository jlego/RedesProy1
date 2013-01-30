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
 * Archivo: bomba.c
 *   Para esta entrega, se solicito programar siguiendo el estilo de 
 * Cliente-Servidor, este archivo hace referencia a los clientes, que en este
 * caso son las bomas, que solicitan a los centros definidos por centro.c
 * (servidores). Que los surtan de gasolina. Para poder hacer esta tarea, la 
 * separa en varios pasos:
 *   1. Evaluar los parametros
 *   2. Conectar a los distintos centros y obtener sus tiempos de respuesta,
 *  ordenar los mismos dando prioridad a los que tarden menos en responder
 *   3. Solicitar gasolina en caso de necesitarla
 *                             
 *************************************************************/

#include "funciones.c"

int main(int argc, char **argv) {
  // Definicion de los valores recibidos por Pantalla e Importantes para el main
  int tiempoTotal = 10;                   // Tiempo de Trabajo
  int min = 1;                            // Duracion del minuto
  int tiempo = 0;                         // Tiempo que se lleva trabajando
  int *parametros = verOp(11,argc,argv);  // Verificacion de Parametros
  char nom[64];                           // Nombre de la B
  strcpy(nom,argv[parametros[0]]);        // Def de Nombre de B
  int cap = atoi(argv[parametros[1]]);    // Def de Cap Maxima de B
  int inv = atoi(argv[parametros[2]]);    // Def de Inventario de B
  int con = atoi(argv[parametros[3]]);    // Def de Consumo de B
  free(parametros);                       // Liberacion de memoria de Parametros
  // Definicion de las variables relacionadas a la evaluacion del Archivo
  char tmp[64];                            
  strcpy(tmp,argv[parametros[4]]);
  FILE *archivo = fopen(tmp,"r");

  // Definicion de las Variables relacionadas con la conexion
  int sockfd;
  struct sockaddr_in serveraddr;
  char *server;
  char nomC[64];
  char dir[64];
  int pue;
  char sim[1];

  // Definicion de las Variables relacionadas con el Log del Sistema
  char nombreLog[128] = "log_";
  strcat(nombreLog,nom);
  strcat(nombreLog,".txt");
  FILE *log = fopen(nombreLog,"w+");

  // Inicio del Trabajo, se maneja con el Log
  printf("Se guardara la informacion en: %s\n",nombreLog);

  // Estado Inicial  
  fprintf(log,"Estado Inicial: %d (Inventario)\n",inv);
  printf("Estado Inicial: %d (Inventario)\n",inv);

  // 
  while (!feof(archivo)){
    if ( fscanf(archivo,"%[^&]%[&]%[^&]%[&] %d ",nomC,sim,dir,sim,&pue) != EOF ){
      printf("Nombre del Centro:%s  Direccion DNS: %s  Numero de Puerto: %d \n", nomC, dir, pue);
    }
  while(tiempo < tiempoTotal) {
    printf("Tie: %d e Inv: %d\n",tiempo,inv);
    sleep(min);

    // Tanque Full
    if (inv == cap) {
      fprintf(log,"Tanque Full: %d (Tiempo)\n",tiempo);
      printf("Tanque Full: %d (Tiempo)\n",tiempo);  
    }
    
    // Realizar consumo
    if (inv >= con) {
      inv -= con;
    } else {
      inv = 0;
    }

    // Realizar Solicitud
    if (inv < 380) {
      fprintf(log,"Se realizo peticion: %d (Tiempo)\n",tiempo);
      printf("Se realizio peticion: %d (Tiempo)\n",tiempo);
    }

    // Tanque Vacio
    if (inv == 0) {
      fprintf(log,"Tanque Vacio: %d (Tiempo)\n",tiempo);
      printf("Tanque Vacio: %d (Tiempo)\n",tiempo);
    } 
    // Pasa el tiempo
    tiempo += 1;
  }
  fclose(log);
  printf("El resumen de la sesion ha sido guardado en %s \n",nombreLog);
  return 0;
}
