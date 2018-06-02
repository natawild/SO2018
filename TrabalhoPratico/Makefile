CC=gcc
CFLAGS=-I. -g
DEPS = parser.h struct.h readl.h 
OBJ = main.o parser.o struct.o readl.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

processanb: $(OBJ)
	gcc -g -o $@ $^ $(CFLAGS)

clean: 
	rm erros.nb core main.o parser.o readl.o struct.o processanb
