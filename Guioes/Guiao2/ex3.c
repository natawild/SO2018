#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h> 

/*
Implemente um programa que crie dez processos filhos que deverão executar sequencialmente. Para este
efeito, os filhos podem imprimir o seu pid e o do seu pai, e finalmente, terminarem a sua execução com
um valor de saída igual ao seu n´umero de ordem (e.g.: primeiro filho criado termina com o valor 1). O
1
pai deverá imprimir o código de saída de cada um dos seus filhos. Note que só pode imprimir o código de
saída de um filho se este tiver terminado com a invocação (implícita ou explícita) da chamada ao sistema
exit().
*/

// quando se faz _exit() temos a certeza que correu bem 

int main() {
	int i, status; 
	for(i = 0 ; i != 10; i++){
		pid_t pid = fork(); 
		if(pid == 0) {/* filho */
			/*coisas*/
			printf("Meu PID: %d. PID do pai: %d\n", getpid(), getppid());
			printf("Eu sou o processo: %d\n", i);
			_exit(i); 
		}
		wait(&status); //Espera até o filho que o pai criou acabe de executar 
		if(WIFEXITED(status)){
			printf("Pai: status = %d, exit do filho = %d\n",status, WEXITSTATUS(status));	
		}
		else {
			puts("ui... o filho não terminou com exit"); 
		}
		
	}
	return 0; 
}