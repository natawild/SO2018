#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h> 

/*
Implemente um programa que imprima o seu identificador de processo e o de seu pai.
Comprove invocando o comando ps que o pai do seu processo é o interpretador de comandos 
que utilizou para o executar 

*/

int main() {
	pid_t pid = fork(); 
	puts("sou o original"); 
	if(pid==0){ /* filho */
		sleep(2); //qd o filho imprime o pai já não existe 
		printf("pid=%d, ppid = %d\n",getpid(), getppid());
		return 0; 
	}
	if( pid == -1){ /* sou o pai mas não criei um filho*/
		perror ("fork"); 
		return 1; 
	}
	else{ /* sou o pai de um filho */
	sleep(5);
	printf("pid = %d, ppid =%d, filho =%d\n", getpid(), getppid(), pid);
	sleep(5);
	pid = wait(NULL); 
	printf("pai: terminou o filho %d\n", pid); 
	
	}
	return 0; 
	
}

//um filho termina quando usamos o wait() para ter a certeza que o filho terminou 