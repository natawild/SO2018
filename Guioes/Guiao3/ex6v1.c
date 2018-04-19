#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define MAX 100

int mysystem(char * comando){
	char* token = NULL; 
	char* argv[MAX]; 
	int i, status; 
	pid_t pid;
	char* copia = strdup(comando);  
	for(i=0; i!=MAX-1 && (token = strsep(&copia, " ")) != NULL; i++)
		argv[i] = strdup(token); 

	argv[i]= NULL; 

	if((pid = fork()) == 0){
		execvp(argv[0], argv); //não sei o nr de argumentos 
		_exit(1); 
	}
	//wait(&status); 
	waitpid(pid, &status, 0);
	free(copia);  
	return WIFEXITED(status) ? WEXITSTATUS(&status) : -1;  

}

int  main() {
	mysystem("ls -l  ex6"); 
	return 0;

}