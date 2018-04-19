#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*
Escreva um programa que emule o funcionamento do interpretador de comandos na execução encadeada
de ls /etc | wc -l
*/

int main(){
	int pd[2];
	pipe(pd);

  	if(fork() == 0) { //se sou filho 
  		close(pd[1]); //fcho escrita
  		dup2(pd[0],0);
  		close(pd[0]);
   		execlp("wc","wc","-l",NULL);
  		perror("wc");
   		return 1;
	} 
 	close(pd[0]); //fecho leitura 
 	dup2(pd[1],1);
 	close(pd[1]);
 	execlp("ls","ls","/etc",NULL);
 	perror("ls");
	return 1;

}
