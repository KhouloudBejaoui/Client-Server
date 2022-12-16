#include "serv_cli_fifo.h"
#include "Handlers_Cli.h"
#include "sys/types.h"
#include "signal.h"

int main(int argc, char **argv){

    /* Déclarations */
    srand(getpid());
    int serverId;
    file= fopen("/home/khouloud/Desktop/projetUnix/Projet_Unix_Part1/src/file.txt","w");

    /* Ouverture des tubes nommés */
    desc1=open(fifo1,O_WRONLY); //ouverture du fifo1 en ecriture
    if (desc1 == -1)
    {
        fprintf(file,"erreur lors de l'ouverture de tube fifo1");
        exit(2);
    }
    desc2=open(fifo2,O_RDWR); //ouverture du fifo1 en lecture et ecriture
    if (desc2 == -1)
    {
        fprintf(file,"erreur lors de l'ouverture de tube fifo");
        exit(2);
    }
    /* Installation des Handlers */
    signal(SIGUSR1,hand_reveil);

    /* Construction et envoi d’une question */
    int n=1+rand()%NMAX;   // remplir n aleatoirement
    question[0]=getpid(); //id du client
    question[1]=n;
    write(desc1,question,sizeof(question));

    /* Attente de la réponse */
    pause();

    /* Lecture de la réponse */
    read(desc2,reponse,sizeof(reponse));
    serverId=reponse[0];
    
    /* Envoi du signal SIGUSR1 au serveur */
    fprintf(file,"\nEnvoi de SIGUSR1 au serveur num = %d pour me donner %d entiers\n",serverId,n);
    kill(serverId,SIGUSR1);

    /* Traitement local de la réponse */
    fprintf(file,"\nLa reponse est : \n");
    for (int i = 1; i <= n; i++)
    {
        fprintf(file,"\n %d) l'entier numero %d =  %d \n",i,i,reponse[i]);
    }
    
    close(desc1); 
    close(desc2);
    fclose(file);
}
