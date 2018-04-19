#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdlib.h> /* para utilizar o exit */ 
#include <stdio.h> 

#define SIZE 128  

int main(int argc, char * argv[])
{

	char buf[SIZE*2]={0}; 
	int fd, n; 
	char *p=buf; 
	char *p0 =p; 

	int a = SIZE; 
	int l = 1; 
	if(argc ==1)
		fd=0;
	else 
		fd=open(argv[1],O_RDONLY,0); 
		if( fd ==- 1){
			perror("Coul not open file"); 
			exit (-1); 

		}
		while (1){
			if(a < sizeof("%6d " ) + 1){
				p=buf; 
				p0= p; 
				a =SIZE; 
			}
			else{
				n=sprintf(p, "%6d ", l++); 
				p+=n; 
				a-=n; 
			}
			n=read(fd,p,a);
			if(n<0) exit(-1);
			p+=n;
			a-=n;
			if(write(1, p0,p-p0)==-1){
				perror("write \n"); 
				exit (-1); 
			}
			if( n==0) 
				exit (0); 
			p0=p; 
		}	
}