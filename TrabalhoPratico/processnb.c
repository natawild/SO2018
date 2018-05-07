#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h> //printf
#include <sys/wait.h> //wait


int main(int argc, char *argv[]){
	int x; //fork
	int f, aux, out; //descritores
	int i=0; //ciclos while
	int fd[2]; //descritores pipe
	
	char buf; //read e write
	char cmd[100]; //comando

	f = open(argv[1], O_RDONLY | O_RDWR);

	aux = open("aux", O_CREAT | O_RDWR | O_TRUNC, 0666);

	out = open("output", O_CREAT | O_RDWR | O_TRUNC, 0666);

	if(f<0 || aux<0)
		exit(-1);

	
	while(read(f, &buf, 1)==1){
		if(buf!='$'){
			write(aux, &buf, 1);

			while(read(f, &buf, 1)==1 && buf!='\n'){
				write(aux, &buf, 1);				
			}
			write(aux, "\n", 1);
		}
		
		
		if(buf=='$'){
			write(aux, &buf, 1);
			read(f, &buf, 1);
			
			if(buf==' '){
				write(aux, &buf, 1);
				while(read(f, &buf, 1)==1 && buf!='\n'){
					write(aux, &buf, 1);
					cmd[i]=buf;		
					i++;
				}
				write(aux, &buf, 1);
				
				pipe(fd);

				x = fork();

				if (x==0){
					close(fd[0]);
					dup2(fd[1], 1);
					close(fd[1]);
					execlp(cmd, cmd, NULL);
					_exit(0);				
				}
				wait(NULL);

				write(aux, ">>>\n", 4);
				i=0;
				while(read(fd[0], &buf, 1)==1 && buf!='\0' && i<6){
					write(out, &buf, 1);
					write(aux, &buf, 1);
					printf("%c",buf);
					
					while(read(fd[0], &buf, 1)==1 && buf!='\n'){
						printf("%c",buf);
						write(out, &buf, 1);
						write(aux, &buf, 1);
					}
					i++;	
					printf("\n");
					write(out, &buf, 1);
					write(aux, &buf, 1);
				}
				printf("%s\n","chegueiaquiechegueibem" );
				close(fd[0]);
				close(fd[1]);
				write(aux, "<<<\n", 4);
				

			}
			
			if(buf=='|'){
				i=0;
				write(aux, &buf, 1);
				while(read(f, &buf, 1)==1 && buf!='\n'){
						write(aux, &buf, 1);
						cmd[i]=buf;
						i++;	
				}
				write(aux, &buf, 1);
				cmd[i]='\0';
				pipe(fd);
				x=fork();
				if(x==0){
					dup2(fd[1],1);
					printf("%s\n",cmd );
					execlp(cmd, cmd, "output", NULL);
					_exit(-1);
				}
				wait(NULL);
				
				i=0;
				while(read(fd[0], &buf, 1 && i<5)==1){
					write(aux, &buf, 1);
					i++;
				}
			}				
			
				}

		}
		
	//}

	return 0;
}