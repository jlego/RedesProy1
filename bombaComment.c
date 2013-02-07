#define PORT 25503

/* Comunicacion Cliente y Servidor */
void copy(int sockfd) {
  int car;
  char outbuffer;
  char inbuffer;

  while ((car = getchar()) != EOF) {
    /* Escribiendo un caracter al socket. */
    outbuffer = car;
    if (write(sockfd, &outbuffer, 1) != 1)
      printf("Error escribiendo en el Socket");
    /* Lee la respuesta y la imprime */
    if (read(sockfd, &inbuffer, 1) != 1)
      printf("Error leyendo en el Socket");
    putchar(inbuffer);
  }
}

// Adentro del main()
  /* Lectura del fichero de centros */
  while (!feof(archivo)){
    if ( fscanf(archivo,"%[^&]%[&]%[^&]%[&] %d ",nomC,sim,dir,sim,&pue) != EOF ){
      printf("Nombre del Centro:%s  Direccion DNS: %s  Numero de Puerto: %d \n", nomC, dir, pue);
    }
  
    /* Conectando al servidor local */
    server = dir;                                    // Cambie el numero por la direccion que se lee del archivo

    /* Obteniendo la direccion del Servidor */
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(server);
    serveraddr.sin_port = htons(pue);                 // Cambie PORT por el pue que se lee en el archivo

    /* Se abre un Socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
      printf("Error abriendo el Socket");

    /* Conectando con el Servidor */
    if (connect(sockfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0)
      printf("Error conectando al Servidor");

    /* Copy input to the server. */
    copy(sockfd);
    close(sockfd);
  }


