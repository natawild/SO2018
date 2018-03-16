#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char * argv[]) {

	execlp("ls","COISINHO","-l",NULL);
	perror ("Não funcionou");
	return 0;
}