CC=gcc
CFLAGS=-I.
DEPS = parser.h struct.h readl.h 
OBJ = main.o parser.o struct.o readl.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

processanb: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean: 
	$(RM) count *.o *~
