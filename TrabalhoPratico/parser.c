#include <stdio.h> //printf function
#include <fcntl.h> //open function
#include <unistd.h> //read funciton
#include <sys/wait.h> //wait function
#include "parser.h"
#include "struct.h"
#include "readl.h"

Notebook parser(Notebook n, char *argv){
	int fnb; //descritor do ficheiro notebook
	int i=0,j=0; //variável de iteração do while
	int x; // retorno do fork
	int pd[2]; //descritores do pipe

	char descricao[1024]; //string da descricao
	char nome[1024]; //string do nome
	char output[1024][1024]; //string do output

	fnb = open(argv, O_RDONLY | O_RDWR);

	while(readln(fnb, descricao, 1024)>0 && 
		readln(fnb, nome, 1024)>0){
		
		//se notebook.nb não estiver direito
		if(descricao[0]=='$' || nome[0]!='$'){
			printf("O ficheiro notebook.nb não corresponde ao formato pedido.\n");
			return (void *)(-1); //void * para não dar warning de passar de intp para apontador
		}

		insereNotebook(n,descricao,nome,i);
		
		if(nome[0]=='$'){
			pipe(pd);
			x = fork();
			if(x==0){
				close(pd[0]); //o filho só irá escrever no pipe
				//dup2(pd[1], 1); //o stdout passa a ser o pipe  
				close(pd[1]); //o stdout já foi redirecionado para o stdout, tornando-se desnecessário
				execvp(getComandoTeste(n, i)[0], &getComandoTeste(n, i)[0]);
				_exit(0);
			}
			wait(NULL);
			close(pd[1]); // o pai só irá ler do pipe
			close(pd[0]);
			/*while(readln(pd[0], output[j], 1024)>0){
				write(1, output[j], 1024);
				printf("\n");
			}*/
			return 0;
			

		}

		i++;
	}

	return n;
}
