#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

/*
Implemente um programa que execute o comando ls -l. Note que no caso da execução ser bem
sucedida, mais nenhuma outra instrução é executada do programa original.
*/

int main (int argc, char * argv[]) {

	execlp("ls","Coisinho","-l",NULL);
	perror ("Não funcionou");//aqui só faz sentido ter tratamento de erros 
	//return 1; 
	//_exit(1);
	return 0;
}