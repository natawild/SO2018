#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "struct.h"

#define LEN 512


struct comando{
   char  *descricao; //linha do notebook com a descrição do comando
   char  *nome; //linha do notebook que tem o nome do comando
   char **args; //array de strings, onde cada uma é um argumento do comando
   int otSize;
   char **output; //array de strings, onde cada uma é um output do comando
   int depends; //depends é o nº de comando do qual deve retirar o output, contado desde o comando atual para trás
}; 

/*array de apontadores para uma estrutura em que
cada posição terá uma estrutura comando*/
struct notebook{
	int size; //tamanho do array
	int used; //quantas posições do array estão usadas
	Comando *arrayCmd; //array de apontadores para structs do tipo Comando
};

Comando initComando(){
	int i;
	Comando c = malloc(sizeof(struct comando));
	c -> descricao = (char *) malloc(LEN * sizeof(char));
	c -> nome = (char *) malloc(LEN * sizeof(char));
	c -> args = (char **) malloc(LEN * sizeof(char*));
	for (i=0; i<LEN; i++){
    	(c->args)[i] = (char*) malloc( LEN * sizeof(char));
	}
	c->otSize = LEN;
	c -> output = (char **) malloc(LEN * sizeof(char*));
	for (i=0; i<LEN; i++){
    	(c->output)[i] = (char*) malloc( LEN * sizeof(char));
	}
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
	int i=0;
	char *aux = NULL;
	if (n->used == n->size){
		n->arrayCmd = realloc(n->arrayCmd, 2*(n->size)*sizeof(struct comando));
		n->size =(n->size)*2;
	}

	Comando cmd = initComando();
	n->arrayCmd[n->used] = cmd;
	strcpy(n->arrayCmd[n->used]->descricao, descricao);
	strcpy(n->arrayCmd[n->used]->nome, nome);
	strcpy(n->arrayCmd[n->used]->args[i++], strtok(nome," $"));//se o nome tiver uma dependencia a posição 0 terá o comando, se tiver mais que uma a posicao 0 terá o nr de dependencias 
	while( (aux = strtok(NULL," $|")) != NULL)
		strcpy(n->arrayCmd[n->used]->args[i++], aux);
	n->arrayCmd[n->used]->args[i] = NULL;   	
	n->arrayCmd[n->used]->depends = depends;
	(n->used)++;
	return 0;		
}

int printNotebook(Notebook n){
	int i, j;
	for(i=0; i < (n->used); i++){
		printf("size: %d\n", n->size);
		printf("used: %d\n", n->used);
		printf("descricao: %s\n", n->arrayCmd[i]->descricao);
		printf("nome: %s\n", n->arrayCmd[i]->nome);
		printf("args:  ");
		for(j=0; (n->arrayCmd[i]->args[j])!=NULL; j++)
			printf("[%d] %s -- ", j, n->arrayCmd[i]->args[j]);
		printf("\n");
		printf("Size outputs: %d\n", n->arrayCmd[i]->otSize);
		printf("outputs:  ");
		for(j=0; n->arrayCmd[i]->output[j]!=NULL; j++)
			printf("[%d] %s -- ", j, n->arrayCmd[i]->output[j]);
		printf("\n");
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

char *getComandoDescricao(Notebook n, int cmdPos){
 	char * descricao = malloc(LEN * sizeof(char));
 	strcpy(descricao, n->arrayCmd[cmdPos]->descricao);
	return descricao;
}

char *getComandoNome(Notebook n, int cmdPos){
 	char * nome = malloc(LEN * sizeof(char));; 
 	strcpy(nome, n->arrayCmd[cmdPos]->nome);
	return nome;
}

char **getComandoArgs(Notebook n, int cmdPos){
	int j;
 	char **args = malloc(LEN * sizeof(char*));
 	for (j=0; j<LEN; j++){
    	args[j] = (char*) malloc( LEN * sizeof(char));
	} 
 	for(j=0; (n->arrayCmd[cmdPos]->args[j])!=NULL; j++){
 		strcpy(args[j], n->arrayCmd[cmdPos]->args[j]);
 	}

 	args[j]=NULL;
 	
	return args;
}

char **getComandoOutput(Notebook n, int cmdPos){
 	int j;
 	char **output = malloc(LEN * sizeof(char*));
 	for (j=0; j<LEN; j++){
    	output[j] = (char*) malloc( LEN * sizeof(char));
	} 
 	for(j=0; (n->arrayCmd[cmdPos]->output[j])!=NULL; j++)
 		strcpy(output[j], n->arrayCmd[cmdPos]->output[j]);
 	
 	output[j]=NULL;
 	
	return output;
}

int getComandoDepends(Notebook n, int cmdPos){
 	int depends = n->arrayCmd[cmdPos]->depends; 
	return depends;
}

void setComandoDescricao(Notebook n, char *descricao, int cmdPos){
 	strcpy(n->arrayCmd[cmdPos]->descricao, descricao);
}

void setComandoNome(Notebook n, char *nome, int cmdPos){
 	strcpy(n->arrayCmd[cmdPos]->nome, nome);
}

void setComandoArgs(Notebook n, char *args, int cmdPos, int argsNr){
	if(args==NULL) 
		n->arrayCmd[cmdPos]->args[argsNr]=NULL;
	else 
		strcpy(n->arrayCmd[cmdPos]->args[argsNr], args);
}

void setComandoOutput(Notebook n, char *output, int cmdPos, int outputNr){

	/*
	if (outputNr == n->arrayCmd[cmdPos]->otSize){
		
		n->arrayCmd[cmdPos]->output = realloc(n->arrayCmd[cmdPos]->output, 2*(n->arrayCmd[cmdPos]->otSize)*sizeof(*(n->arrayCmd[cmdPos]->output)));
		
		for(int i=(n->arrayCmd[cmdPos]->otSize); i<((n->arrayCmd[cmdPos]->otSize)*2); i++)
			n->arrayCmd[cmdPos]->output[i] = (char*) malloc( LEN * sizeof(char));
		
		n->arrayCmd[cmdPos]->otSize = (n->arrayCmd[cmdPos]->otSize)*2;
	}*/

	if (n->used == n->size){
		n->arrayCmd = realloc(n->arrayCmd, 2*(n->size)*sizeof(struct comando));
		n->size =(n->size)*2;
	}
	if(output==NULL) 
		n->arrayCmd[cmdPos]->output[outputNr]=NULL;
	else{
		strcpy(n->arrayCmd[cmdPos]->output[outputNr], output);
	}
	
}

