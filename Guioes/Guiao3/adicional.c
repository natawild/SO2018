#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
Implemente um programa controlador que execute concorrentemente um conjunto de programas
especificados como argumento da sua linha de comando. O controlador deverá re-executar cada
programa enquanto não terminar com código de saída nulo. No final da sua execução, o controlador
deverá imprimir o número de vezes que cada programa foi executado. Considere que os programas são
especificados sem qualquer argumento.
*/
 
int get_pid(int *connect_pid_i, int n, int pid){
    int i = 0;
    while(i < n && connect_pid_i[i] != pid)
        i++;
    return i;
}
 
int check_array(int *v, int n){
    int i = 0;
 
    while((v[i] == 0) && i < n){
        i++;
    }
 
    return i;
}
 
int main(int argc, char const *argv[]) {
    int v[argc-1],n_vezes[argc-1],connect_pid_i[argc-1];
    int i;
    for(i=0; i < argc - 1; i++){
        v[i] = -1;
        n_vezes[i] = 0;
        connect_pid_i[i] = -1;
    }
    int n_forks = 0, t,p,status,status2;
    int * a = malloc(sizeof(int));
 
    while (check_array(v,argc-1) != (argc-1)) {
        for(i = 0,n_forks=0; i < argc -1; i++){
            if (v[i] != 0){
                n_forks++;
                n_vezes[i]++;
                p = fork();
                if (p == 0){
                    execlp(argv[i+1],argv[i+1],NULL);
                    //perror("erros");
                    _exit(-1);
                }
                else{
                    connect_pid_i[i]=p;
                    //sleep(2);
                }
            }
        }
 
        for(t=0; t < n_forks; t++){
            p = wait(&status);
            if WIFEXITED(status) {
                status2 = WEXITSTATUS(status);
                i = get_pid(connect_pid_i,argc-1,p);
                //n_vezes[i]++;
                //printf("%d\n",status2);
                if (status2 == 0)
                    v[i] = 0;
            }
        }
    }
    for(i=1; i < argc; i++)
        printf("%s -> %d \n",argv[i],n_vezes[i-1]);
 
    return 0;
}