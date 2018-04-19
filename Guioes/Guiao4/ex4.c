#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h> 
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

/*
Escreva um programa redir que permita executar um comando, opcionalmente redireccionando a entrada
e/ou a saída. O programa poderá ser invocado, com:

redir [-i fich_entrada] [-o fich_saida] comando arg1 arg2 ...
*/

int main(int argc, char *argv[]) {

  int fd;
  if(strcmp(argv[1],"-i") == 0) {
           fd=open(argv[2],O_RDONLY,0666);
           dup2(fd,0);
           close(fd);
  	   execvp(argv[2],&argv[3]);
            perror("erro aqui"); 

  }
  else {
        if(strcmp(argv[1],"-o") == 0) {         
            fd=open(argv[2],O_CREAT | O_WRONLY | O_TRUNC,0666);
            dup2(fd,1);
            close(fd);
            execvp(argv[2],&argv[3]);
            perror("erro ola");
          }
          else { printf("erro grave\n");}

       }
      //percorer os argumentos com um for 
       //posso fazer exec[c]

  return 0;
}
