#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdlib.h> /* para utilizar o exit */ 
#include <stdio.h> 
#include <string.h>

//head 

void imprimeConteudo (char * nome){
	int n; 
	int f = open(nome, O_RDONLY); 
	char buf[1]; 
	int contador=0; 
	//vou ler apenas o numero de linhas que quero a partir do inicio do ficheiro
	while( (n = read(f, &buf, 1)) > 0 && contador<10){ 
		write(1, &buf, n); 
		if(strstr(buf, "\n")!=NULL){//comparar se encontrei a uma mudanca de linha
			contador++; 

		} 
	}
}


int main(int argc, char * argv[]){

	for(int i =1; i<argc; i++){
		imprimeConteudo(argv[i]); 
	}


	exit(1); 
}

