#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LINHAS 4
#define COLUNAS 1000000

/*
Pretende-se determinar a existência de um determinado número inteiro nas linhas de numa matriz de
números inteiros, em que o número de colunas é muito maior do que o número de linhas. Implemente,
utilizando processos um programa que determine a existência de um determinado número, recebido como
argumento, numa matriz gerada aleatoriamente.
*/

//nr das colunas mt maior que as linhas 


int palheiro[LINHAS][COLUNAS]; 


int main(int argc, char* argv[]){
    int i, j, agulha = atoi(argv[1]); 
    
    palheiro[0][873453] = palheiro[1][6347] = agulha; 
    
    for(i=0; i < LINHAS; i++) {
        pid_t pid = fork(); 
        if(pid == 0){
            for(j=0; j < COLUNAS; j++)
                if(palheiro[i][j] == agulha){
                    puts("encontrei"); 
                    break; 
                }
        }
        _exit(i); 
    }


    for( i= 0; i!=LINHAS; i++)
        wait(NULL); 

}





