#ifndef __HANDLERS_SERV_h__
#define __HANDLERS_SERV_h__

#include<stdio.h>
#include<fcntl.h> 
#include<signal.h>
#include<string.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>

void hand_reveil(int sig){
    fprintf(file,"\nJe suis le serveur numero %d : je suis reveille et je vais traiter la demande \n-----------------------------------------------------\n",getpid());
}

void fin_serveur(int sig){
    fprintf(file,"\n fin serveur \n");
    exit(1);
}

#endif 


