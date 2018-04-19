#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h> 
#include <stdlib.h>

/*
Implemente um programa que crie dez processos filhos que deverão executar (potencialmente) em concorrência. 
O pai deverá esperar pelo fim da execução de todos os seus filhos, imprimindo os respectivos
códigos de saída.
*/


int procura(pid_t p){
  pid_t pids[10]; 
  for (int i = 0; i < 10; ++i)
  {
    if(pids[i]==p) return i; 
  }
  return -1 ; 
}

int main() {
  int res[10]; 
  pid_t pids[10]; 

int i; 
for(i = 0; i < 10; i++){
  pid_t pid = fork(); 
  pids[i] = pid; //array para uso do pai 
  if(!pid){ //sou filho 
    printf("Sou o filho número %d\n", i+1);
    _exit(i+1);
  }
}

  //o pai deve esperar pelo fim da execução de todos os seus filhos 
for(i = 0; i < 10; i++){
    int status; 
    waitpid(pids[i],&status,0); //escolhe por quem esperar 
    //wait(&status); 
    if(WEXITSTATUS(status))
      printf("Filho %d terminou com exit de %d\n", i+1, WEXITSTATUS(status));
}
}
