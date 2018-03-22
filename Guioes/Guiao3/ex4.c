#include <unistd.h>
#include <sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
/*
Implemente um programa que execute o programa da questão anterior com uma qualquer lista de argumentos.
Mantendo o nome do ficheiro que corresponde o programa executável, experimente alterar o
primeiro elemento da lista de argumentos (índice zero do argv).
*/


int main (int argc, char * argv[]) {

	//strncpy(argv[1],"12345")

	execv("./ex3",&argv[1]);
	perror("Não funcinou");

	return 1;

}				