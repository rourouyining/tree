CC=gcc
OBJ=tree.o

LIB=
CFLAGS= -g -Wall
INCLUDE=

target=tree

all:$(OBJ)
	$(CC) $^ -o $(target) $(LIB)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

clean:
	rm -rf *.o $(target)

