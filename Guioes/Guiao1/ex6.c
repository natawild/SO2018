#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdlib.h> /* para utilizar o exit */ 
#include <stdio.h> 
#include "ex5.h"

#define SIZE 128  

ssize_t readln(int fildes, void *buf, size_t nbyte); 

int main(int argc, char * argv[])
{

	char buf[SIZE]={0};
	char buf2[9]={0};
	int fd, n; 
	int l=1; // contador de linhas 

	if(argc ==1)
		fd=0;
	else {
		fd=open(argv[1], O_RDONLY,0);
		if( fd ==-1){
			perror ("Could not open file"); 
			exit(-1); 
		}
	}

	while( (n = readln(fd,buf,SIZE)) > 0){ 
		if(buf[SIZE-1] == '\n'){
			sprintf(buf2,"%6d ", l++);
			write(1, buf2, sizeof(buf2)-1); 
		}
		write(1, &buf, n); 
		
	}

}