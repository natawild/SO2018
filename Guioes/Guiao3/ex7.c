#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define TAM_STR 50
#define TAM_STR_MAIN 100

/*
Implemente um interpretador de comandos muito simples ainda que inspirado na bash. O interpretador
deverá executar comandos especificados numa linha de texto introduzida pelo utilizador. Os comandos
são compostos pelo nome do programa a executar e uma eventual lista de argumentos. Os comandos
podem ainda executar em primeiro plano, ou em pano de fundo, caso o utilizador termine a linha com &.
O interpretador deverá terminar a sua execução quando o utilizador invocar o comando interno exit ou
quando assinalar o fim de ficheiro (Control-D no início de uma linha em sistemas baseados em Unix).
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
 
 
int mysystem(const char * command){
 
    int p;
 
    p=fork();
 
    if (p == 0) {
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
 
    return 0;
}
 
int main(){
 
    char * str = malloc(TAM_STR_MAIN*sizeof(char));
 
    int n;
 
    while( (n=read(0, str, 100)) > 0){
        str[n-1] = '\0';
        mysystem(str);
    }
}