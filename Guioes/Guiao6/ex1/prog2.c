#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char const *argv[]){
	puts("Antes"); 
	int ficheiro = open("fifo",O_WRONLY);
	puts("depois"); 
 	char linha[1024];
    int n;

	while((n=read(0,linha,sizeof(linha+1)))>0){ //enquanto leio caracteres 

			write(ficheiro,linha,n); //escrevo 
     }
     close(ficheiro); 

	return 0;
}