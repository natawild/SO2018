#include <stdio.h> //printf function
#include <fcntl.h> //open function
#include <unistd.h> //read and write, lseek functions
#include <sys/types.h> //lseek function 
#include <sys/wait.h> //wait function
#include <stdlib.h> //strtol fucntion
#include <string.h>
#include <signal.h> //para fazer o sigkill
#include "parser.h"
#include "struct.h"
#include "readl.h"

int isEmpty(char *string){
	int i, r=0;
	if(string[0]=='$'){
		for(i=0; string[i]!=' '; i++);
		i++;
		for(; string[i]!='\0'; i++)
			r++;
		return r;
	}
	return r; 
}

int containsPipes(char *nome){
	int i, c=0;
	for(i=0; nome[i]!=' '; i++);
	for(; nome[i]!='\0'; i++)
		if(nome[i]=='|') c++;
	return c;
}

int seeDepends(char *nome){
	int depends = 0;
	if(nome[0]==' ')
		return depends;
	if(nome[0]=='|')
		return depends=1;	
	depends = strtol(nome, &nome, 10);
		return depends;
}

void sig_handlerPai(){
	//_exit(1);
}

void sig_handlerFilho(){
	_exit(1);
}

Notebook parser(Notebook n, char *argv){
	signal(SIGINT, sig_handlerPai);
	int fnb, fe; //descritor do ficheiro notebook.nb e do erros.nb
	int i=0, j=0; //variável de iteração do while
	int r; //número de bytes lidos pelo readln 
	int x, y; // retorno do fork
	int z; //para o wait do pai
	int pd[2]; //descritores do pipe
	int pda[2]; //descritores de um pipe entre filho e filho do filho
	char descricao[1024]; //string da descricao
	char nome[1024]; //string do nome
	char output[1024]; //string do output
	char erro[1024]; //buffer do ficheiro erros
	int depends; 

	fe = open("erros.nb", O_CREAT | O_RDWR | O_TRUNC, 0666);
	if(fe<0){
		perror("O ficheiro erros.nb não foi aberto.\n");
		_exit(1);
	}
	dup2(fe,2);
	close(fe);

	fnb = open(argv, O_RDONLY | O_RDWR);
	if(fnb<0){
		perror("O ficheiro notebook.nb ou erros.nb não foi aberto.\n");
		_exit(1);
	}

	// a cada iteração são lidos o nome e a descrição de um comando
	while(readln(fnb, descricao, 1024)>0 && 
		readln(fnb, nome, 1024)>0){

		if(0==strcmp(descricao, ">>>") &&  0!=strcmp(nome, "<<<")){
			while (0!=strcmp(descricao, "<<<"))
				r=readln(fnb, descricao, 1024);
			r=readln(fnb, descricao, 1024);
			r=readln(fnb, nome, 1024);
			if (r<=0)
				break; 
		}		

		//isto nunca vai acontecer, mas fica aqui de prevenção, caso nao seja impresso nenhum output
		if(0==strcmp(descricao, ">>>") &&  0==strcmp(nome, "<<<")){
			r=readln(fnb, descricao, 1024);
			r=readln(fnb, nome, 1024);
			if (r<=0)
				break; 
		}

		if(0==isEmpty(nome)){
			perror("O ficheiro notebook.nb não corresponde ao formato pedido.\n");
			_exit(1);
		}

		//se notebook.nb não estiver direito
		if(descricao[0]=='$' || nome[0]!='$'){
			perror("O ficheiro notebook.nb não corresponde ao formato pedido.\n");
			_exit(1); //void * para não dar warning de passar de intp para apontador
		}

		depends = seeDepends(&nome[1]);

		if(depends>i){
			perror("Um comando depende de outro que é inexistente.\n");
			_exit(1);
		}	

		if(containsPipes(nome) == 0){ //Se não existem | no input entre argumentos

			insereNotebook(n, descricao, nome, depends); //insere no notebook n, o nome, a descricao lidos e a dependencia
			pipe(pd); //criamos um pipe para passar informacao do pai para o filho
			x = fork(); //criamos um filho para executar o exec
			if(x==0){
				signal(SIGINT, sig_handlerFilho);
				close(pd[0]); //.. pois o filho só irá escrever no pipe
				dup2(pd[1], 1); //o stdout passa a ser o pipe  
				close(pd[1]); //o stdout já foi redirecionado para o stdout, tornando-se desnecessário

				if(depends==0){
					execvp(getComandoArgs(n, i)[0], &getComandoArgs(n, i)[0]);
					perror("Um comando não pode ser executado.\n");//caso o exec não tenha sido feito
					//kill(getppid(), SIGKILL); //envia um sinal para matar o processo pai e abortar a alteração do notebook
					_exit(1);
				}
			
				if(depends!=0){
					pipe(pda);		
					y = fork();
					if(y==0){
						close(pda[0]);
						for(j=0; (getComandoOutput(n,(i-depends))[j])!=NULL; j++){
							write(pda[1], getComandoOutput(n, (i-depends))[j], strlen(getComandoOutput(n, (i-depends))[j]));
							write(pda[1], "\n", 1);
						}
						write(pda[1], getComandoOutput(n, (i-depends))[j], 1024);
						close(pda[1]);
						_exit(1);
					}

					close(pda[1]);
					dup2(pda[0], 0);
					
					execvp(getComandoArgs(n, i)[1], &getComandoArgs(n, i)[1]);
					perror("Um comando não pode ser executado.\n");//caso o exec não tenha sido feito
					//kill(getppid(), SIGKILL);//envia um sinal para matar o processo pai e abortar a alteração do notebook
					wait(NULL);
					_exit(1);
					
				}

				_exit(1);
			}
			
			close(pd[1]); // ... pois o pai só irá ler do pipe
			//neste while lemos uma linha do pipe em cada iteraçao
			j=0;
			while(readln(pd[0], output, 1024)>0){
				setComandoOutput(n, output, i, j++); //coloca a linha lida no array output 
				//printf("POSIÇÃO: %d\n", cmdpos);
				//printf("TAMANHO DA STRING DOS OUTPUTS: %d\n", size(n->arrayCmd[cmdPos]->output));
			}

			setComandoOutput(n, (char *)NULL, i, j);//colocamos a ultima posição deste array a NULL
			close(pd[0]); //... pois já nao precisamos dele
			
			wait(&z);
			//if(1==WEXITSTATUS(z))
			//	_exit(1); //o processo pai para se houver algum erro nos execs

		}
		//else{

		//}		

		i++;
	}
	
	lseek(2, 0, SEEK_SET);
	if((readln(2, erro, 1024))<=0)
		unlink("erros.nb");
	lseek(2, 0, SEEK_END);
	
	return n;
}