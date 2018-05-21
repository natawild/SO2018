#ifndef __PARSER_H__
#define __PARSER_H__

#include "struct.h"

int containsPipes(char *nome);

int seeDepends(char *nome);

Notebook parser(Notebook n, char *argv);

#endif 
