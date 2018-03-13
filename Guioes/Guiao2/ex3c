#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h> 

/*
Criar 
*/

int main() {
	int i =0; 
	/*
	
	//por cada itereção exponecializa o nr de filhos
	for(i=0 ; i!=10; i++){
		fork(); 
	}
	
	 */ 

	for(i = 0 ; i != 10; i++){
		if(fork() ==0) {/* filho */
		/*coisas*/
			_exit(i); 
		}
		wait(NULL); //Espera até o filho acabar 
	}
	return 0; 
}