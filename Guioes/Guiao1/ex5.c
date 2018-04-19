#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdlib.h> /* para utilizar o exit */ 
#include <stdio.h> 
#include "ex5.h"

//Implemente a leitura de uma linha numa função readln, cujo prototipo é compatível com a chamada
//ao sistema read. Nesta versão, leia um caractere de cada vez.

// ssize_t readln(int fildes, void *buf, size_t nbyte);

ssize_t readln(int fildes, void *buf, size_t nbyte) {

	size_t i = 0;
	ssize_t n = 1;
	char c = ' ';
	
	/* Enquanto está a ler algo mas que seja menos de nbyte caracteres, e não seja o '\n' */
	while((i < nbyte) && (n > 0) && (c != '\n')) {
		//Lê um caractere
		n = read(fildes, &c, 1);
		// Se não for o '\n' adiciona-o ao buffer
		if(n && (c != '\n')) {
			((char*) buf)[i] = c;
			i++;
		}
	}

	// Adição de EOF == 0 com verificação no caso de chegar ao limite de leitura (N);
	if(i < nbyte)
		((char*) buf)[i] = 0;
	else {
		// passou o limite (i == 100). buf[99] = EOF.
		i--;
		((char*) buf)[i] = 0;
	}

	// se deu erro na leitura retorna esse mesmo erro
	if(n < 0)
		return n;
	// no caso de apanhar a linha só com o '\n'
	if((n == 0) && (i == 0))
		return (-1);
	return i;
}
