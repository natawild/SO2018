#include <unistd.h>
#include <sys/wait.h>
#include<stdio.h>
#include<stdlib.h>

/*
Implemente um programa que imprima a lista de argumentos recebidos na sua linha de comando
*/


int main (int argc, char * argv[]) {
	int i = 0;
	for (i = 0; i < argc; i++) {
    	printf ("argv[%d]->%s\n", i, argv[i]);
	}

	return 0;
}