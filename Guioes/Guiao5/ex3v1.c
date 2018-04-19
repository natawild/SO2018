#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*
Escreva um programa que execute o comando wc num processo filho. O processo pai deve enviar ao
filho através de um pipe anónimo uma sequência de linhas de texto introduzidas pelo utilizador no seu
standard input. Recorra à técnica de redireccionamento estudada no guião anterior de modo a associar
o standard input do processo filho ao descritor de leitura do pipe anónimo criado pelo pai. Recorde a
necessidade de fechar o(s) descritor(es) de escrita no pipe de modo a verificar-se a situação de end of file.

*/

int main(){
  int pd[2];
  char buffer; 
	pipe(pd); 

  pid_t pid;
  pid=fork();

  if(!pid) { //se sou o filho 
    dup2(pd[0],0);
    close(pd[0]); //sem isto o filho não deteta EOF

    execlp("wc","wc",NULL);           
    exit(-1); 
  }
  else {
    while( read( 0, &buffer, 1) == 1){
      write(pd[1], &buffer, 1); 
    }
    close(pd[1]); /*sem isto filho não deteta EOF */
    wait(NULL); 
  }
}
