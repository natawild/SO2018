#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h> 
#include <stdlib.h>

/*
Implemente um programa que crie dez processos filhos que deverão executar (potencialmente) em concorrência. 
O pai deverá esperar pelo fim da execução de todos os seus filhos, imprimindo os respectivos
códigos de saída.
*/

int main() {
	int i, status;

	for(i = 0; i < 10; i++){
		pid_t pid = fork();
		if(pid == 0){//sou filho 
			printf("Sou o filho número %i\n",i+1);
			printf("Sou o filho %d com o PID %d, com pai %d\n",i+1,getpid(), getppid());
			_exit(i+1);
		}
	}

	for(i = 0; i < 10; i++){
		pid_t pid = wait(&status);
		if(WIFEXITED(status)){
			printf("Pai: pid = %d, exit do filho = %d\n",pid, WEXITSTATUS(status));	
		}
		else {
			puts("ui... o filho não terminou com exit"); 
		}

	}		
}
