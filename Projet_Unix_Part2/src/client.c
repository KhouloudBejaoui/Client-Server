#include "serv_cli.h"
#include <unistd.h>

int main(int argc, char **argv){
  char *ip = "127.0.0.1"; //adresse ip
  int port = 9090; //port
  int e; //erreur
  file= fopen("/home/khouloud/Desktop/projetUnix/Projet_Unix_Part2/src/file.txt","w");

  int sockfd; //socket client
  struct sockaddr_in server_addr; //abstract address type
  
  int reponse[2000];//contient les numéros reçus du serveur
  srand(getpid());
  int n=(rand()%NMAX)+1; //numéro choisi aléatoirement
  
  //création de la socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    fprintf(file,"Erreur lors de la création du socket");
    exit(1);
  }
  fprintf(file,"Le socket serveur est crée avec succès\n");

  server_addr.sin_family = AF_INET; //famille adresse
  server_addr.sin_port = port; //numéro port
  server_addr.sin_addr.s_addr = inet_addr(ip); //adresse ip

  //Établissement d’une connexion au serveur
  e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)); 
  if(e == -1) {
    fprintf(file,"Erreur dans le socket");
    exit(1);
  }
  fprintf(file,"Je demande au serveur de m'envoyer %d nombres.\n",n);

  //Écriture du numéro sortant dans socket socketfd
  if (send(sockfd, &n, sizeof(n), 0) == -1) { 
    fprintf(file,"Erreur lors de l'envoi du numéro.");
    exit(1);
   }
   fprintf(file,"Demande envoyée avec succès.\n");
   
   //réception du tableau de nombres sur le socket socketfd et le stocke dans reponse
   int n1 = recv(sockfd, &reponse, sizeof(reponse), 0); //n longueur du message reçu
   if (n1 <= 0){
    fprintf(file,"erreur");
   }
  
  //Affichage de la réponse du serveur
  fprintf(file,"La réponse du serveur : \n");
  for(int i=0; i<n; i++){
    fprintf(file,"%d ) %d\n",i,reponse[i]);
  }
  
  //femeture de la connexion
  fprintf(file,"Fermeture de la connexion.\n");
  close(sockfd);
fclose(file);
  return 0;
}
