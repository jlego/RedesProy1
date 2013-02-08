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


#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>

#include "funciones.c"
#include "lista.c"

#ifndef true
# define true 1
#endif

#ifndef false
# define false 0
#endif

int main(int argc, char **argv) {
  /* Definicion de los valores recibidos por Pantalla e Importantes para el main */
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
  int espera = -1;
  int vacio = true;
  if (inv > 0) {
    vacio = false;
  }

  // Definicion de las variables relacionadas a la evaluacion del Archivo
  char tmp[64];                            
  strcpy(tmp,argv[parametros[4]]);
  FILE *archivo = fopen(tmp,"r");
  lista *servidores = iniciarLista();

  /* Definicion de las Variables relacionadas con la conexion */
  struct sockaddr_in address;
  struct in_addr inaddr;
  struct hostent *host;
  int sock;

  char *inbuffer;
  int tResp;

  char *nomC;
  char *dir;
  int pue;
  char sim[1];

  /* Definicion de las Variables relacionadas con el Log del Sistema */
  char nombreLog[128] = "log_";
  strcat(nombreLog,nom);
  strcat(nombreLog,".txt");
  FILE *log = fopen(nombreLog,"w+");

  /* Inicio del Trabajo, se maneja con el Log */
  printf("Se guardara la informacion en: %s\n",nombreLog);

  /* Estado Inicial */
  fprintf(log,"Inventario Inicial: %d litros\n",inv);
  printf("Inventario Inicial: %d litros\n",inv);
  
  /* Se lee la informacion del archivo */  
  while (!feof(archivo)){
    if ( fscanf(archivo,"%[^&]%[&]%[^&]%[&]%d ",nomC,sim,dir,sim,&pue) != EOF ){
      printf("Nombre del Centro:%s  Direccion DNS: %s  Numero de Puerto: %d \n", nomC, dir, pue);

      if (inet_aton(dir, &inaddr)) {
	host = gethostbyaddr((char *) &inaddr, sizeof(inaddr), AF_INET);
      } else {
	host = gethostbyname(dir);
      }
      if (host) {
	sock = socket(AF_INET,SOCK_STREAM,0);
	if (sock >= 0) {
	  address.sin_family = AF_INET;
	  address.sin_port = htons(pue);
	  memcpy(&address.sin_addr, host->h_addr_list[0], sizeof(address.sin_addr));

	  if (connect(sock, (struct sockaddr *)&address, sizeof(address)) >= 0) {
	    if (write(sock,"tiempo",6) == 1) {
	      if (read(sock, &inbuffer, 1) == 1) {
		tResp = atoi(inbuffer);
		agregarElemento(servidores,nomC,dir,pue,tResp);
	      } else {
		printf("No se logro comunicar de manera efectiva con %s, en la direccion %s y puerto %d.\nSin embargo, se continuara con la ejecucion del programa\n",nomC,dir,pue);
	      }
	    } else {
	      printf("No se logro comunicar de manera efectiva con %s, en la direccion %s y puerto %d.\nSin embargo, se continuara con la ejecucion del programa\n",nomC,dir,pue);
	    }
	    close(sock);
	  } else {
	    printf("No se logro comunicar de manera efectiva con %s, en la direccion %s y puerto %d.\nSin embargo, se continuara con la ejecucion del programa\n",nomC,dir,pue);
	  }
	} else {
	  printf("No se logro comunicar de manera efectiva con %s, en la direccion %s y puerto %d.\nSin embargo, se continuara con la ejecucion del programa\n",nomC,dir,pue);
	}
      } else {	
	printf("No se logro comunicar de manera efectiva con %s, en la direccion %s y puerto %d.\nSin embargo, se continuara con la ejecucion del programa\n",nomC,dir,pue);
      }
    }
  }

  while(tiempo < tiempoTotal) {
    printf("Tie: %d e Inv: %d\n",tiempo,inv);
    sleep(min);

    /* Tanque Full */
    if (inv == cap) {
      fprintf(log,"Tanque Full: %d minutos\n",tiempo);
      printf("Tanque Full: %d minutos\n",tiempo);  
    }
    
    /* Realizar consumo */
    if (inv >= con) {
      inv -= con;
    } else {
      inv = 0;
    }

    /* Realizar Solicitud */
    if (inv < 380) {
      // Realizar solicitud
      if (espera == -1) {
	int i = 0;
	int listo = false;
	elemento *e;
	while ((listo != true) && (i < tamLista(servidores))) {
	  e = obtenerElemento(servidores,i);
	  nomC = e->nombre;
	  dir = e->dir;
	  pue = e->puerto;
	  tResp = e->tResp;
	  if (inet_aton(dir, &inaddr)) {
	    host = gethostbyaddr((char *) &inaddr, sizeof(inaddr), AF_INET);
	  } else {
	    host = gethostbyname(dir);
	  }
	  
	  if (host) {
	    sock = socket(AF_INET,SOCK_STREAM,0);
	    if (sock >= 0) {
	      address.sin_family = AF_INET;
	      address.sin_port = htons(pue);
	      memcpy(&address.sin_addr, host->h_addr_list[0], sizeof(address.sin_addr));
	      if (connect(sock, (struct sockaddr *)&address, sizeof(address)) >= 0) {
		if (write(sock,"tiempo",6) == 1) {
		  if (read(sock, &inbuffer, 1) == 1) {
		    if (strcmp(inbuffer,"si") == 0){
		      fprintf(log,"Peticion: %d minutos, %s, Ok\n",tiempo,nomC);
		      printf("Peticion: %d minutos, %s, Ok\n",tiempo,nomC);
		      espera = tResp;
		      listo = true;
		    } else {
		      fprintf(log,"Peticion: %d minutos, %s, Sin inventario\n",tiempo,nomC);
		      printf("Peticion: %d minutos, %s, Sin inventario\n",tiempo,nomC);
		    }
		  } else {
		    fprintf(log,"Peticion: %d minutos, %s, Sin respuesta\n",tiempo,nomC);
		    printf("Peticion: %d minutos, %s, Sin Respuesta\n",tiempo,nomC);
		  }
		} else {
		  fprintf(log,"Peticion: %d minutos, %s, Sin respuesta\n",tiempo,nomC);
		  printf("Peticion: %d minutos, %s, Sin Respuesta\n",tiempo,nomC);
		}
		close(sock);
	      } else {
		fprintf(log,"Peticion: %d minutos, %s, Sin respuesta\n",tiempo,nomC);
		printf("Peticion: %d minutos, %s, Sin Respuesta\n",tiempo,nomC);
	      }
	    } else {
	      fprintf(log,"Peticion: %d minutos, %s, Sin respuesta\n",tiempo,nomC);
	      printf("Peticion: %d minutos, %s, Sin Respuesta\n",tiempo,nomC);
	    }
	  } else {
	    fprintf(log,"Peticion: %d minutos, %s, Sin respuesta\n",tiempo,nomC);
	    printf("Peticion: %d minutos, %s, Sin Respuesta\n",tiempo,nomC);
	  }
	  i += 1;
	}
      }
    }

    /* Tanque Vacio */
    if (inv == 0) {
      if (vacio == false) {
	fprintf(log,"Tanque Vacio: %d minutos\n",tiempo);
	printf("Tanque Vacio: %d minutos\n",tiempo);
	vacio = true;
      }
    }

    /* Llegada de la Gandola */
    if (espera >= 0) {
      espera -=1;
      if (espera == 0) {
	fprintf(log,"Llegada de gandola: %d minutos, 38000 litros\n",tiempo);
	printf("Llegada de gandola: %d minutos, 38000 litros\n",tiempo);
	inv += 38000;
	vacio = false;
      }
    }
    /* Pasa el tiempo */
    tiempo += 1;
  }
  fclose(log);
  limpiarLista(servidores);
  printf("El resumen de la sesion ha sido guardado en %s \n",nombreLog);
  return 0;
}
