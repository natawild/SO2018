#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>

/*
Usando SIGCONT, SIGSTOP, e SIGCHLD, escreva um programa que receba como argumento uma lista
de comandos (que não têm argumentos), e corra os programas, escalonando-os de forma rotativa (round
robin) em intervalos de 1 segundo.
*/

void child(int s){
	printf("%s\n","SIGCHLD" );
}

void cont (int s){
	printf("%s\n","SIGCONT" );
}

int main(){
	pid_t pid = fork(); 
	if(!pid){
		signal(SIGCONT, cont); 
		pause(); 
		pause(); 
		_exit(0); 
	}
	sleep(1); 
	signal(SIGCHLD, child); 
	kill(pid, SIGCONT); 
	sleep(1); 
	kill(pid, SIGSTOP); 
	sleep(1); 
	kill(pid, SIGCONT); 
	wait(0); 
	sleep(1);
}