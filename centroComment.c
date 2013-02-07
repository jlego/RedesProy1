#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include "funciones.c"

// #define PORT 25503
// #define QUEUELENGTH 5

void gandola(int sockfd) {
  char car;
  int status;

  while (read(sockfd, &car, 1) == 1)
    /* Echo the character. */
    if (write(sockfd, &car, 1) != 1)    // Envia una gandola de 38000
      printf("Error escribiendo en el socket");
}

int main(int argc, char **argv) {
  int sockfd, newsockfd;
  struct sockaddr_in clientaddr, serveraddr;
  int clientaddrlength;
  int pid;
  int m;
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

  /* Se crean los pipes */
  for (m = 0; m < QUEUELENGTH; m++ ) {
    if (pipe (fd[m]) == -1)  {
	fprintf(stderr,"Error creando el pipe %d: %s \n",m,strerror(errno));
	exit(1);
    };
    if (pipe (fdp[m]) == -1)  {
	fprintf(stderr,"Error creando el pipe %d: %s \n",m,strerror(errno));
	exit(1);
    };
  }
  
  /* Ejemplo de lectura y escritura en un pipe 
      read(fd[k][0], &salida, sizeof(salida));
      write(fd[i][1], &id, sizeof(id) );
      write(fd[i][1], &d[i].numCola, sizeof(d[i].numCola));
      close(fd[i][0]);		
      close(fd[i][1]);
  */

  /* Se abre el Socket TCP */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    printf("Error abriendo el Socket");

  /* Enlazando la direccion al socket. */
  bzero(&serveraddr, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons(pue);     // Cambie PORT por pue

  if (bind(sockfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) != 0)
    printf("Error enlazando el Socket");
  if (listen(sockfd, QUEUELENGTH) < 0) // Inventario < 38000
    printf("No disponible");            

  /* Esperando una peticion */
  while (1) {
    clientaddrlength = sizeof(clientaddr);
    newsockfd = accept(sockfd,(struct sockaddr *) &clientaddr,&clientaddrlength);
    if (newsockfd < 0)
      printf("Error de aceptacion");

    /* Se hace fork */
    pid = fork();
    if (pid < 0)
      printf("Error creando el proceso");
    else if (pid == 0) {
      /* Codigo del hijo */
      close(sockfd);
      gandola(newsockfd);  
      gandola(0);
      printf("Envio una gandola \n");
      // Se escribe en el pipe que inv = inv - 38000
      exit(EXIT_SUCCESS);
    }
    else
      /* Codigo del padre */
      close(newsockfd);
  }
  return 0;
}
