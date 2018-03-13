#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h> 

/*
Criar 
*/

int main() {
	int i =0; 
	/*
	
	//por cada iteração exponencializa o nr de filhos, aqui não ia ter 10 processos, mas sim muitos 
	for(i=0 ; i!=10; i++){
		fork(); 
	}
	*/ 

	for(i = 0 ; i != 10; i++){
		if(fork() == 0) {/* filho */
			/*coisas*/
			printf("Eu sou o processo: %d\n", i);
			_exit(i); 
		}
		wait(NULL); //Espera até o filho acabar 
		printf("Meu PID: %d. PID do pai: %d\n", getpid(), getppid());
	}
	return 0; 
}