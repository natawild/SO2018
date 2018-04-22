#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


int main(){
	int pfds[2];
	int n;
	char buffer[20];

	pipe(pfds); 

	if(!fork()){
		close(pfds[1]);
		n = read(pfds[0], buffer, sizeof(buffer));
		/*
		printf("FILHO a ler\n");
		n = read(pfds[0], buffer, sizeof(buffer));
		printf("FILHO leu: %d %s\n",n ,buffer );
		n = read(pfds[0], buffer, sizeof(buffer));
		printf("FILHO leuuuuuu: %d %s\n",n ,buffer );
		*/
		write(1,buffer,n); 
		exit(0); 
	} 
	else{
		sleep(6);
		close(pfds[0]); 
		//getchar(); 
		printf("Pai a escrever\n");
		write(pfds[1], "linha de teste muito comprida a ver que disparates vão acontecer se funciona ou não\n", 200);
		wait(NULL); 
	}
	return 0;
}


