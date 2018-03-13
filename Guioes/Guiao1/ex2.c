#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdlib.h> /* para utilizar o exit */ 
#include <stdio.h> 

#define DEZMEGA 1024*1024*10 


int main(int argc, char *argv[])
{
	char ch = 'a';
	int c= 0;
	int fd;
	fd = open(argv[1], O_CREAT | O_WRONLY, 0744); 
	if(fd ==-1){
		perror ("Não consigo abrir o ficheiro"); 
		exit(-1);
	}

	while(c++ < DEZMEGA){
		write(fd, &ch, 1);  
	}

	close(fd); 
	exit(0); 

}

	