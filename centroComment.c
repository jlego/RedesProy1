
#define PORT 25503
#define QUEUELENGTH 5

void echo(int sockfd) {
  char car;
  int status;

  while (read(sockfd, &car, 1) == 1)
    /* Echo the character. */
    if (write(sockfd, &car, 1) != 1)
      printf("Error escribiendo en el socket");
}

// Adentro del main
  /* Open a TCP socket. */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    printf("can't open socket");

  /* Bind the address to the socket. */
  bzero(&serveraddr, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons(PORT);
  if (bind(sockfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) != 0)
    printf("can't bind to socket");
  if (listen(sockfd, QUEUELENGTH) < 0)
    printf("can't listen");

  while (1) {
    /* Wait for a connection. */
    clientaddrlength = sizeof(clientaddr);
    newsockfd = accept(sockfd, 
                       (struct sockaddr *) &clientaddr,
                       &clientaddrlength);
    if (newsockfd < 0)
      printf("Error de aceptacion");

    /* Fork a child to handle the connection. */
    pid = fork();
    if (pid < 0)
      printf("Error creando el proceso");
    else if (pid == 0) {
      /* I'm the child. */
      close(sockfd);
      echo(newsockfd);
      echo(0);
      printf("Escribio\n");
      exit(EXIT_SUCCESS);
    }
    else
      /* I'm the parent. */
      close(newsockfd);
  }
    
    
