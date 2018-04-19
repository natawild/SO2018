#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LINHAS 4
#define COLUNAS 1000000
#define MAX_NUM 1500000

/*
Pretende-se determinar a existência de um determinado número inteiro nas linhas de numa matriz de
números inteiros, em que o número de colunas é muito maior do que o número de linhas. Implemente,
utilizando processos um programa que determine a existência de um determinado número, recebido como
argumento, numa matriz gerada aleatoriamente.
*/

//nr das colunas mt maior que as linhas 


int palheiro[LINHAS][COLUNAS]; 

int main(int argc, char* argv[]){
    int contaOcorrencias =0; 
    int status; 
    int i, j; 
    int agulha = atoi(argv[1]); 
    srand(time(NULL));
    for(i=0; i < LINHAS; i++) {
        for(j=0; j < COLUNAS; j++){
          palheiro[i][j] = rand() % MAX_NUM; 
          //printf("MATRIZ: %d\n", palheiro[i][j]);
        }
    }
    
    for(i=0; i < LINHAS; i++) {
        pid_t pid = fork(); 
        if(pid == 0){//se sou filho
            for(j=0; j < COLUNAS; j++){
                if(palheiro[i][j] == agulha){
                    contaOcorrencias++; 
                    printf("Encontrei o numero %d na linha %d coluna %d \n", agulha, i, j);
                    exit(contaOcorrencias); 
                }
            }
        }
    }

    for(i=0; i<LINHAS; i++){
        wait(&status);
        contaOcorrencias += WEXITSTATUS(status);
        printf("Encontrei %d\n", contaOcorrencias);
    }

}






