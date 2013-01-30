###############################################################
##
## Asunto: Codigo fuente de Proyecto 1
## Materia: Laboratorio de Redes
## Trimestre: Enero-Marzo 2013
##
## Grupo: 
## Integrantes:                  Carnet:
## * Maria Isabel  Jilo          (07-41063)
## * Jose Gregorio Lezama        (07-41104)
##
###############################################################

.PHONY: all clean

CC = gcc

all: bomba centro

bomba: bomba.o funciones.c
	$(CC) bomba.o -o bomba   

bomba.o: bomba.c funciones.c
	$(CC) -c bomba.c

centro: centro.o funciones.c
	$(CC) centro.o -o centro

centro.o: centro.c funciones.c
	$(CC) -c centro.c
clean:
	rm bomba centro *.o

