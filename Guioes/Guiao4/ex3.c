#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

/*
Modifique novamente o programa inicial de modo a que seja executado o comando wc, sem argumentos,
depois do redireccionamento dos descritores de entrada e saáda. Note que, mais uma vez, as associaçoes
– e redireccionamentos – de descritores de ficheiros sao preservados pela primitiva exec().
*/

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
    execlp("wc","wc","-l",NULL);
	perror("Erro no wc");

	//Vamos imprimir para o stand output 
	printf("Olá meus amigos lindos\n");

}