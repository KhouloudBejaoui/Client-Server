#include "serv_cli.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
  
  file = fopen("/home/khouloud/Desktop/projetUnix/Projet_Unix_Part2/src/file.txt", "w");

  char *ip = "127.0.0.1"; // adresse ip
  int port = 9090;        // port
  int e;                  // erreur

  int sockfd, new_sock;
  struct sockaddr_in server_addr, new_addr; // Structure for handling internet addresses
  socklen_t addr_size;

  int reponse[2000]; // tableau qui contient les nombres aléatoires envoyés client
  int n;             // représente le nombre de numéros demandés par le client

  srand(getpid());

  // création de la socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
  {
    printf("Erreur lors de la création du socket");
    exit(1);
  }
  printf("Le socket serveur est crée avec succès\n");

  server_addr.sin_family = AF_INET;            // famille adresse
  server_addr.sin_port = port;                 // port
  server_addr.sin_addr.s_addr = inet_addr(ip); // adresse ip

  // association du socket à l’adresse IP, au port et à l'adresse du famille'.
  e = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (e < 0)
  {
    printf("Erreur dans la liaison");
    exit(1);
  }
  printf("Liaison faite avec succès.\n");

  // prêt à accepter les demandes de connexion client
  // Création d’une file d’attente de demandes de connexion de longueur = 10 pour mettre en file d’attente les demandes de connexion entrantes.
  if (listen(sockfd, 10) == 0)
  {
    printf("Écoute....\n");
  }
  else
  {
    printf("Erreur lors de l'écoute");
    exit(1);
  }

  while (1)
  { // Création d’un nouveau descripteur de socket avec les mêmes propriétés que socketfd
    addr_size = sizeof(new_addr);
    new_sock = accept(sockfd, (struct sockaddr *)&new_addr, &addr_size);
    // Recevoir le nombre de numéros demandés par le client et le stocker dans la variable n
    int n1 = recv(new_sock, &n, SIZE, 0); // n longueur du message reçu
    if (n1 <= 0)
    {
      break;
    }
    printf("Le client demande %d numéros.\n", n);

    int pid = fork();
    if (pid < 0)
    {
      printf("Erreur fork");
      exit(1);
    }

    if (pid == 0)
    {
      // générer les nombres au hasard et les stocker en réponse
      for (int i = 0; i < n; i++)
      {
        reponse[i] = (rand() % NMAX) + 1;
      }
      // écriture des numéros sortants sur le socket accepté new_socket
      if (send(new_sock, &reponse, sizeof(reponse), 0) == -1)
      {
        printf("Erreur lors de l'envoi des numéros.");
        exit(1);
      }
      printf("Les numéros sont envoyés au client avec succès.\n");
    }
  }
  fclose(file);
  return 0;
}
