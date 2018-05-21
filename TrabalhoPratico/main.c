#include <stdio.h>
#include "parser.h"
#include "struct.h"

int main(int argc, char *argv[]){
	int i;

	Notebook n = initNotebook(10);
	
	parser(n, argv[1]);

	/*para ver a estrutura a funcminar
	int res = insereNotebook(n,desc,nome,0);
	*/

	/*para ver o conteudo da estrutura*/
	printNotebook(n);
	
	
	/*
	printf("struct %s\n", getComandoDescricao(n, 0));
	*/

	return 0;
}