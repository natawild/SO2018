#ifndef __STRUCT_H__
#define __STRUCT_H__

typedef struct comando *Comando;
typedef struct notebook *Notebook;

Comando initComando();

Notebook initNotebook(int size);

int insereNotebook(Notebook n, char *descricao, char *nome, int depends);

int printNotebook(Notebook n);

int getNotebookSize(Notebook n);

int getNotebookUsed(Notebook n);

char *getComandoDescricao(Notebook n, int i);

char *getComandoNome(Notebook n, int i);

int getComandoDepends(Notebook n, int i);

#endif 

