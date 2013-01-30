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
 * Archivo: centro.c
 *   Para esta entrega, se solicito programar siguiendo el estilo de 
 * Cliente-Servidor, este archivo hace referencia a los sevidores, que en este
 * caso son los centros, que esperan la conexion solicitada por las bombas 
 * definidas por bombas.c (clientes). Al realizar la conexion debe responder 
 * si se puede satisfacer la solicitud del cliente o no. Para realizar, sigue
 * los siguientes pasos:
 *   1. Evaluar los parametros
 *   2. Esperar conexion
 *   3. Establecer conexion
 *   4. Responder si se puede satisfacer o no la solicitud de bomba
 *                             
 *************************************************************/

#include "funciones.c"

int main(int argc, char **argv) {
  // Definicion de los valores recibidos por Pantalla e Importantes para el main
  int tiempoTotal = 10;                   // Tiempo de Trabajo
  int min = 1;                            // Duracion del minuto
  int tiempo = 0;                         // Tiempo que se lleva trabajando
  int *parametros = verOp(13,argc,argv);  // Verificacion de los parametros
  char nom[64];                           // Nombre del C
  strcpy(nom,argv[parametros[0]]);        // Def de Nombre del C
  int cap = atoi(argv[parametros[1]]);    // Def de Cap Maxima del C
  int inv = atoi(argv[parametros[2]]);    // Def de Inventario del C
  int tie = atoi(argv[parametros[3]]);    // Def de TiempoRespuesta del C
  int sum = atoi(argv[parametros[4]]);    // Def de Suministro del C
  int pue = atoi(argv[parametros[5]]);    // Def de Puerto de comunicacion
  free(parametros);                       // Liberacion de memoria de Parametros

  // Definicion de las Variables relacionadas con la conexion
  int sockfd, newsockfd;
  struct sockaddr_in clientaddr, serveraddr;
  int clientaddrlength;
  int pid;

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

  while (tiempo < tiempoTotal) {
    printf("Tie: %d e Inv: %d\n",tiempo,inv);
    sleep(min);

    // Recibir Suministro
    inv += cap;
    if (inv > cap) {
      inv = cap;
    }

    // Tanque Full
    if (inv == cap) {
      fprintf(log,"Tanque Full: %d (Tiempo)\n",tiempo);
      printf("Tanque Full: %d (Tiempo)\n",tiempo);  
    }
    
    // Realizar Suministro

    // Tanque Vacio
    if (inv == 0) {
      fprintf(log,"Tanque Vacio: %d (Tiempo)\n",tiempo);
      printf("Tanque Vacio: %d (Tiempo)\n",tiempo);
    } 
    // Realizar Solicitud
    if (inv < 380) {
      fprintf(log,"Se realizo peticion: %d (Tiempo)\n",tiempo);
      printf("Se realizio peticion: %d (Tiempo)\n",tiempo);
    }
    // Pasa el tiempo
    tiempo += 1;
  }
  return 0;
}
