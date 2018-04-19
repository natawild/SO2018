#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h> 
#include <stdlib.h>
#include <fcntl.h>

int main() {
	int fd; 
	char c; 
	fd=open("/etc/passwd", O_RDONLY); 
	if(fd==-1 ){
		perror("Erro ao abrir /etc/passwd"); 
		_exit(-1);
	}
	//fd = 3, mas não temos de saber usa-se o resultado do open 
	//Descritor 3 foi copiado para o stdout e por isso 
	//há 2 descritores a permitir acesso ao mesmo ficheiro 
	dup2(fd,1); 
	//Vamos fechar o que não precisamos 
	close(fd); 

	fd=open("saida.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    dup2(fd,1);
    close(fd);

	int fp2 = open("erros.txt",O_CREAT | O_WRONLY | O_TRUNC,0666);
    dup2(fp2,2);
    close(fp2);
 
    while(read(0,&c,1) == 1) {
        write(1,&c,1);
        write(2,&c,1);
	}

	//Vamos imprimir para o stand output 
	printf("Olá meus amigos lindos\n");

	
}
