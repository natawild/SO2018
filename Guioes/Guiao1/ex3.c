#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdlib.h> /* para utilizar o exit */ 
#include <stdio.h> 


int main(int argc, char * argv[]){

	int f, n; 
	int buffSize=atoi(argv[1]); 
	char buf[buffSize]; 
	//vou ler o numero de caracteres que forem passados como argumento  
	while( (n = read(0, &buf, buffSize)) > 0){ 
		write(1, &buf, n); 
	}

	exit(n); 

	
}