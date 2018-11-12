CFLAGS = -Wall -Wextra
CC = gcc -std=c99
SRC = main.c bst.c 
OBJ = $(SRC:.c = .o)
autocomplete: $(OBJ)
	$(CC) $(CFLAGS) -o autocomplete $(OBJ)
clean:
	rm -f core *.o 

run:
	clear
	./autocomplete

valgrind:
	clear 
	valgrind ./autocomplete

