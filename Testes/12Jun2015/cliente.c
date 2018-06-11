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

int main(int argc, char *argv[]){
	char *nomeFicheiro;
	//int ordena;  
	//ordena = mkfifo("ordenar", 0666); 
	int ler; 
	int lidos; 
	
		//if(ordena <0) {perror("sads"); _exit(1);}


		ler=open("ordenar" , O_WRONLY);
		write(ler,argv[1],sizeof(argv[1]));
			//escreveFicheiro(nomeFicheiro); 
		

	
	close(ler); 
	return 0; 
}

