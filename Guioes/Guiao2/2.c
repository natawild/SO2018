#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h> 

/*
Implemente um programa que imprima o seu identificador de processo e o de seu pai.
Comprove invocando o comando ps que o pai do seu processo é o interpretador de comandos 
que utilizou para o executar 

*/

int main() {
	pid_t pid; 
	puts("sou o original"); 
	pid=fork(); 
	if(pid==0){ /* filho */

	}
	if( pid == -1){
		perror ("fork"); 
		return 1; 
	}
	printf("pid = %d, ppid =%d\n", getpid(), getppid());
	
}