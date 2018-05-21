#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "struct.h"


struct comando{
   char  *descricao; //linha do notebook com a descrição do comando
   char  *nome; //linha do notebook que tem o nome do comando
   char **args; //array de strings, onde cada uma é um argumento do comando
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
	c -> descricao = (char *) malloc(512 * sizeof(char));
	c -> nome = (char *) malloc(512 * sizeof(char));
	c -> args = (char **) malloc(512 * sizeof(char*));
	for (i=0; i<512; i++){
    	(c->args)[i] = (char*) malloc( 512 * sizeof(char));
	}
	c -> output = (char **) malloc(512 * sizeof(char*));
	for (i=0; i<512; i++){
    	(c->output)[i] = (char*) malloc( 512 * sizeof(char));
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
	strcpy(n->arrayCmd[n->used]->args[i], strtok(nome," $|"));
	while( (aux = strtok(NULL," $|")) != NULL)
		strcpy(n->arrayCmd[n->used]->args[++i], aux);
	n->arrayCmd[n->used]->args[++i] = NULL;	
	/*
	i=0;
   	while((n->arrayCmd[n->used]->args[i])!=NULL){
   		printf("%s\n", n->arrayCmd[n->used]->args[i++]);
   		printf("%d\n",i);
   	}*/
   	
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
		for(j=0; (n->arrayCmd[i]->args[j])!=NULL; j++)
			printf("[%d] %s -- ", j, n->arrayCmd[i]->args[j]);
		
		printf("\n");
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
 	char * descricao = malloc(512 * sizeof(char));
 	strcpy(descricao, n->arrayCmd[cmdPos]->descricao);
	return descricao;
}

char *getComandoNome(Notebook n, int cmdPos){
 	char * nome = malloc(512 * sizeof(char));; 
 	strcpy(nome, n->arrayCmd[cmdPos]->nome);
	return nome;
}

char **getComandoArgs(Notebook n, int cmdPos){
 	char **args = malloc(512 * sizeof(char));
 	int j;
 	for (j=0; j<512; j++){
    	args[j] = (char*) malloc( 512 * sizeof(char));
	} 
 	for(j=0; (n->arrayCmd[cmdPos]->args[j])!=NULL; j++){
 		strcpy(args[j], n->arrayCmd[cmdPos]->args[j]);
 	}

 	args[j]=NULL;
 	
	return args;
}

char **getComandoOutput(Notebook n, int cmdPos){
 	char **output = malloc(512 * sizeof(char));
 	int j;
 	for (j=0; j<512; j++){
    	output[j] = (char*) malloc( 512 * sizeof(char));
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

void setComandoOutput(Notebook n, char *output, int cmdPos, int outputNr){
	if(output==NULL) 
		n->arrayCmd[cmdPos]->output[outputNr]=NULL;
	else 
		strcpy(n->arrayCmd[cmdPos]->output[outputNr], output);
	
}

