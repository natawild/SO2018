#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h> 

int main() {
	printf(" Meu pid = %d, ppid = %d\n", getpid(), getppid());
	_exit(0); 
}