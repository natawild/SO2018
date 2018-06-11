#include <stdio.h> //printf function
#include <fcntl.h> //open function
#include <unistd.h> //read and write, lseek functions
#include <sys/types.h> //lseek function 
#include <sys/wait.h> //wait function
#include <stdlib.h> //strtol fucntion
#include <string.h>
#include <signal.h> 
#include <time.h>
#include <string.h>
#include <sys/stat.h>

void escreveFicheiro(char * nomeFicheiro){
	pid_t x; 
	char * novoNome = (char*) malloc(1024); 
	sprintf(novoNome,"%s.sorted",nomeFicheiro); 
	x=fork(); 
	if(x==0){
		execlp("sort","sort","-o", novoNome, nomeFicheiro, NULL); 
		printf("The call to execlp() was not successful.\n");
		perror("Erro no execlp"); 
		_exit(1); 
	}
	else{
		wait(0); 
	}
}


int main(int argc, char *argv[]){
	char *nomeFicheiro=(char*) malloc(1024) ;
	int ordena;  
	ordena = mkfifo("ordenar", 0666); 
	int ler; 
	int lidos; 
	while(1){
		if(ordena <0) {perror("sads"); _exit(1);}

		
		ler=open("ordenar" , O_RDONLY);
		if( (lidos = read(ler,nomeFicheiro,sizeof(nomeFicheiro)))>0){

			escreveFicheiro(nomeFicheiro); 

		}

	}
	close(ler); 
	return 0; 
}