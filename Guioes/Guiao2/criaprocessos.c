#include<stdio.h>
#include<unistd.h>


int main(){
	int i, p;
	for(i = 0; i!=10; i++){
		p= fork();
	}
	printf("myPID = %d, son or self = %d\n", getpid(), p); 

	return 0; 
}