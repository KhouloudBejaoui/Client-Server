#ifndef __HANDLERS_CLI_h__
#define __HANDLERS_CLI_h__


void hand_reveil(int sig){
    fprintf(file,"\nJe suis le client numero %d : je suis reveille \n",getpid());
}

#endif 
