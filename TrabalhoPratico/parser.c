#include <stdio.h> //printf function
#include <fcntl.h> //open function
#include <unistd.h> //read funciton
#include <sys/wait.h> //wait function
#include <stdlib.h> //strtol fucntion
#include <string.h>
#include "parser.h"
#include "struct.h"
#include "readl.h"

int containsPipes(char *nome){
	int c=0;
	for(int i=0; nome[i]!='\0'; i++)
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

Notebook parser(Notebook n, char *argv){
	int fnb; //descritor do ficheiro notebook
	int i=0, j=0; //variável de iteração do while
	int x, y; // retorno do fork
	int pd[2]; //descritores do pipe
	int pda[2]; //descritores de um pipe entre filho e filho do filho
	char descricao[1024]; //string da descricao
	char nome[1024]; //string do nome
	char output[1024]; //string do output
	int depends; 

	fnb = open(argv, O_RDONLY | O_RDWR);

	// a cada iteração são lidos o nome e a descrição de um comando
	while(readln(fnb, descricao, 1024)>0 && 
		readln(fnb, nome, 1024)>0){
		
		//se notebook.nb não estiver direito
		if(descricao[0]=='$' || nome[0]!='$'){
			printf("O ficheiro notebook.nb não corresponde ao formato pedido.\n");
			return (void *)(-1); //void * para não dar warning de passar de intp para apontador
		}

		depends = seeDepends(&nome[1]);

		if(depends>i){
			printf("O comando <%s> depende de outro que é inexistente.\n", nome);
			return (void *)(-1);
		}	

		if(containsPipes(nome) <= 1){


			insereNotebook(n, descricao, nome, depends); //insere no notebook n, o nome, a descricao lidos e a dependencia
			pipe(pd); //criamos um pipe para passar informacao do pai para o filho
			x = fork(); //criamos um filho para executar o exec
			if(x==0){
				close(pd[0]); //.. pois o filho só irá escrever no pipe
				dup2(pd[1], 1); //o stdout passa a ser o pipe  
				close(pd[1]); //o stdout já foi redirecionado para o stdout, tornando-se desnecessário

				if(depends==0){
					execvp(getComandoArgs(n, i)[0], &getComandoArgs(n, i)[0]);
				}
			
				if(depends!=0){
					pipe(pda);		
					y = fork();
					if(y==0){
						close(pda[0]);
						for(j=0; (getComandoOutput(n,(i-depends))[j])!=NULL; j++){
							write(pd[1], getComandoOutput(n, (i-depends))[j], strlen(getComandoOutput(n, (i-depends))[j]));
							write(pd[1], "\n", 1);
						}
						write(pda[1], getComandoOutput(n, (i-depends))[j], 1024);
						close(pda[1]);
						_exit(-1);
					}

					wait(NULL);
					close(pda[1]);
					char buf[1024];
					int r;
					dup2(pda[0], 0);
					/*while((r=read(0, buf, 1024))>0){
						printf("%s\n", buf);
					}*/
					close(pda[0]);
					if(depends==1)
						execvp(getComandoArgs(n, i)[0], &getComandoArgs(n, i)[0]);
					else
						execvp(getComandoArgs(n, i)[1], &getComandoArgs(n, i)[1]);
				}

				_exit(0);
			}
			wait(NULL);
			close(pd[1]); // ... pois o pai só irá ler do pipe
			//neste while lemos uma linha do pipe em cada iteraçao
			j=0;
			while(readln(pd[0], output, 1024)>0){
				setComandoOutput(n, output, i, j++); //coloca a linha lida no array output 
			}
			setComandoOutput(n, (char *)NULL, i, j);//colocamos a ultima posição deste array a NULL
			close(pd[0]); //... pois já nao precisamos dele
		}		

		i++;
	}

	return n;
}
