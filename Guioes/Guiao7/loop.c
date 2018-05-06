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


void loop (){
	for(long i =0; i< 10000000; i++)
}

int main(){
	
	char * name = argv[0] +2; 
	int n = atoi(nome); 
	for(int i =0; i<n ; i++){
		printf("%s\n", name);
		loop(); 
	}
}