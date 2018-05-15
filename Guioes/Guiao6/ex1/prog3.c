#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char const *argv[]){
   puts("antes"); 
   int ficheiro = open("fifo",O_RDONLY), n;//le
   puts("depois"); 
   char l[1024];

   while(n=read(ficheiro,l,sizeof(l+1))){
        write(1,l,n);
   }
   close(ficheiro); 



	return 0;
}