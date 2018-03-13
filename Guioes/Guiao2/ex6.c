#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h> 
#include <stdlib.h>

/*
Pretende-se determinar a existência de um determinado número inteiro nas linhas de numa matriz de
números inteiros, em que o número de colunas é muito maior do que o número de linhas. Implemente,
utilizando processos um programa que determine a existência de um determinado número, recebido como
argumento, numa matriz gerada aleatoriamente.
*/

//nr das colunas mt maior que as linhas 


int main(int argc, char* argv[]) {
	int i, j; 
	int matriz[i][j]; 

	//Atribui nrs aleatórios na matriz 
	for(i=0;i<5;i++) {
   		for(j=0;j<50;j++) {
        	matriz[i][j]=rand() % 10; 
        	printf("%d\n",matriz[i][j]);
		}

	}
	//iterar ciclo pela linhas 

}
