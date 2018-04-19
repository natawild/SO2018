#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LINHAS 9
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
    int i, j,status,  agulha = atoi(argv[1]); 
    pid_t pid[LINHAS]; 
    
    palheiro[0][873453] = palheiro[1][6347] = agulha; 
    
    for(i=0; i < LINHAS; i++) {
        pid[i] = fork(); 
        int contador = 0; //nr de ocorrencias de agulha no palheiro 
        if(pid[i] == 0){
            for(j=0; j < COLUNAS; j++)
                if(palheiro[i][j] == agulha){
                    contador++; 
                    break; 
                }
             _exit(contador); 
        }
        
    }

    for( i= 0; i!=LINHAS; i++){
        waitpid(pid[i], &status, 0);
        if(WIFEXITED(status)){
            if(WEXITSTATUS(status) > 0 ){
                printf("%d ocorrencias na linha % d\n", WEXITSTATUS(status), i );
            }
        }
        else{
            printf("Erro na pesquisa da linha %d\n", i);
        }
    }
}
