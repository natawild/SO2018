#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

#define TAM_STR 50

/*
Implemente uma versão simplificada da função system(). Ao contrário da função original, não tente
suportar qualquer tipo de redireccionamento, ou composição/encadeamento de programas executáveis.
O único argumento deverá ser uma string que especifica um programa executável e uma eventual lista de
argumentos. Procure que o comportamento e valor de retorno da sua função sejam compatíveis com a
original.

*/

int conta_palavras(const char * line){
    int i = 0;
    int palavra = 0,status = 0;
    for(;line[i] != '\0'; i++){
        if (status == 0 && line[i] != ' ') {
            palavra++; status = 1;
        }
        else if (status == 1 && line[i] == ' '){
            status=0;
        }
    }
 
    return palavra;
}


void escreve_conta_palavras(const char * line,int *v,int n,char ** args){
    int i = 0;
    int palavra = 0,status = 0;
    for(;line[i] != '\0'; i++){
        if (status == 0 && line[i] != ' ') {
            palavra++;
            status = 1;
            args[palavra-1][v[palavra-1]] = line[i];
            v[palavra-1]++;
        }
        else if (status == 1 && line[i] == ' '){
            status=0;
        }
        else if (status == 1){
            args[palavra-1][v[palavra-1]] = line[i];
            v[palavra-1]++;
        }
    }
    for(i=0; i < palavra; i++)
        args[i][v[i]] ='\0';
}

//o número de argumentos pode ser no máximo o nr de caracteres 
//quando aparecer um espaço avanço 
//quando encontrei um zero termino 

//Implementar e testar 
int mysystem(char * command){
	int n = conta_palavras(command); // contar palavras
 
    int v[n],i; // array com o tam das palavra
    for(i=0; i < n; v[i++]=0); // inicializar o array
 
    char ** args = malloc((n+1)*sizeof(char*)); // alocar espaço para os argumentos
    for(i=0; i <= n; i++){
        args[i] = malloc(TAM_STR*sizeof(char));
    }
    args[n] = NULL;
 
    escreve_conta_palavras(command,v,n,args); // preencher os argumentos
 
    execvp(args[0],args); //executar
    perror("erros->bla");
    _exit(0);
}


//int mysystem(const char *command); //não estou autorizado a mexer neste comando porque é um const 

int  main() {
	mysystem("echo eu sou linda  "); 

}


