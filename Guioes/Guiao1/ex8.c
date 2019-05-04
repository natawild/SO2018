#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdlib.h> /* para utilizar o exit */ 
#include <stdio.h> 


void imprimeConteudo (char * nome){
	int n; 
	int f = open(nome, O_RDONLY); 
	char buf[1024]; 
	//vou ler o numero de caracteres que forem passados como argumento  
	while( (n = read(f, &buf, 1024)) > 0){ 
		write(1, &buf, n); 
	}
}

int main(int argc, char * argv[]){

	for(int i =1; i<argc; i++){
		imprimeConteudo(argv[i]); 
	}

	exit(0);
	
}

