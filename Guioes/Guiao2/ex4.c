#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h> 
#include <stdlib.h>

/*
Implemente um programa que crie dez processos filhos que deverão executar (potencialmente) em concorrência. 
O pai deverá esperar pelo fim da execução de todos os seus filhos, imprimindo os respectivos
códigos de saída.
*/

int main() {
int i, fPid, ret;
for(i = 0; i < 10; i++){
	fPid = fork();
	if(fPid == 0){//sou filho 
		printf("Sou o filho número %i\n",i);
		_exit(i);
	}
	printf("Pai: Criei o filho %d com o PID %d\n",i,fPid);
	}

while((fPid=wait(&ret))!= -1){
	ret=WEXITSTATUS(ret);
	printf("O filho com PID %d devolveu-me %d\n",fPid,ret);
	}
}
