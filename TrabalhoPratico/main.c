#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "parser.h"
#include "struct.h"

int main(int argc, char *argv[]){
	int i, j, fnb;

	//função que inicializa a estrutura
	Notebook n = initNotebook(10);
	
	//função que analisa e distribui o ficheiro pela estrutura
	parser(n, argv[1]);

	//função que imprime o conteudo da estrutura
	printNotebook(n);
	
	//parte da função que imprime a estrutura no ficheiro original
	fnb = open(argv[1], O_RDONLY | O_RDWR | O_TRUNC, 0666);
	for(i=0; i<(getNotebookUsed(n)); i++){
		write(fnb, getComandoDescricao(n,i), strlen(getComandoDescricao(n,i)));
		write(fnb, "\n", 1);
		write(fnb, getComandoNome(n,i), strlen(getComandoNome(n,i)));
		write(fnb, "\n", 1);
		write(fnb, ">>>\n", 4);
		for (j=0; (getComandoOutput(n, i)[j])!=NULL; j++){
			write(fnb, getComandoOutput(n, i)[j],  strlen(getComandoOutput(n, i)[j]));
			write(fnb, "\n", 1);
		}
		write(fnb, "<<<\n", 4);
	}
	return 0;
}