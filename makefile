CC = gcc 
SRC = main.c bst.c 
OBJ = $(SRC:.c = .o)
autocomplete: $(OBJ)
	$(CC) -o autocomplete $(OBJ)
clean:
	rm -f core *.o 

run:
	clear
	./autocomplete

valgrind:
	clear 
	valgrind ./autocomplete