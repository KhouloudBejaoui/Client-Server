#include "serv_cli_fifo.h"
#include "Handlers_Serv.h"
#include "signal.h"

int main(int argc, char **argv){

    /*Déclarations */
    int f1,f2;//pour tester la creation des 2 tubes
    int n; //le nombre envoyé par le client
    int nsig; //num signal
    int idClient;


    file= fopen("/home/khouloud/Desktop/projetUnix/Projet_Unix_Part1/src/file.txt","w");

    /* Création des tubes nommés */
    unlink(fifo1); //supprimer fifo1 s'il existe
    unlink(fifo2); //supprimer fifo2 s'il existe
    f1= mkfifo(fifo1,0644); //creation du fifo1
    f2= mkfifo(fifo2,0644); //creation du fifo2
    if (f1 == -1 || f2 == -1)
    {
        printf("erreur lors de creation des tubes");
        exit(2);
    }
    
    /*initialisation du générateur de nombres aléatoires*/
    srand(getpid());

    /* Ouverture des tubes nommés */
    desc1=open(fifo1,O_RDWR); //ouverture du fifo1 en lecture et ecriture
    desc2=open(fifo2,O_WRONLY); //ouverture du fifo1 en ecriture
    if (desc1 == -1 || desc2 == -1)
    {
        printf("erreur lors de l'ouverture des tubes");
        exit(1);
    }

    /* Installation des Handlers */
    signal(SIGUSR1,hand_reveil); //a la reception du sigusr1 on va executer hand_reveil
    for(nsig=1;nsig<=NSIG;nsig++){
        if(nsig!=SIGUSR1){

            signal(nsig,fin_serveur); //si ce n'est pas un signal sigusr1 on fait fin serveur
        }
    }

    while(1){

        /* lecture d’une question */
        read(desc1,question,sizeof(question));
        idClient = question[0];
        n=question[1];

        /* construction de la réponse */
        reponse[0]=getpid();//id du serveur
        for (int i = 1; i < n; i++)
        {
            reponse[i]=rand()%10000;
        }
        

        /* envoi de la réponse */
        write(desc2,reponse,sizeof(reponse));
        
        /* envoi du signal SIGUSR1 au client concerné */
        printf("\nEnvoi de SIGUSR1 au client num = %d\n",idClient);
        kill(idClient,SIGUSR1);
        fclose(file);
    }
close(desc1);
close(desc2);

}
