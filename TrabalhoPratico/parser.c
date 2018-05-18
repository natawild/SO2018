#include <stdio.h> //printf function
#include <fcntl.h> //open function
#include <unistd.h> //read funciton
#include "parser.h"
#include "struct.h"

Notebook parser(Notebook n, char *argv){
	int fnb;
	char buf;

	fnb = open(argv, O_RDONLY | O_RDWR);

	return n;
}
