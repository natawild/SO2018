#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LINHAS 16
#define COLUNAS 32
#define MAX_NUM 150
#define MAX_SEARCH 150

/*
Pretende-se determinar a existência de um determinado número inteiro nas linhas de numa matriz de
números inteiros, em que o número de colunas é muito maior do que o número de linhas. Implemente,
utilizando processos um programa que determine a existência de um determinado número, recebido como
argumento, numa matriz gerada aleatoriamente.
*/

//nr das colunas mt maior que as linhas 

 
void procura(int ** mat, int valor){
    int i,j;
    for(i=0; i < LINHAS; i++)
        for(j=0; j < COLUNAS; j++)
            if (mat[i][j] == valor)
                printf("Encontrei Col-> %d Linha-> %d \n",j,i);
}
 
void  criaMat(int *** mat1){
    int **mat;
    srand(time(NULL));
    mat = malloc(LINHAS*sizeof(int*));
 
    int i,j;
    for(i = 0; i < LINHAS; i++){
        mat[i]=malloc(COLUNAS*sizeof(int));
    }
    for(i = 0; i < LINHAS; i++)
        for(j = 0; j < COLUNAS; j++)
            mat[i][j] = rand() % MAX_NUM;
 
    (*mat1) = mat;
}
 
int main(){
 
    int valor, ***mat1, status, **mat;
 
    criaMat(mat1);
    mat = *mat1;
    valor = rand() % MAX_SEARCH;
 
    int i,j;
 
    for(i=0; i < LINHAS; i++) {
        if(!fork()){
            for(j=0; j < COLUNAS; j++)
                if (mat[i][j] == valor) {
                    printf("Encontrei Coluna: %d Linha: %d. Sou o processo com PID %d e o meu pai é %d\n",j,i, getpid(), getppid());
                    _exit(0);
                }
            _exit(0);
        }
    }
    for(i=0; i < LINHAS; i++)
        wait(&status);
}