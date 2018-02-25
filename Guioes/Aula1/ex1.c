#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdlib.h> /* para utilizar o exit */ 
#include <stdio.h> 


int main()
{

	int f, n; 
	char buf; 

	while( (n = read(0,&buf,1)) > 0){ 
		write(1, &buf, 1); 
	}

	_exit(0);

	
}