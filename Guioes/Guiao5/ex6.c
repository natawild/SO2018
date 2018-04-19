#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*
Implemente uma função semelhante ao popen(), mas que em vez de retornar um valor do tipo FILE *,
retorne o descritor apropriado do descritor de um pipe anónimo. Nota: se desejar pode converter um
descritor num endereço de uma estrutura FILE usando para o efeito a função fdopen(). Reflicta sobre
a necessidade da função pclose() da biblioteca de C e como poderia proceder para suportar essa
funcionalidade.

FILE *fdopen(int fildes, const char *mode);

//criar um pipe anonimo antes de fazer fork e exec 
int fd = mypopen("ls", "r"); 
while(){
	read(fd); 
	write(); 
}

es = pclose(FILE * )
myclose(int); 
*/


FILE *mypopen(const char *file, const char **argv){
	int pid;
	int fildes[2];

	if(pipe(fildes))//criar o pipe 
		return NULL;

	pid = fork(); //fazer fork
	if(pid == -1) {
		return NULL;
	} 
	else if(! pid) {
		close(fildes[1]);
		dup2(fildes[0], fileno(stdout));
		execvp(file, argv);
	} else {
		close(fildes[0]);
		return fdopen(fildes[1], "r");
	}
}

int main(int argc, char **argv){
	FILE *file;
	const char *args[3] = {"ls", "r", NULL};
	int inchar;

	file = mypopen("ls", args);
	if(! file) {
		return 1;
	} else {
		inchar = fgetc(file);
		while(inchar != EOF) {
			fputc(inchar, stdout);
			inchar = fgetc(file);
		}
	fclose(file);
	}
	return 0;
}