#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*
Escreva um programa que emule o funcionamento do interpretador de comandos na execução encadeada
de grep -v ˆ# /etc/passwd | cut -f7 -d: | uniq | wc -l.
*/

int main(int argc, char  *argv[]){
   int pid1[2];
   int pid2[2];
   int pid3[2];
   int i = 0;

   pid_t pide;
   
   if(pipe(pid1) == -1) {
   		perror("pipe1"); 
   		return 1;
   	}

	pide=fork();
  
    if(pide == 0){//se sou filho 	
		if(pipe(pid2) == -1) {
			perror("pipe2"); 
			return 1;
		}	

		pide=fork();

		if(pide == 0) {
			if(pipe(pid3) == -1) {
				perror("pipe3"); 
				return 1;
			}
			pide=fork();
			if(pide == 0) {
				//dup2(pid3[0],0);
				dup2(pid3[1],1);
				close(pid3[0]);
				close(pid3[1]);
				close(pid2[0]);
				close(pid2[1]);
				close(pid1[0]);
				close(pid1[1]);
				execlp("grep","grep","-v","^#","/etc/passwd",NULL);
				//execlp("cat","cat",NULL);
				perror("grep");
				return 1;
			}
			else {

				dup2(pid3[0],0);
            	dup2(pid2[1],1);
				close(pid3[0]);
				close(pid3[1]);
				close(pid2[0]);
				close(pid2[1]);
				close(pid1[0]);
				close(pid1[1]);

				execlp("cut","cut","-f7","-d:",NULL);
				//execlp("cat","cat",NULL);
				perror("cut");
				return 1;	
			}
		}
		else {
				dup2(pid2[0],0);
				dup2(pid1[1],1);
       			close(pid2[0]);
       			close(pid2[1]);
       			close(pid1[0]);
       			close(pid1[1]);
       			execlp("uniq","uniq",NULL);
       			//execlp("cat","cat",NULL);

       			perror("uniq");		
       			return 1;	
		} 
 	}
  	else {

  		dup2(pid1[0],0);
      	close(pid1[0]);
       	close(pid1[1]);
       	execlp("wc","wc","-l",NULL);
       	perror("wc");
       	return 1;
  	}
	return 0;
}