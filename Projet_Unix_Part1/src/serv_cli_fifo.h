#ifndef _SERV_CLI_FIFO_H
#define _SERV_CLI_FIFO_H

#define NMAX 10

#include<stdio.h>
#include<fcntl.h> 
#include<signal.h>
#include<string.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>

char fifo1[]="/home/khouloud/Desktop/projetUnix/Projet_Unix_Part1/build/fifo1"; //tube 1
char fifo2[]="/home/khouloud/Desktop/projetUnix/Projet_Unix_Part1/build/fifo2"; //tube 2
FILE *file;

int question[2]; //tableau qui contient la question(idClient et n)
int reponse[NMAX+1]; //tableau qui contient la reponse (idServeur et n nombre aleatoire)
int desc1; //pour tester l'ouverture de tube fifo1
int desc2; //pour tester l'ouverture de tube fifo2

#endif
