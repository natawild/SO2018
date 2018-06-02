#include <stdio.h> //printf
#include <string.h> //funções de strings
#include <stdlib.h> //malloc
#include <unistd.h> //fork
#include <sys/wait.h> //
#include "readl.c"


int pdf[2], pdp[2];
int multiplica(int j, int i, char **comando){
	
	if(j==0){
		pipe(pdf);
		pipe(pdp);
	}

	int r=0;
	char buffer[1024];
	int x=fork(), y;
	if(j==i && x==0){ 
		printf("eu %d, cheguei ao ultimo \n", j);
		write(pdf[1],"acabas\0",9);
		close(pdf[1]);close(pdf[0]);
		close(pdp[1]);close(pdp[0]);
		_exit(i);
	}
	if(x==0){
		printf("Processo %d  PID:%d  PPID:%d\n", j, getpid(), getppid());
		multiplica(++j, i, comando);
		printf("oubla\n" );
		dup2(pdp[0],0);
		close(pdp[0]);
		close(pdp[1]);
		
		int k=0;
		char * aux = NULL;
		char **output = NULL;
		output = (char **) malloc(512 * sizeof(char*));
		for (k=0; k<512; k++){
    		output[k] = (char*) malloc( 512 * sizeof(char));
		}

		//printf("O COMANDO:->%s<-\n", comando[(i-j)-1]);
		strcpy(output[0], strtok(comando[(i-j)-1]," "));
		for(k=1; (aux = strtok(NULL," ")) != NULL; k++)
			strcpy(output[k], aux);
		output[k] = NULL;
		//printf("O COMANDO DEPOIS:->%s<-\n", comando[(i-j)-1]);

		/*for(k=0; output[k]!=NULL; k++)
			printf("comando: %s\n", comando[k]);
		printf("comando: %s\n", comando[k]);*/
		
		//printf("Processo %d\n", j);
		if( ((i-j)-1)!=(i-1)){
			printf("entrei aqui no if\n");	
			dup2(pdf[1],1);
			close(pdf[1]);
		}
		execvp(output[0], &output[0]);
		//execvp(comando[(i-j)-1], &comando[(i-j)-1]); 
		_exit(--j);
	}
	else{
		wait(&y);
		close(pdf[1]);
		close(pdp[0]);
		printf("JUST LEAVED %d\n", WEXITSTATUS(y));
		int q=0;
		while((r=read(pdf[0], buffer, 1024))>0){
			printf("%s\n", buffer);
			write(pdp[1], buffer, r); //coloca a linha lida no array output 
			//printf("POSIÇÃO: %d\n", cmdpos);
			//printf("TAMANHO DA STRING DOS OUTPUTS: %d\n", size(n->arrayCmd[cmdPos]->output));
		}
		printf("O Processo %d saiu\n", WEXITSTATUS(y));
	}
}


int main(int argc, char*argv[]){
	char string[100] ="ls -l | cal | date";
	char * aux = NULL;
	int x;
	int i=0, j=0;
	char **comando = NULL; //array de strings, onde cada uma é um comando do comando
	comando = (char **) malloc(512 * sizeof(char*));
	for (i=0; i<512; i++){
    	comando[i] = (char*) malloc( 512 * sizeof(char));
	}


	strcpy(comando[0], strtok(string,"|"));
	for(i=1; (aux = strtok(NULL,"|")) != NULL; i++)
		strcpy(comando[i], aux);
	comando[i] = NULL;

	
	/**for(i=0; i<2; i++)
		printf("comando: %s\n", comando[i]);
	printf("comando: %s\n", comando[i]);*/

	multiplica(0, i, comando);

	return 0;
}