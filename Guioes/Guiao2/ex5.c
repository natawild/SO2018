#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h> 
#include <stdlib.h>

/*
Implemente um programa que crie uma descendência em profundidade de dez processos, ou seja, 
o processo cria um filho, este filho cria outro, e assim por diante até ao décimo nível de descendência.
Cada processo deverá imprimir o seu pid e o pid do seu pai. Se desejar, poderá obrigar cada processo a 
esperar pelo fim da execução do seu (eventualmente) único filho.
*/

int main() {
	/*
	por cada iteração exponencializa o nr de filhos, aqui não ia ter 10 processos, mas sim muitos 
	for(i=0 ; i!=10; i++){
		fork(); 
	}
	*/ 
	for(int i = 0; i != 10; i++){
		pid_t pid = fork(); 
		if(pid) {/* se sou pai */
			printf("Eu sou o processo: %d o meu pid é %d, o meu pai é %d\n", i+1, getpid(), getppid());
			wait(0); //eu antes de terminar vou esperar que o meu filho termine 
			_exit(0); 
		}
	}
	return 0; 
}

