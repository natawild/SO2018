#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdlib.h> /* para utilizar o exit */ 
#include <stdio.h> 
#include <string.h>

int numeroDeLinhas(char * buf, int tamanho){
	int i, n=0;
	for(i=0; i<tamanho; i++){
		if(buf[i]=='\n'){
			n++;
		}
	}
	return n;
}

void imprimeConteudo (char * nome){
	int n; 
	int f = open(nome, O_RDONLY); 
	char buf[20]; 
	int contador= 0; 
	char *res; 
	//vou ler o numero de caracteres que forem passados como argumento  
	while( (n = read(f, &buf, 20)) > 0 && contador<10){ 
		if(strstr(buf, "\n")!=NULL){
			contador += numeroDeLinhas(buf, n); //dentro dos 20 bytes a ler é possivel encontrar mais de um \n por isso é necessário acrescentar o valor 
			res=strstr(buf, "\n");
			if(contador == 10){
				int position = res - buf;
				write(1, &buf, position+1); 
			}
			else {
				write(1, &buf, n); 
			}
		} 
		else {
			write(1, &buf, n); 
		}
	}
}


int main(int argc, char * argv[]){

	for(int i =1; i<argc; i++){
		imprimeConteudo(argv[i]); 
	}

	exit(1); 
}


