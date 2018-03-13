#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdlib.h> /* para utilizar o exit */ 
#include <stdio.h> 


int main()
{

	int f, n; 
	char buf; 

	f= open("/etc/passwd", O_RDONLY); 
	if( f==-1){
		perror ("erro no acesso à password"); 
		exit(-1); 
	}
	while( (n = read(f,&buf,1)) > 0){ 
		write(1, &buf, 1); 
	}

	if(n== -1){

		perror ("erro no read"); 
		exit(-1); 
	} else exit(0); 

	
}