#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>

int segundos=0;
int controlcs=0;
int n= 0;

void sec (int s){
	segundos++; 
	alarm(1); 
}

void f(int signal) {
	switch(signal) {
		case SIGINT: //caso clique em control c : INTR
			controlcs++;
			printf("Tempo em segundos:  %d\n",segundos );
			break;
		case SIGQUIT: //caso clique em control \ : QUIT
			printf("Numero de control ^c = %d\n",controlcs );
			_exit(0);
			break;
	}
}


int main(int argc, char const *argv[]){
	signal(SIGINT,f);
	signal(SIGQUIT,f);
	signal(SIGALRM,sec);
	alarm(1);
	while(1) pause();
	return 0;
}


