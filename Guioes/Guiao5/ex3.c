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
  int n;
  char buffer[1024];

	if(pipe(pd) == -1) {
    perror("pipe"); return 1;
  }

  pid_t pid;
  pid=fork();

  if(pid == 0) { //se sou o filho 
    close(pd[1]); /* como o filho nao vai precisar de escrever podemos fechar essa opcao */
    dup2(pd[0],0);
    close(pd[0]);
    execlp("wc","wc",NULL);           
    perror("execpl");
    return 1;
  }
  else {
    if(pid == -1) {
      perror("fork"); 
      return 1;
    }

    else {
      close(pd[0]); /*como o pai nao vai ler podemos fechar esta opcao */
      while((n = read( 0, buffer, sizeof(buffer))) > 0){
        write(pd[1], buffer, n); //escreve 
      }
      close(pd[1]);

    }        
  }
return 0;
}
