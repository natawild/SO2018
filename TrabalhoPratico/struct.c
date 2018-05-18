#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "struct.h"

struct comando{
   char  *descricao; //descrição do comando
   char  *nome; //comando
   int depends;
   //char *output; //output do comando
}; 

/*array de apontadores para uma estrutura em que
cada posição terá uma estrutura comando*/
struct notebook{
	int size; //tamanho do array
	int used; //quantas posições do array estão usadas
	Comando *arrayCmd;
};

Comando initComando(){
	Comando c = malloc(sizeof(struct notebook));
	c -> descricao = (char *) malloc(512 * sizeof(char));
	c -> nome = (char *) malloc(512 * sizeof(char));
	c -> depends = 0;
	return c;
}

Notebook initNotebook(int size){
	Notebook n = malloc(sizeof(struct notebook));
	n->size = size;
	n->used = 0;
	n->arrayCmd = malloc(size*sizeof(struct comando)); 
	return 	n;
}

int insereNotebook(Notebook n, char *descricao, char *nome, int depends){
	if (n->used == n->size){
		n->arrayCmd = realloc(n->arrayCmd, 2*(n->size)*sizeof(struct comando));
		n->size =(n->size)*2;
	}

	Comando cmd = initComando();
	n->arrayCmd[n->used] = cmd;
	strcpy(n->arrayCmd[n->used]->descricao, descricao);
	strcpy(n->arrayCmd[n->used]->nome, nome);
	n->arrayCmd[n->used]->depends = 0;
	(n->used)++;
	return 0;	
}

int printNotebook(Notebook n){
	int i;
	for(i=0; i < (n->used); i++){
		printf("size: %d\n", n->size);
		printf("used: %d\n", n->used);
		printf("descricao: %s\n", n->arrayCmd[i]->descricao);
		printf("descricao: %s\n", n->arrayCmd[i]->nome);
		printf("dependencias: %d\n", n->arrayCmd[i]->depends);
		printf("------------\n");
	}
	return 0;	
}

/*Gets e Sets*/
int getNotebookSize(Notebook n){
 	int size = n->size; 
	return size;
}

int getNotebookUsed(Notebook n){
 	int used = n->used; 
	return used;
}

char *getComandoDescricao(Notebook n, int i){
 	char * descricao = malloc(512 * sizeof(char));
 	strcpy(descricao, n->arrayCmd[i]->descricao);
	return descricao;
}

char *getComandoNome(Notebook n, int i){
 	char * nome = malloc(512 * sizeof(char));; 
 	strcpy(nome, n->arrayCmd[i]->nome);
	return nome;
}

int getComandoDepends(Notebook n, int i){
 	int depends = n->arrayCmd[i]->depends; 
	return depends;
}