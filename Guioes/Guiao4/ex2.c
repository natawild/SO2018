#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

/*
Modifique o programa anterior de modo a que, depois de realizar os redireccionamentos, seja criado um
novo processo que realize operaçoes de leitura e escrita. Observe o conteudo dos ficheiros. Repare que o
processo filho “nasce” com as mesmas associaçoes de descritores de ficheiros do processo pai

*/

int main(int argc, char *argv[]){
    int fd = open("/etc/passwd",O_RDONLY);
    char c;
    if(fd == -1) { 
      perror ("Erro ao abrir /etc/passwd") ; 
      _exit(-1);
    }
    dup2(fd,0);
    close(fd);
   
    fd=open("saida.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    if(fd == -1) { 
      perror ("Erro ao abrir saida.txt") ; 
      _exit(-1);
    }
    (fd,1);
    close(fd);

    int fp2=open("erros.txt",O_CREAT | O_WRONLY | O_TRUNC,0666);
    if(fd == -1) { 
      perror ("Erro ao abrir erros.txt") ; 
      _exit(-1);
    }
    dup2(fp2,2);
    close(fp2);
    if(fork()==0){//SE SOU FILHO 
      while(read(0,&c,1)==1) {
        write(1,&c,1);
        write(2,&c,1); 
      }

    puts("ola");
    
    }
return 0; 
}
