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

int seg=0; 
int n=0; 

void sec (int s){
	seg++; 
	printf("pid/sec= %d:%d\n",n, seg);
	alarm(1); 
}

int main(){
	n=getpid();
	signal(SIGALRM, sec); 
	alarm(1); 
	while(1) pause(); 
}