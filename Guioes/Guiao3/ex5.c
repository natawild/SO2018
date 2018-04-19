#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>


/*
Implemente um programa que execute concorrentemente uma lista de executáveis especificados como
argumentos da linha de comando. Considere os executáveis sem quaisquer argumentos próprios. O
programa deverá esperar pelo fim da execução de todos processos por si criados.
*/


//argv recebe argumentos 
int main(int argc, char * argv[]) {

  pid_t filho;
  int values [argc];
  int i;
  int crianca[argc];

  //Vamos criar tantos filhos quantos os argumentos 
  for (i=1; i < argc; i++) {
       filho=fork();
              if(filho == 0) { 
                    //exelp(argv[i], argv[i], NULL); 
                    execvp(argv[i],&argv[i]);
                    perror("Não funciona");  
                    _exit(127);//nao consegui executar o programa
                   }
   				     else {
   					      crianca[i-1]=filho; //
   				     }
  }

  for (i = 0;i < argc; i++) {
    wait(NULL); 
    //waitpid(crianca[i],&values[i],0); //espera pelo fim de execução dos processos criados 
  }

  return 0;
}