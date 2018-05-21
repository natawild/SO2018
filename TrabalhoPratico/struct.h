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

char *getComandoDescricao(Notebook n, int cmdPos);

char *getComandoNome(Notebook n, int cmdPos);

char **getComandoArgs(Notebook n, int cmdPos);

char **getComandoOutput(Notebook n, int cmdPos);

int getComandoDepends(Notebook n, int cmdPos);

void setComandoDescricao(Notebook n, char *descricao, int cmdPos);

void setComandoNome(Notebook n, char *nome, int cmdPos);

void setComandoOutput(Notebook n, char *output, int cmdPos, int outputNr);


#endif 

