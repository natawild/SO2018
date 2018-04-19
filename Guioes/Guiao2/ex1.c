#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h> 

/*
Implemente um programa que imprima o seu identificador de processo e o de seu pai.
Comprove invocando o comando ps que o pai do seu processo é o interpretador de comandos 
que utilizou para o executar 

*/

int main() {
	puts("Antes do sleep"); 
	sleep(10);
	printf(" Meu pid = %d, meu pai: ppid = %d\n", getpid(), getppid());
	_exit(0); 
}