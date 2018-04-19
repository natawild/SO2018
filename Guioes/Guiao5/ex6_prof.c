#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


int myopen(char* cmd, char* modo){

	if(!cmd || !modo){ 
		return -1; 
	}
	int m; 
	if(!strcmp(modo, "r")){
		m=0; 
	}
	else if(!strcmp(modo, "w")){
		m=1; 
	}
	else return -1; 

	int fd[2]; 
	pipe(fd);
	if(!fork()){//se sou o filho 
		dup2(fd[1-m], 1-m);
		close(fd[0]); 
		close(fd[1]); 
		execlp(cmd, cmd, NULL); //ASSUME Que não há argumentos 
		_exit(1); 
	} 
	close(fd[1-m]); //fecho o que não me interessa 
	return fd[m]; 
}

int main(int argc, char  *argv[]){
	
	int fd = mypopen("ls", "r"); 


}
