
#include <unistd.h>
#include <sys/wait.h>
#include<stdio.h>
#include<stdlib.h>

int main () {
	pid_t filho;
	filho=fork();
	if(filho == 0) { /* se sou o filho */    
    	execlp("ls","ls","-l",NULL);
    	perror("Não funcionou");
    	_exit(-1);
	}
	else {
		wait (NULL);  //pai espera pelo final da listagem 
	}

	/*
	if(filho == 0) { /* se sou o filho    
    	execlp("ls","ls","-l",NULL);
    	perror("Não funcionou");
    	_exit(-1);
	}
	printf("Sou o pai"); 

	*/
  	return 0;
}